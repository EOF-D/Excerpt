#include "gtest/gtest.h"
#include "excerpt/tokenizer.hpp"

using namespace excerpt;

TEST(TokenizerTest, SingleCharacterTokens) {
  std::shared_ptr<std::string> input =
      std::make_shared<std::string>("+-*/%(){}[];:,.=");

  Tokenizer tokenizer(input);

  EXPECT_EQ(tokenizer.scan()->type, TokenType::PLUS);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::MINUS);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::STAR);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::SLASH);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::PERCENT);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::LPAREN);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::RPAREN);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::LBRACE);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::RBRACE);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::LBRACKET);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::RBRACKET);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::SEMICOLON);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::COLON);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::COMMA);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::DOT);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::ASSIGN);
}

TEST(TokenizerTest, IdentifierParsing) {
  std::shared_ptr<std::string> input =
      std::make_shared<std::string>("if while variable123 _underscore");

  Tokenizer tokenizer(input);

  EXPECT_EQ(tokenizer.scan()->type, TokenType::IF);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::WHILE);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::IDENTIFIER);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::IDENTIFIER);
}

TEST(TokenizerTest, NumberParsing) {
  std::shared_ptr<std::string> input =
      std::make_shared<std::string>("123 45.67");

  Tokenizer tokenizer(input);

  EXPECT_EQ(tokenizer.scan()->type, TokenType::INTEGER_LITERAL);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::FLOAT_LITERAL);
}

TEST(TokenizerTest, CharacterLiteralParsing) {
  std::shared_ptr<std::string> input = std::make_shared<std::string>("'a' '1'");

  Tokenizer tokenizer(input);

  EXPECT_EQ(tokenizer.scan()->type, TokenType::CHAR_LITERAL);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::CHAR_LITERAL);
}

TEST(TokenizerTest, StringLiteralParsing) {
  std::shared_ptr<std::string> input =
      std::make_shared<std::string>("\"hello world\" \"123\"");

  Tokenizer tokenizer(input);

  EXPECT_EQ(tokenizer.scan()->type, TokenType::STRING_LITERAL);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::STRING_LITERAL);
}

TEST(TokenizerTest, EOFToken) {
  std::shared_ptr<std::string> input = std::make_shared<std::string>("");
  Tokenizer tokenizer(input);
  EXPECT_EQ(tokenizer.scan()->type, TokenType::END);
}
