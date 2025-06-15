#pragma once

#include <string>
#include <format>

#include "types.hpp"

struct RunOnce {
  template<typename T> RunOnce(T&& f) { f(); }
};

[[nodiscard]]
std::string readFile(const fspath& path);

void printTabs(u8 n);

void error(const std::string& msg);

template<typename... Args>
void error(const char* fmtMsg, Args&&... args) {
  error(std::vformat(std::string(fmtMsg), std::make_format_args(args...)));
}

void warning(const std::string& msg);

inline void scaleU8toU16(const u8* src, u16* dst, size_t count) {
  for (size_t i = 0; i < count; i++)
    dst[i] = static_cast<u16>(src[i]) * 257; // 255 * 257 ≈ 65535
}

