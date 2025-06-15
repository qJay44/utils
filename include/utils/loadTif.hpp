#pragma once

#include "types.hpp"

[[nodiscard]]
s16* loadTif_R16I(
  const char* path,
  u32* width,
  u32* height,
  bool flipVertically = false
);

[[nodiscard]]
u16* loadTif_R16UI(
  const char* path,
  u32* width,
  u32* height,
  bool flipVertically = false
);
