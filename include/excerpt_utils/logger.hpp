#pragma once

#include <iostream>
#include <string>
#include <ctime>

namespace excerpt::logger {

  // Log levels
  enum LogLevel { DEBUG, INFO, WARNING, ERROR };

  // Log function
  inline void log(LogLevel level, const std::string& message) {
    // Get the current time
    std::time_t currentTime = std::time(0);
    std::tm* localTime = std::localtime(&currentTime);

    // Format the timestamp
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime);

    // Define log level string and color
    const char* levelStr;
    const char* color;

    switch (level) {
      case DEBUG:
        levelStr = "DEBUG";
        color = "\033[0;37m";  // White
        break;
      case INFO:
        levelStr = "INFO";
        color = "\033[0;32m";  // Green
        break;
      case WARNING:
        levelStr = "WARNING";
        color = "\033[0;33m";  // Yellow
        break;
      case ERROR:
        levelStr = "ERROR";
        color = "\033[0;31m";  // Red
        break;
      default:
        levelStr = "UNKNOWN";
        color = "\033[0m";  // Reset color
        break;
    }

    // Print the log message with timestamp and log level to the console
    std::cout << "[" << timestamp << "] " << color << levelStr
              << "\033[0m: " << message << std::endl;
  }

  // Convenience functions for specific log levels
  inline void debug(const std::string& message) { log(DEBUG, message); }
  inline void info(const std::string& message) { log(INFO, message); }
  inline void warn(const std::string& message) { log(WARNING, message); }
  inline void error(const std::string& message) { log(ERROR, message); }

}  // namespace excerpt::logger
