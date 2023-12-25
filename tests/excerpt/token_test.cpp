#include <gtest/gtest.h>
#include "excerpt/token.hpp"

using namespace excerpt;

TEST(TokenTest, ConstructionAndStringRepresentation) {
  const std::pair<TokenType, std::string> testCases[] = {
      {TokenType::PLUS, "+"},
      {TokenType::MINUS, "-"},
      {TokenType::STAR, "*"},
      {TokenType::SLASH, "/"},
      {TokenType::PERCENT, "%"},
      {TokenType::LPAREN, "("},
      {TokenType::RPAREN, ")"},
      {TokenType::LBRACE, "{"},
      {TokenType::RBRACE, "}"},
      {TokenType::LBRACKET, "["},
      {TokenType::RBRACKET, "]"},
      {TokenType::SEMICOLON, ";"},
      {TokenType::COLON, ":"},
      {TokenType::COMMA, ","},
      {TokenType::DOT, "."},
      {TokenType::ASSIGN, "="},
      {TokenType::EQUAL, "=="},
      {TokenType::NOT_EQUAL, "!="},
      {TokenType::LESS, "<"},
      {TokenType::LESS_EQUAL, "<="},
      {TokenType::GREATER, ">"},
      {TokenType::GREATER_EQUAL, ">="},
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
      {TokenType::IDENTIFIER, "variable"},
      {TokenType::INTEGER_LITERAL, "42"},
      {TokenType::FLOAT_LITERAL, "3.14"},
      {TokenType::CHAR_LITERAL, "'a'"},
      {TokenType::STRING_LITERAL, "\"hello\""},
      {TokenType::END, "END"},
      {TokenType::INVALID, "INVALID"}};

  for (const auto& testCase : testCases) {
    SCOPED_TRACE("Token type: " + TOKEN_STR.at(testCase.first));

    Token token(testCase.first, testCase.second);
    EXPECT_EQ(token.type, testCase.first);
    EXPECT_EQ(token.value, testCase.second);

    EXPECT_EQ(token.str(), "Token(" + TOKEN_STR.at(testCase.first) + ", " +
                               testCase.second + ")");
  }
}
