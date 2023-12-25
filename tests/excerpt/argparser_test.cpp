#include "gtest/gtest.h"
#include "excerpt_utils/argparser.hpp"

using namespace excerpt;

TEST(ArgParserTest, ShowHelp) {
  const char* argv[] = {"test", "--help"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  ArgParser parser(argc, argv);
  ASSERT_TRUE(parser.show_help());
}

TEST(ArgParserTest, InputFile) {
  const char* argv[] = {"test", "input.txt"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  ArgParser parser(argc, argv);
  ASSERT_EQ(parser.input_file(), "input.txt");
}

TEST(ArgParserTest, OutputFile) {
  const char* argv[] = {"test", "--output", "output.txt"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  ArgParser parser(argc, argv);
  ASSERT_EQ(parser.output_file(), "output.txt");
}

// Add more test cases as needed

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
