#include "../include/utils/loadTif.hpp"

#include <format>

#include "../include/utils/utils.hpp"
#include "tiffio.h"

s16* loadTif_R16I(
  const char* path,
  u32* width,
  u32* height,
  bool flipVertically
) {
  TIFF* tif = TIFFOpen(path, "r");
  if (!tif)
    error(std::format("tif can't open file [{}]\n", path));

  u16 channels, depth, sampleFormat;

  if (width)        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, width);
  if (height)       TIFFGetField(tif, TIFFTAG_IMAGELENGTH, height);
  TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &channels);
  TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &depth);
  TIFFGetField(tif, TIFFTAG_SAMPLEFORMAT, &sampleFormat); // 1 - uint, 2 - sint, 3 - float, 4 - undefined
  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

  if (channels != 1)     error(std::format("[loadTif_R16UI] Unexpected number of channels [{}]", channels));
  if (depth != 16)       error(std::format("[loadTif_R16UI] Unexpected depth [{}]", depth));
  if (sampleFormat != 2) error(std::format("[loadTif_R16UI] Unexpected sample format [{}]", sampleFormat));

  const u32& w = *width;
  const u32& h = *height;
  s16* buf = new s16[w * h];

  for (u32 row = 0; row < h; row++) {
    s16* bufRow = buf + row * w;

    if (TIFFReadScanline(tif, bufRow, row) < 0) {
      puts("tif scanline read error");
      exit(1);
    }
  }

  if (flipVertically)
    for (u32 y = 0; y < h / 2; ++y) {
      s16* rowTop = buf + y * w;
      s16* rowBottom = buf + (h- y - 1) * w;
      std::swap_ranges(rowTop, rowTop + w, rowBottom);
    }

  return buf;

  TIFFClose(tif);
}


u16* loadTif_R16UI(
  const char* path,
  u32* width,
  u32* height,
  bool flipVertically
) {
  TIFF* tif = TIFFOpen(path, "r");
  if (!tif)
    error(std::format("tif can't open file [{}]\n", path));

  u16 channels, depth, sampleFormat;

  if (width)        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, width);
  if (height)       TIFFGetField(tif, TIFFTAG_IMAGELENGTH, height);
  TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &channels);
  TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &depth);
  TIFFGetField(tif, TIFFTAG_SAMPLEFORMAT, &sampleFormat); // 1 - uint, 2 - sint, 3 - float, 4 - undefined
  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

  if (channels != 1)     error(std::format("[loadTif_R16UI] Unexpected number of channels [{}]", channels));
  if (depth != 16)       error(std::format("[loadTif_R16UI] Unexpected depth [{}]", depth));
  if (sampleFormat != 1) error(std::format("[loadTif_R16UI] Unexpected sample format [{}]", sampleFormat));

  const u32& w = *width;
  const u32& h = *height;
  u16* buf = new u16[w * h];

  for (u32 row = 0; row < h; row++) {
    u16* bufRow = buf + row * w;

    if (TIFFReadScanline(tif, bufRow, row) < 0) {
      puts("tif scanline read error");
      exit(1);
    }
  }

  if (flipVertically)
    for (u32 y = 0; y < h / 2; ++y) {
      u16* rowTop = buf + y * w;
      u16* rowBottom = buf + (h- y - 1) * w;
      std::swap_ranges(rowTop, rowTop + w, rowBottom);
    }

  return buf;

  TIFFClose(tif);
}

