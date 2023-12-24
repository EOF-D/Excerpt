#pragma once

#include "llvm/Support/CommandLine.h"

namespace excerpt {

  /**
   * @brief Command-line parser for the Excerpt compiler.
   * This class uses LLVM's CommandLine library to parse command-line options.
   */
  class ArgParser {
   public:
    /**
     * @brief Constructs a ArgParser instance and parses the command-line
     * options.
     * @param argc The number of command-line arguments.
     * @param argv An array of command-line arguments.
     */
    ArgParser(int argc, const char *argv[]) {
      llvm::cl::ParseCommandLineOptions(argc, argv);
    }

    /**
     * @brief Get the input file name.
     * @return The input file name specified on the command line.
     */
    std::string input_file() const { return _input_file; }

    /**
     * @brief Get the output file name.
     * @return The output file name specified on the command line.
     */
    std::string output_file() const { return _output_file; }

    /**
     * @brief Check if the help option is specified.
     * @return True if the help option is specified, false otherwise.
     */
    bool show_help() const { return help; }

   private:
    // The input file name.
    llvm::cl::opt<std::string> _input_file{
        llvm::cl::Positional, llvm::cl::desc("Specify input filename"),
        llvm::cl::value_desc("filename"), llvm::cl::init("-")};

    // The output file name.
    llvm::cl::opt<std::string> _output_file{
        "output", llvm::cl::desc("Specify output filename"),
        llvm::cl::value_desc("filename")};

    // True if the help flag is set, otherwise false.
    llvm::cl::opt<bool> help{llvm::cl::desc("Show help")};
  };

}  // namespace excerpt
