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
  const void* pixels
);

void saveTif_R16UI(
  const char* path,
  const u32& width,
  const u32& height,
  const u16* pixels
);

template<typename T>
static void saveBuf(TIFF* tif, const u32& w, const u32& h, const void* buf) {
  const T* pixels = (T*)buf;
  for (u32 row = 0; row < h; row++) {
    const T* rowPtr = pixels + row * w;

    if (TIFFWriteScanline(tif, (void*)rowPtr, row) < 0)
      error("Failed to write scanline, row: [%i]\n", row);
  }
}

