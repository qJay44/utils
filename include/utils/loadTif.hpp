#pragma once

#include "types.hpp"
#include "tiffio.h"

[[nodiscard]]
void* loadTif(
  const char* path,
  u32* width,
  u32* height,
  u16* channels,
  u16* depth,
  u16* sampleFormat,
  bool flipVertically = false
);

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

template<typename T>
static T* loadBuf(TIFF* tif, const u32& w, const u32& h, const bool& flipVertically) {
  T* buf = new T[w * h];
  for (u32 row = 0; row < h; row++) {
    T* bufRow = buf + row * w;

    if (TIFFReadScanline(tif, bufRow, row) < 0) {
      puts("tif scanline read error");
      exit(1);
    }
  }

  if (flipVertically)
    for (u32 y = 0; y < h / 2; ++y) {
      T* rowTop = buf + y * w;
      T* rowBottom = buf + (h- y - 1) * w;
      std::swap_ranges(rowTop, rowTop + w, rowBottom);
    }

  return buf;
}
