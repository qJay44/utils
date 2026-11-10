#include "../include/utils/utils.hpp"

#include <cstdlib>
#include <fstream>
#include <sstream>

#include "../include/utils/clrp.hpp"

std::string readFile(const fspath& path) {
  std::ifstream ifs(path);
  if (!ifs.is_open())
    error("[readFile] Can't open [{}]", path.string());

  std::ostringstream oss;
  oss << ifs.rdbuf();
  std::string entireFile = oss.str();

  return entireFile;
}

void printTabs(u8 n) {
  for (int i = 0; i < n; i++)
    printf("\t");
}

void error(const std::string& msg) {
  static clrp::clrp_t fmt = {
    .attr = clrp::ATTRIBUTE::BOLD,
    .fg = clrp::FG::RED,
  };
  std::string text = clrp::format(msg, fmt);
  puts(text.c_str());
  std::exit(EXIT_FAILURE);
}

void warning(const std::string& msg) {
  static clrp::clrp_t fmt = {
    .attr = clrp::ATTRIBUTE::BOLD,
    .fg = clrp::FG::YELLOW,
  };
  std::string text = clrp::format(msg, fmt);
  puts(text.c_str());
}

void dprint(const std::string& msg) {
  #ifndef NDEBUG

  static clrp::clrp_t fmt = {
    .attr = clrp::ATTRIBUTE::BOLD,
    .fg = clrp::FG::CYAN,
  };
  std::string text = clrp::format(msg, fmt);
  puts(text.c_str());

  #endif
}

