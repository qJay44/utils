#pragma once

#include "types.hpp"

void saveTif_R16UI(
  const char* path,
  const u32& width,
  const u32& height,
  const u16* pixels
);

