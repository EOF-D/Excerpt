#include "excerpt/tokenizer.hpp"
#include "excerpt_utils/logger.hpp"

namespace excerpt {
  std::shared_ptr<Token> create_token(TokenType type, std::string value,
                                      int line, int column) {
    return make_unique<Token>(type, value, line, column);
  }

  Tokenizer::Tokenizer(std::shared_ptr<std::string> source)
      : source(source), index(0), line(1), column(1) {}

  char Tokenizer::peek(int offset) {
    if (index + offset >= source->length()) {
      return '\0';
    }

    return source->at(index + offset);
  }

  char Tokenizer::advance() {
    if (index >= source->length()) {
      return '\0';
    }

    char current = source->at(index);

    index++;
    column++;

    if (current == '\n') {
      line++;
      column = 1;
    }

    return current;
  }

  char Tokenizer::current() {
    if (index >= source->length()) {
      return '\0';
    }

    return source->at(index);
  }

  char Tokenizer::skipws() {
    while (true) {
      // Skip whitespace characters
      while (std::isspace(current())) {
        advance();
      }

      // Check for single-line comments
      if (current() == '/' && peek() == '/') {
        while (current() != '\0' && current() != '\n') {
          advance();
        }
      }

      // Check for multi-line comments
      else if (current() == '/' && peek() == '*') {
        int sline = line;
        int scol = column;

        // Skip the opening of the multi-line comment
        advance();
        advance();

        while (true) {
          if (current() == '\0') {
            // Unclosed multi-line comment
            return '\0';
          } else if (current() == '*' && peek() == '/') {
            // Skip the closing of the multi-line comment
            advance();
            advance();
            break;
          } else {
            // Skip other characters in the comment
            advance();
          }
        }
      } else {
        break;
      }
    }

    return current();
  }

  std::string Tokenizer::walk(std::function<bool(char)> predicate) {
    std::string result;

    while (predicate(current())) {
      result += current();
      advance();
    }

    return result;
  }

  std::shared_ptr<Token> Tokenizer::next() {
    char current_char = skipws();
    if (current_char == '\0')
      return create_token(TokenType::END, "", line, column);

    if (std::isdigit(current_char))
      return parse_number();

    else if (std::isalpha(current_char) || current_char == '_')
      return parse_identifier();

    else if (current_char == '"')
      return parse_string();

    return parse_symbol();
  }

  std::shared_ptr<Token> Tokenizer::parse_string() {
    std::stringstream stream;

    int sline = line;
    int scol = column;

    // Skip the opening quote
    advance();

    while (current() != '"') {
      if (current() == '\0') {
        return create_token(TokenType::INVALID, stream.str(), sline, scol);
      }

      stream << advance();
    }

    // Skip the closing quote
    advance();

    return create_token(TokenType::STRING_LITERAL, stream.str(), sline, scol);
  }

  std::shared_ptr<Token> Tokenizer::parse_number() {
    std::stringstream stream;

    int sline = line;
    int scol = column;

    // Consuming and appending digits
    stream << walk([](char ch) { return std::isdigit(ch); });

    // If the character is a dot, handle as float.
    if (current() == '.' && std::isdigit(peek())) {
      // Consume the dot
      stream << advance();
      stream << walk([](char ch) { return std::isdigit(ch); });

      return create_token(TokenType::FLOAT_LITERAL, stream.str(), sline, scol);
    }

    return create_token(TokenType::INTEGER_LITERAL, stream.str(), sline, scol);
  }

  std::shared_ptr<Token> Tokenizer::parse_identifier() {
    std::stringstream stream;

    int sline = line;
    int scol = column;

    // Consuming and appending alphanumeric characters
    stream << walk([](char ch) { return std::isalnum(ch) || ch == '_'; });

    // Checking if the identifier is a keyword
    std::string value = stream.str();
    for (const auto &pair : TOKEN_STR) {
      if (pair.second == value) {
        return create_token(pair.first, value, sline, scol);
      }
    }

    return create_token(TokenType::IDENTIFIER, value, sline, scol);
  }

  std::shared_ptr<Token> Tokenizer::parse_symbol() {
    char current_char = current();
    char next_char = peek();

    auto sline = line;
    auto scol = column;

    // Helper to map a character to a token type
    std::unordered_map<char, TokenType> conversion = {
        {'+', TokenType::PLUS},
        {'-', TokenType::MINUS},
        {'*', TokenType::STAR},
        {'/', TokenType::SLASH},
        {'%', TokenType::PERCENT},
        {'(', TokenType::LPAREN},
        {')', TokenType::RPAREN},
        {'{', TokenType::LBRACE},
        {'}', TokenType::RBRACE},
        {'[', TokenType::LBRACKET},
        {']', TokenType::RBRACKET},
        {';', TokenType::SEMICOLON},
        {':', TokenType::COLON},
        {',', TokenType::COMMA},
        {'.', TokenType::DOT},
        {'=', (peek() == '=') ? TokenType::EQUAL : TokenType::ASSIGN},
        {'!', (peek() == '=') ? TokenType::NOT_EQUAL : TokenType::INVALID},
        {'<', (peek() == '=') ? TokenType::LESS_EQUAL : TokenType::LESS},
        {'>', (peek() == '=') ? TokenType::GREATER_EQUAL : TokenType::GREATER}};

    auto it = conversion.find(current_char);
    TokenType type = (it != conversion.end()) ? it->second : TokenType::INVALID;

    std::string value = std::string(1, current_char);

    if (type != TokenType::INVALID) {
      advance();

      // Consume the next character if it's a double-character token
      if (type == TokenType::EQUAL || type == TokenType::NOT_EQUAL ||
          type == TokenType::LESS_EQUAL || type == TokenType::GREATER_EQUAL) {
        advance();
        return create_token(type, value + next_char, sline, scol);
      }
    }

    return create_token(type, value, sline, scol);
  }

}  // namespace excerpt
