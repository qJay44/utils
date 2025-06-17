#pragma once

#include <string>

struct status {
public:
  status() = delete;
  static void start(const std::string& title, const std::string& what);
  static void update(const std::string& what, const bool& rightAlignment = true, const size_t width = 1);
  static void end(bool success);
};

