#include "KaleidoscopeJIT.h"

using namespace llvm;
using namespace llvm::orc;

std::string KaleidoscopeJIT::mangle(const std::string &Name) {
    std::string MangledName;
    {
        raw_string_ostream MangledNameStream(MangledName);
        Mangler::getNameWithPrefix(MangledNameStream, Name, DL);
    }
    return MangledName;
}

KaleidoscopeJIT::KaleidoscopeJIT()
      : Resolver(createLegacyLookupResolver(
            ES,
            [this](const std::string &Name) { return findMangledSymbol(Name); },
            [](Error Err) { cantFail(std::move(Err), "lookupFlags failed"); })),
        TM(EngineBuilder().selectTarget()), DL(TM->createDataLayout()),
        ObjectLayer(AcknowledgeORCv1Deprecation, ES,
                    [this](VModuleKey) {
                      return ObjLayerT::Resources{
                          std::make_shared<SectionMemoryManager>(), Resolver};
                    }),
        CompileLayer(AcknowledgeORCv1Deprecation, ObjectLayer,
                     SimpleCompiler(*TM)) {
    llvm::sys::DynamicLibrary::LoadLibraryPermanently(nullptr);
}

VModuleKey KaleidoscopeJIT::addModule(std::unique_ptr<Module> M) {
    auto K = ES.allocateVModule();
    cantFail(CompileLayer.addModule(K, std::move(M)));
    ModuleKeys.push_back(K);
    return K;
}

void KaleidoscopeJIT::removeModule(VModuleKey K) {
    ModuleKeys.erase(find(ModuleKeys, K));
    cantFail(CompileLayer.removeModule(K));
}

JITSymbol KaleidoscopeJIT::findMangledSymbol(const std::string &Name) {
#ifdef _WIN32
    // The symbol lookup of ObjectLinkingLayer uses the SymbolRef::SF_Exported
    // flag to decide whether a symbol will be visible or not, when we call
    // IRCompileLayer::findSymbolIn with ExportedSymbolsOnly set to true.
    //
    // But for Windows COFF objects, this flag is currently never set.
    // For a potential solution see: https://reviews.llvm.org/rL258665
    // For now, we allow non-exported symbols on Windows as a workaround.
    const bool ExportedSymbolsOnly = false;
#else
    const bool ExportedSymbolsOnly = true;
#endif

    // Search modules in reverse order: from last added to first added.
    // This is the opposite of the usual search order for dlsym, but makes more
    // sense in a REPL where we want to bind to the newest available definition.
    for (auto H : make_range(ModuleKeys.rbegin(), ModuleKeys.rend()))
      if (auto Sym = CompileLayer.findSymbolIn(H, Name, ExportedSymbolsOnly))
        return Sym;

    // If we can't find the symbol in the JIT, try looking in the host process.
    if (auto SymAddr = RTDyldMemoryManager::getSymbolAddressInProcess(Name))
      return JITSymbol(SymAddr, JITSymbolFlags::Exported);

#ifdef _WIN32
    // For Windows retry without "_" at beginning, as RTDyldMemoryManager uses
    // GetProcAddress and standard libraries like msvcrt.dll use names
    // with and without "_" (for example "_itoa" but "sin").
    if (Name.length() > 2 && Name[0] == '_')
      if (auto SymAddr =
              RTDyldMemoryManager::getSymbolAddressInProcess(Name.substr(1)))
        return JITSymbol(SymAddr, JITSymbolFlags::Exported);
#endif

    return nullptr;
  }