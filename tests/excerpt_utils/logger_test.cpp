#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "excerpt_utils/logger.hpp"

std::string captureStdout(const std::function<void()>& testFunction) {
  std::ostringstream oss;
  std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
  testFunction();
  std::cout.rdbuf(oldCout);
  return oss.str();
}

TEST(LoggerTest, DebugMessage) {
  std::string output =
      captureStdout([]() { excerpt::logger::debug("Debug message"); });

  std::string expectedLogLevel = "DEBUG";
  std::string expectedMessage = "Debug message";

  EXPECT_THAT(output, testing::HasSubstr(expectedLogLevel));
  EXPECT_THAT(output, testing::HasSubstr(expectedMessage));
}

TEST(LoggerTest, InfoMessage) {
  std::string output =
      captureStdout([]() { excerpt::logger::info("Info message"); });

  std::string expectedLogLevel = "INFO";
  std::string expectedMessage = "Info message";

  EXPECT_THAT(output, testing::HasSubstr(expectedLogLevel));
  EXPECT_THAT(output, testing::HasSubstr(expectedMessage));
}

TEST(LoggerTest, WarningMessage) {
  std::string output =
      captureStdout([]() { excerpt::logger::warn("Warning message"); });

  std::string expectedLogLevel = "WARNING";
  std::string expectedMessage = "Warning message";

  EXPECT_THAT(output, testing::HasSubstr(expectedLogLevel));
  EXPECT_THAT(output, testing::HasSubstr(expectedMessage));
}

TEST(LoggerTest, ErrorMessage) {
  std::string output =
      captureStdout([]() { excerpt::logger::error("Error message"); });

  std::string expectedLogLevel = "ERROR";
  std::string expectedMessage = "Error message";

  EXPECT_THAT(output, testing::HasSubstr(expectedLogLevel));
  EXPECT_THAT(output, testing::HasSubstr(expectedMessage));
}
