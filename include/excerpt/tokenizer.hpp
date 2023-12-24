#pragma once

#include <memory>
#include <unordered_map>
#include <string>

namespace excerpt {

  /**
   * @brief Enumeration representing different token types.
   */
  enum class TokenType {
    // Single-character tokens
    PLUS,       // +
    MINUS,      // -
    STAR,       // *
    SLASH,      // /
    PERCENT,    // %
    LPAREN,     // (
    RPAREN,     // )
    LBRACE,     // {
    RBRACE,     // }
    LBRACKET,   // [
    RBRACKET,   // ]
    SEMICOLON,  // ;
    COLON,      // :
    COMMA,      // ,
    DOT,        // .

    // Operators
    ASSIGN,         // =
    EQUAL,          // ==
    NOT_EQUAL,      // !=
    LESS,           // <
    LESS_EQUAL,     // <=
    GREATER,        // >
    GREATER_EQUAL,  // >=

    // Keywords
    IF,
    ELSE,
    WHILE,
    FOR,
    BREAK,
    CONTINUE,
    RETURN,
    TRUE,
    FALSE,

    // Data types
    INT,
    FLOAT,
    CHAR,
    BOOL,

    // Identifiers and literals
    IDENTIFIER,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    CHAR_LITERAL,
    STRING_LITERAL,

    // End of file
    END,

    // Invalid token
    INVALID
  };

  /**
   * @brief Structure representing a token with its type and value.
   */
  struct Token {
    TokenType type;    /**< The type of the token. */
    std::string value; /**< The value associated with the token. */

    /**
     * @brief Constructor for Token.
     * @param t The type of the token.
     * @param v The value associated with the token.
     */
    Token(TokenType t, const std::string& v) : type(t), value(v) {}

    /**
     * @brief Get the string representation of a token type.
     * @param type The token type.
     * @return The string representation of the token type.
     */
    static TokenType fromString(const std::string& str) {
      static const std::unordered_map<std::string, TokenType> str_map = {
          {"PLUS", TokenType::PLUS},
          {"MINUS", TokenType::MINUS},
          {"STAR", TokenType::STAR},
          {"SLASH", TokenType::SLASH},
          {"PERCENT", TokenType::PERCENT},
          {"LPAREN", TokenType::LPAREN},
          {"RPAREN", TokenType::RPAREN},
          {"LBRACE", TokenType::LBRACE},
          {"RBRACE", TokenType::RBRACE},
          {"LBRACKET", TokenType::LBRACKET},
          {"RBRACKET", TokenType::RBRACKET},
          {"SEMICOLON", TokenType::SEMICOLON},
          {"COLON", TokenType::COLON},
          {"COMMA", TokenType::COMMA},
          {"DOT", TokenType::DOT},
          {"ASSIGN", TokenType::ASSIGN},
          {"EQUAL", TokenType::EQUAL},
          {"NOT_EQUAL", TokenType::NOT_EQUAL},
          {"LESS", TokenType::LESS},
          {"LESS_EQUAL", TokenType::LESS_EQUAL},
          {"GREATER", TokenType::GREATER},
          {"GREATER_EQUAL", TokenType::GREATER_EQUAL},
          {"IF", TokenType::IF},
          {"ELSE", TokenType::ELSE},
          {"WHILE", TokenType::WHILE},
          {"FOR", TokenType::FOR},
          {"BREAK", TokenType::BREAK},
          {"CONTINUE", TokenType::CONTINUE},
          {"RETURN", TokenType::RETURN},
          {"TRUE", TokenType::TRUE},
          {"FALSE", TokenType::FALSE},
          {"INT", TokenType::INT},
          {"FLOAT", TokenType::FLOAT},
          {"CHAR", TokenType::CHAR},
          {"BOOL", TokenType::BOOL},
          {"IDENTIFIER", TokenType::IDENTIFIER},
          {"INTEGER_LITERAL", TokenType::INTEGER_LITERAL},
          {"FLOAT_LITERAL", TokenType::FLOAT_LITERAL},
          {"CHAR_LITERAL", TokenType::CHAR_LITERAL},
          {"STRING_LITERAL", TokenType::STRING_LITERAL},
          {"END", TokenType::END},
          {"INVALID", TokenType::INVALID}};

      auto it = str_map.find(str);
      if (it != str_map.end()) {
        return it->second;
      }

      return TokenType::INVALID;
    }
  };

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
