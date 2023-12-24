#include "excerpt/argparser.hpp"
#include <iostream>

int main(int argc, const char* argv[]) {
  excerpt::ArgParser parser(argc, argv);

  if (parser.show_help()) {
    std::cout << "Excerpt Compiler - Help Menu\n";
  }

  return 0;
}
