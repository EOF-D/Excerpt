#include <gtest/gtest.h>
#include "excerpt/tokenizer.hpp"

using namespace excerpt;

TEST(TokenizerTest, ParseNumber) {
  Tokenizer tokenizer(std::make_shared<std::string>("123 3.14"));
  auto token = tokenizer.next();

  EXPECT_EQ(token->type, TokenType::INTEGER_LITERAL);
  EXPECT_EQ(token->value, "123");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::FLOAT_LITERAL);
  EXPECT_EQ(token->value, "3.14");
}

TEST(TokenizerTest, ParseString) {
  Tokenizer tokenizer(std::make_shared<std::string>("\"Hello, World!\""));
  auto token = tokenizer.next();

  EXPECT_EQ(token->type, TokenType::STRING_LITERAL);
  EXPECT_EQ(token->value, "Hello, World!");
}

TEST(TokenizerTest, ParseIdentifier) {
  Tokenizer tokenizer(std::make_shared<std::string>("variable_name"));
  auto token = tokenizer.next();

  EXPECT_EQ(token->type, TokenType::IDENTIFIER);
  EXPECT_EQ(token->value, "variable_name");
}

TEST(TokenizerTest, ParseSymbolSingle) {
  Tokenizer tokenizer(std::make_shared<std::string>("+-*/%(){}[];:,."));
  auto token = tokenizer.next();

  EXPECT_EQ(token->type, TokenType::PLUS);
  EXPECT_EQ(token->value, "+");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::MINUS);
  EXPECT_EQ(token->value, "-");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::STAR);
  EXPECT_EQ(token->value, "*");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::SLASH);
  EXPECT_EQ(token->value, "/");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::PERCENT);
  EXPECT_EQ(token->value, "%");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::LPAREN);
  EXPECT_EQ(token->value, "(");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::RPAREN);
  EXPECT_EQ(token->value, ")");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::LBRACE);
  EXPECT_EQ(token->value, "{");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::RBRACE);
  EXPECT_EQ(token->value, "}");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::LBRACKET);
  EXPECT_EQ(token->value, "[");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::RBRACKET);
  EXPECT_EQ(token->value, "]");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::SEMICOLON);
  EXPECT_EQ(token->value, ";");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::COLON);
  EXPECT_EQ(token->value, ":");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::COMMA);
  EXPECT_EQ(token->value, ",");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::DOT);
  EXPECT_EQ(token->value, ".");
}

TEST(TokenizerTest, ParseSymbolDouble) {
  Tokenizer tokenizer(std::make_shared<std::string>("== != <= >= < >"));

  auto token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::EQUAL);
  EXPECT_EQ(token->value, "==");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::NOT_EQUAL);
  EXPECT_EQ(token->value, "!=");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::LESS_EQUAL);
  EXPECT_EQ(token->value, "<=");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::GREATER_EQUAL);
  EXPECT_EQ(token->value, ">=");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::LESS);
  EXPECT_EQ(token->value, "<");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::GREATER);
  EXPECT_EQ(token->value, ">");
}
