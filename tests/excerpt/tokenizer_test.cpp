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
  Tokenizer tokenizer(std::make_shared<std::string>(
      "variable_name _foo if else while for break continue return true false"));

  auto token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::IDENTIFIER);
  EXPECT_EQ(token->value, "variable_name");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::IDENTIFIER);
  EXPECT_EQ(token->value, "_foo");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::IF);
  EXPECT_EQ(token->value, "if");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::ELSE);
  EXPECT_EQ(token->value, "else");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::WHILE);
  EXPECT_EQ(token->value, "while");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::FOR);
  EXPECT_EQ(token->value, "for");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::BREAK);
  EXPECT_EQ(token->value, "break");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::CONTINUE);
  EXPECT_EQ(token->value, "continue");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::RETURN);
  EXPECT_EQ(token->value, "return");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::TRUE);
  EXPECT_EQ(token->value, "true");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::FALSE);
  EXPECT_EQ(token->value, "false");
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

TEST(TokenizerTest, SinglelineComment) {
  Tokenizer tokenizer(
      std::make_shared<std::string>("int x; // This is a comment\n"));

  auto token = tokenizer.next();

  EXPECT_EQ(token->type, TokenType::INT);
  EXPECT_EQ(token->value, "int");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::IDENTIFIER);
  EXPECT_EQ(token->value, "x");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::SEMICOLON);
  EXPECT_EQ(token->value, ";");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::END);
  EXPECT_EQ(token->value, "");
}

TEST(TokenizerTest, MultilineComment) {
  Tokenizer tokenizer(std::make_shared<std::string>(
      "/* This is\na multi-line\ncomment */ int y;"));

  auto token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::INT);
  EXPECT_EQ(token->value, "int");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::IDENTIFIER);
  EXPECT_EQ(token->value, "y");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::SEMICOLON);
  EXPECT_EQ(token->value, ";");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::END);
  EXPECT_EQ(token->value, "");
}

TEST(TokenizerTest, CommentsWithCode) {
  Tokenizer tokenizer(std::make_shared<std::string>(
      "int /* Comment */ z; // Another comment\n"));

  auto token = tokenizer.next();

  EXPECT_EQ(token->type, TokenType::INT);
  EXPECT_EQ(token->value, "int");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::IDENTIFIER);
  EXPECT_EQ(token->value, "z");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::SEMICOLON);
  EXPECT_EQ(token->value, ";");

  token = tokenizer.next();
  EXPECT_EQ(token->type, TokenType::END);
  EXPECT_EQ(token->value, "");
}
