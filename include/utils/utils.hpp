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
    dst[i] = static_cast<u16>(src[i]) * 257u; // 255 * 257 ≈ 65535
}

inline void scaleU8toU32(const u8* src, u32* dst, size_t count) {
  for (size_t i = 0; i < count; i++)
    dst[i] = static_cast<u32>(src[i]) * 16843009u;
}

inline void scaleU32toU8(const u32* src, u8* dst, size_t count) {
  for (size_t i = 0; i < count; i++)
    dst[i] = static_cast<u8>(src[i] / 16843009u); // 255 * 257 ≈ 65535
}

#ifdef UTILS_ENABLE_GLM

inline void print(const vec3& v, const std::string& name = "vec") {
  printf("%s\n", std::format("{}: {}, {}, {}", name, v.x, v.y, v.z).c_str());
}

inline void print(const vec2& v, const std::string& name = "vec") {
  printf("%s\n", std::format("{}: {}, {}", name, v.x, v.y).c_str());
}

#endif

