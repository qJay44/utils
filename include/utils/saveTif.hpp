#pragma once

#include "types.hpp"
#include "tiffio.h"
#include "utils.hpp"

void saveTif(
  const char* path,
  const u32& width,
  const u32& height,
  const u16& channels,
  const u16& depth,
  const u16& sampleFormat,
  const void* pixels,
  const bool& flipVertically = false
);

void saveTif_R16UI(
  const char* path,
  const u32& width,
  const u32& height,
  const u16* pixels,
  const bool& flipVertically = false
);

void saveTif_R32UI(
  const char* path,
  const u32& width,
  const u32& height,
  const u32* pixels,
  const bool& flipVertically = false
);

template<typename T>
static void saveBuf(TIFF* tif, const u32& w, const u32& h, const void* buf, const bool& flipVertically) {
  const T* pixels = (T*)buf;

  if (flipVertically)
    for (u32 row = 0; row < h; row++) {
      const T* rowPtr = pixels + row * w;

      if (TIFFWriteScanline(tif, (void*)rowPtr, row) < 0)
        error("[saveBuf] Failed to write scanline, row: [{}]\n", row);
    }
  else
    for (u32 row = 0; row < h; row++) {
      const T* rowPtr = pixels + (h - 1 - row) * w;

      if (TIFFWriteScanline(tif, (void*)rowPtr, row) < 0)
        error("[saveBuf] Failed to write scanline, row: [{}]\n", row);
    }
}

