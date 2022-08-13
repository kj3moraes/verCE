#include "Lexer.h"
#include <algorithm>
#include <cctype>
#include <map>

const std::map<std::string, Kind> specialIDS = {
    {"def", DEF},
    {"extern", EXTERN},
};

