#include <gtest/gtest.h>

TEST(BasicFunctionality_Test, Numbers_Test) {
    ASSERT_EQ(1, 1);
}

TEST(BasicFunctionality_Test, Extern_Test) {
    ASSERT_EQ(1, 1);
}

TEST(BasicFunctionality_Test, FunctionDef_Test) {
    ASSERT_EQ(1, 1);
}

TEST(BasicFunctionality_Test, _Test) {
    ASSERT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
