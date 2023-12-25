#pragma once

#include <memory>
#include <unordered_map>
#include <string>

#include "token.hpp"

namespace excerpt {

  /**
   * @brief Class for tokenizing input strings.
   */
  class Tokenizer {
   public:
    /**
     * @brief Constructor for Tokenizer.
     * @param input The input string to be tokenized.
     */
    explicit Tokenizer(std::shared_ptr<std::string> input);

    /**
     * @brief Get the next token from the input string.
     * @return The next token.
     */
    std::shared_ptr<Token> scan();

    /**
     * @brief Reset the tokenizer state.
     */
    void reset();

    /**
     * @brief Scan for single character tokens.
     * @param current_char The current character.
     * @return The token.
     */
    std::shared_ptr<Token> scan_single(char current_char);

   private:
    std::shared_ptr<std::string> input;
    size_t position; /**< The current position in the input string. */

    /**
     * @brief Parses an identifier.
     * @return An identifier token, can be a reserved keyword or data type.
     */
    std::shared_ptr<Token> parse_ident();

    /**
     * @brief Parses an number literal.
     * @return An integer token or a float token.
     */
    std::shared_ptr<Token> parse_number();

    /**
     * @brief Parses a character literal.
     * @return A character literal token.
     */
    std::shared_ptr<Token> parse_char();

    /**
     * @brief Parses a string literal.
     * @return A string literal token.
     */
    std::shared_ptr<Token> parse_string();
  };

}  // namespace excerpt
