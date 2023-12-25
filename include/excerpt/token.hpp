#pragma once

#include <map>
#include <memory>

namespace excerpt {
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

  static const std::map<TokenType, std::string> TOKEN_STR = {
      {TokenType::PLUS, "PLUS"},
      {TokenType::MINUS, "MINUS"},
      {TokenType::STAR, "STAR"},
      {TokenType::SLASH, "SLASH"},
      {TokenType::PERCENT, "PERCENT"},
      {TokenType::LPAREN, "LPAREN"},
      {TokenType::RPAREN, "RPAREN"},
      {TokenType::LBRACE, "LBRACE"},
      {TokenType::RBRACE, "RBRACE"},
      {TokenType::LBRACKET, "LBRACKET"},
      {TokenType::RBRACKET, "RBRACKET"},
      {TokenType::SEMICOLON, "SEMICOLON"},
      {TokenType::COLON, "COLON"},
      {TokenType::COMMA, "COMMA"},
      {TokenType::DOT, "DOT"},
      {TokenType::ASSIGN, "ASSIGN"},
      {TokenType::EQUAL, "EQUAL"},
      {TokenType::NOT_EQUAL, "NOT_EQUAL"},
      {TokenType::LESS, "LESS"},
      {TokenType::LESS_EQUAL, "LESS_EQUAL"},
      {TokenType::GREATER, "GREATER"},
      {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
      {TokenType::IF, "IF"},
      {TokenType::ELSE, "ELSE"},
      {TokenType::WHILE, "WHILE"},
      {TokenType::FOR, "FOR"},
      {TokenType::BREAK, "BREAK"},
      {TokenType::CONTINUE, "CONTINUE"},
      {TokenType::RETURN, "RETURN"},
      {TokenType::TRUE, "TRUE"},
      {TokenType::FALSE, "FALSE"},
      {TokenType::INT, "INT"},
      {TokenType::FLOAT, "FLOAT"},
      {TokenType::CHAR, "CHAR"},
      {TokenType::BOOL, "BOOL"},
      {TokenType::IDENTIFIER, "IDENTIFIER"},
      {TokenType::INTEGER_LITERAL, "INTEGER_LITERAL"},
      {TokenType::FLOAT_LITERAL, "FLOAT_LITERAL"},
      {TokenType::CHAR_LITERAL, "CHAR_LITERAL"},
      {TokenType::STRING_LITERAL, "STRING_LITERAL"},
      {TokenType::END, "END"},
      {TokenType::INVALID, "INVALID"}};

  struct Token {
    TokenType type;    /**< The type of the token. */
    std::string value; /**< The value of the token. */

    /**
     * @brief Construct a new Token object.
     *
     * @param type The type of the token.
     * @param value The value of the token.
     */
    Token(TokenType type, const std::string& value)
        : type(type), value(value) {}

    /**
     * @brief Get a string representation of the token.
     *
     * @param type The type of the token.
     * @param value The value of the token.
     */
    std::string str() const {
      return "Token(" + TOKEN_STR.at(type) + ", " + value + ")";
    }
  };
}  // namespace excerpt
