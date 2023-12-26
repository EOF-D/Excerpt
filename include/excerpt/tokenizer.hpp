#pragma once

#include "token.hpp"

#include <iostream>
#include <functional>
#include <sstream>
#include <memory>
#include <unordered_map>

namespace excerpt {

  /**
   * @brief A class for tokenizing a given input string.
   */
  class Tokenizer {
   public:
    /**
     * @brief Constructs a Tokenizer instance.
     * @param source The source string to tokenize.
     */
    explicit Tokenizer(std::shared_ptr<std::string> source);

    /**
     * @brief Peek at the next character without consuming it.
     * @param offset The offset to peek at. Defaults to 1.
     * @return The next character.
     */
    char peek(int offset = 1);

    /**
     * @brief Advance the current index and return the next character.
     * @return The next character.
     */
    char advance();

    /**
     * @brief Get's the current character.
     * @return The current character.
     */
    char current();

    /**
     * @brief Skips until character is not whitespace or a comment
     * @return The next non-whitespace/comment character
     */
    char skipws();

    /**
     * @brief Walk the tokenizer through until the predicate is false.
     * @param predicate The predicate to match.
     * @return The characters that matched the predicate.
     */
    std::string walk(std::function<bool(char)> predicate);

    /**
     * @brief Tokenize the next character.
     * @return The tokenized character.
     */
    std::shared_ptr<Token> next();

    /**
     * @brief Parses a string literal.
     * @return The token representation of the literal.
     */
    std::shared_ptr<Token> parse_string();

    /**
     * @brief Parses a number literal.
     * @return The token representation of the literal.
     */
    std::shared_ptr<Token> parse_number();

    /**
     * @brief Parses an identifier.
     * @return The token representation of the identifier.
     */
    std::shared_ptr<Token> parse_identifier();

    /**
     * @brief Parses a symbol.
     * @return The token representation of the symbol.
     */
    std::shared_ptr<Token> parse_symbol();

   private:
    std::shared_ptr<std::string>
        source;  //**< The source string to tokenize. */

    size_t index;  //**< The current index in the source string. */
    int line;      //**< The current line number. */
    int column;    //**< The current column number. */
  };

}  // namespace excerpt
