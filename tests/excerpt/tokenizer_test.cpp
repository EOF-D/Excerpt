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

TEST(TokenizerTest, DataTypeTest) {
  std::string input = "int float char bool";
  auto tokenizer = std::make_shared<excerpt::Tokenizer>(
      std::make_shared<std::string>(input));

  // Test data type tokens
  EXPECT_EQ(tokenizer->scan()->type, excerpt::TokenType::INT);
  EXPECT_EQ(tokenizer->scan()->type, excerpt::TokenType::FLOAT);
  EXPECT_EQ(tokenizer->scan()->type, excerpt::TokenType::CHAR);
  EXPECT_EQ(tokenizer->scan()->type, excerpt::TokenType::BOOL);
  EXPECT_EQ(tokenizer->scan()->type, excerpt::TokenType::END);
}

TEST(TokenizerTest, TrueFalseTest) {
  std::string input = "true false";
  auto tokenizer = std::make_shared<excerpt::Tokenizer>(
      std::make_shared<std::string>(input));

  // Test true and false tokens
  EXPECT_EQ(tokenizer->scan()->type, excerpt::TokenType::TRUE);
  EXPECT_EQ(tokenizer->scan()->type, excerpt::TokenType::FALSE);
  EXPECT_EQ(tokenizer->scan()->type, excerpt::TokenType::END);
}

TEST(TokenTypeTest, FromString) {
  // Test known valid conversions
  EXPECT_EQ(Token::fromString("PLUS"), TokenType::PLUS);
  EXPECT_EQ(Token::fromString("MINUS"), TokenType::MINUS);
  EXPECT_EQ(Token::fromString("STAR"), TokenType::STAR);
  EXPECT_EQ(Token::fromString("SLASH"), TokenType::SLASH);
  EXPECT_EQ(Token::fromString("PERCENT"), TokenType::PERCENT);
  EXPECT_EQ(Token::fromString("LPAREN"), TokenType::LPAREN);
  EXPECT_EQ(Token::fromString("RPAREN"), TokenType::RPAREN);
  EXPECT_EQ(Token::fromString("LBRACE"), TokenType::LBRACE);
  EXPECT_EQ(Token::fromString("RBRACE"), TokenType::RBRACE);
  EXPECT_EQ(Token::fromString("LBRACKET"), TokenType::LBRACKET);
  EXPECT_EQ(Token::fromString("RBRACKET"), TokenType::RBRACKET);
  EXPECT_EQ(Token::fromString("SEMICOLON"), TokenType::SEMICOLON);
  EXPECT_EQ(Token::fromString("COLON"), TokenType::COLON);
  EXPECT_EQ(Token::fromString("COMMA"), TokenType::COMMA);
  EXPECT_EQ(Token::fromString("DOT"), TokenType::DOT);
  EXPECT_EQ(Token::fromString("ASSIGN"), TokenType::ASSIGN);
  EXPECT_EQ(Token::fromString("EQUAL"), TokenType::EQUAL);
  EXPECT_EQ(Token::fromString("NOT_EQUAL"), TokenType::NOT_EQUAL);
  EXPECT_EQ(Token::fromString("LESS"), TokenType::LESS);
  EXPECT_EQ(Token::fromString("LESS_EQUAL"), TokenType::LESS_EQUAL);
  EXPECT_EQ(Token::fromString("GREATER"), TokenType::GREATER);
  EXPECT_EQ(Token::fromString("GREATER_EQUAL"), TokenType::GREATER_EQUAL);
  EXPECT_EQ(Token::fromString("IF"), TokenType::IF);
  EXPECT_EQ(Token::fromString("ELSE"), TokenType::ELSE);
  EXPECT_EQ(Token::fromString("WHILE"), TokenType::WHILE);
  EXPECT_EQ(Token::fromString("FOR"), TokenType::FOR);
  EXPECT_EQ(Token::fromString("BREAK"), TokenType::BREAK);
  EXPECT_EQ(Token::fromString("CONTINUE"), TokenType::CONTINUE);
  EXPECT_EQ(Token::fromString("RETURN"), TokenType::RETURN);
  EXPECT_EQ(Token::fromString("TRUE"), TokenType::TRUE);
  EXPECT_EQ(Token::fromString("FALSE"), TokenType::FALSE);
  EXPECT_EQ(Token::fromString("INT"), TokenType::INT);
  EXPECT_EQ(Token::fromString("FLOAT"), TokenType::FLOAT);
  EXPECT_EQ(Token::fromString("CHAR"), TokenType::CHAR);
  EXPECT_EQ(Token::fromString("BOOL"), TokenType::BOOL);
  EXPECT_EQ(Token::fromString("IDENTIFIER"), TokenType::IDENTIFIER);
  EXPECT_EQ(Token::fromString("INTEGER_LITERAL"), TokenType::INTEGER_LITERAL);
  EXPECT_EQ(Token::fromString("FLOAT_LITERAL"), TokenType::FLOAT_LITERAL);
  EXPECT_EQ(Token::fromString("CHAR_LITERAL"), TokenType::CHAR_LITERAL);
  EXPECT_EQ(Token::fromString("STRING_LITERAL"), TokenType::STRING_LITERAL);
  EXPECT_EQ(Token::fromString("END"), TokenType::END);
  EXPECT_EQ(Token::fromString("INVALID"), TokenType::INVALID);

  // Test an unknown string (should default to INVALID)
  EXPECT_EQ(Token::fromString("UNKNOWN_TOKEN"), TokenType::INVALID);
}
