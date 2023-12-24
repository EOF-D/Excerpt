#include "excerpt/tokenizer.hpp"

namespace excerpt {

  Tokenizer::Tokenizer(std::shared_ptr<std::string> input)
      : input(input), position(0) {}

  std::shared_ptr<Token> Tokenizer::scan() {
    // At end of file, so produce EOF
    if (position >= input->size()) {
      return std::make_shared<Token>(TokenType::END, "");
    }

    char current = input->at(position);

    // Skip any whitespace
    while (std::isspace(current)) {
      ++position;
      if (position >= input->size()) {
        return std::make_shared<Token>(TokenType::END, "");
      }

      current = input->at(position);
    }

    if (std::isalpha(current) || current == '_') {
      return parse_ident();
    }

    if (std::isdigit(current)) {
      return parse_number();
    }

    if (current == '\'') {
      return parse_char();
    }

    if (current == '"') {
      return parse_string();
    }

    std::shared_ptr<Token> token = scan_single(current);
    if (token != nullptr) {
      return token;
    }

    // No token found, so return an invalid token
    ++position;
    return std::make_shared<Token>(TokenType::INVALID, "");
  }

  std::shared_ptr<Token> Tokenizer::scan_single(char current_char) {
    // Mapping of single-character tokens
    const std::unordered_map<char, TokenType> single_char_tokens = {
        {'+', TokenType::PLUS},     {'-', TokenType::MINUS},
        {'*', TokenType::STAR},     {'/', TokenType::SLASH},
        {'%', TokenType::PERCENT},  {'(', TokenType::LPAREN},
        {')', TokenType::RPAREN},   {'{', TokenType::LBRACE},
        {'}', TokenType::RBRACE},   {'[', TokenType::LBRACKET},
        {']', TokenType::RBRACKET}, {';', TokenType::SEMICOLON},
        {':', TokenType::COLON},    {',', TokenType::COMMA},
        {'.', TokenType::DOT},      {'=', TokenType::ASSIGN}};

    auto it = single_char_tokens.find(current_char);
    if (it != single_char_tokens.end()) {
      ++position;
      return std::make_shared<Token>(it->second, std::string(1, current_char));
    }

    return nullptr;  // No single-character token found
  }

  std::shared_ptr<Token> Tokenizer::parse_ident() {
    // Identify and extract the identifier
    size_t start_position = position;

    // Increment while the character is alphanumeric or underscore
    while (position < input->size() &&
           (std::isalnum(input->at(position)) || input->at(position) == '_')) {
      ++position;
    }

    // Extract the identifier
    std::string identifier_value =
        input->substr(start_position, position - start_position);

    TokenType identifier_type =
        TokenType::IDENTIFIER;  // Default to regular identifier

    // Define a map for keywords
    static const std::unordered_map<std::string, TokenType> keyword_map = {
        {"if", TokenType::IF},         {"else", TokenType::ELSE},
        {"while", TokenType::WHILE},   {"for", TokenType::FOR},
        {"break", TokenType::BREAK},   {"continue", TokenType::CONTINUE},
        {"return", TokenType::RETURN}, {"true", TokenType::TRUE},
        {"false", TokenType::FALSE}};

    static const std::unordered_map<std::string, TokenType> type_map = {
        {"int", TokenType::INT},
        {"float", TokenType::FLOAT},
        {"char", TokenType::CHAR},
        {"bool", TokenType::BOOL}};

    // Check if the identifier is a keyword
    auto keyword_it = keyword_map.find(identifier_value);
    if (keyword_it != keyword_map.end()) {
      identifier_type = keyword_it->second;
    }

    // Check if the identifier is a type
    auto type_it = type_map.find(identifier_value);
    if (type_it != type_map.end()) {
      identifier_type = type_it->second;
    }

    return std::make_shared<Token>(identifier_type, identifier_value);
  }

  std::shared_ptr<Token> Tokenizer::parse_number() {
    size_t start_position = position;

    while (position < input->size()) {
      char current_char = input->at(position);

      // Break if the character is not a digit or a decimal point
      if (!(std::isdigit(current_char) || current_char == '.')) {
        break;
      }

      ++position;
    }

    // Extract the number
    std::string number_value =
        input->substr(start_position, position - start_position);

    // Check if it's an integer or a float
    if (number_value.find('.') == std::string::npos) {
      return std::make_shared<Token>(TokenType::INTEGER_LITERAL, number_value);
    }

    return std::make_shared<Token>(TokenType::FLOAT_LITERAL, number_value);
  }

  std::shared_ptr<Token> Tokenizer::parse_char() {
    // Expecting the next character to be the opening single quote
    if (position >= input->size() || input->at(position) != '\'') {
      // Invalid character literal
      return std::make_shared<Token>(TokenType::INVALID, "");
    }

    // Move past the opening single quote
    ++position;

    // Check if there's a valid character
    if (position >= input->size()) {
      // Incomplete character literal
      return std::make_shared<Token>(TokenType::INVALID, "");
    }

    char char_literal = input->at(position);

    // Move past the character
    ++position;

    // Check for the closing single quote
    if (position >= input->size() || input->at(position) != '\'') {
      // Missing closing single quote
      return std::make_shared<Token>(TokenType::INVALID, "");
    }

    // Move past the closing single quote
    ++position;

    // Return the character literal token
    return std::make_shared<Token>(TokenType::CHAR_LITERAL,
                                   std::string(1, char_literal));
  }

  std::shared_ptr<Token> Tokenizer::parse_string() {
    // Expecting the next character to be the opening double quote
    if (position >= input->size() || input->at(position) != '"') {
      // Invalid string literal
      return std::make_shared<Token>(TokenType::INVALID, "");
    }

    // Move past the opening double quote
    ++position;

    size_t start_position = position;

    // Find the closing double quote
    while (position < input->size() && input->at(position) != '"') {
      // Escaped character handling can be added here if needed
      ++position;
    }

    // Check for an unterminated string literal
    if (position >= input->size()) {
      // Unterminated string literal
      return std::make_shared<Token>(TokenType::INVALID, "");
    }

    // Extract the string value
    std::string string_value =
        input->substr(start_position, position - start_position);

    // Move past the closing double quote
    ++position;

    // Return the string literal token
    return std::make_shared<Token>(TokenType::STRING_LITERAL, string_value);
  }

}  // namespace excerpt
