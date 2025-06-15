#include "../include/utils/saveTif.hpp"

#include <format>

#include "../include/utils/utils.hpp"
#include "tiffio.h"

void saveTif_R16UI(
  const char* path,
  const u32& width,
  const u32& height,
  const u16* pixels
) {
  TIFF* tif = TIFFOpen(path, "w");
  if (!tif)
    error(std::format("tif can't open file [{}]\n", path));

  TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);
  TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);
  TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
  TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 16);
  TIFFSetField(tif, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_UINT);
  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

  for (u32 row = 0; row < height; row++) {
    const u16* rowPtr = pixels + row * width;

    if (TIFFWriteScanline(tif, (void*)rowPtr, row) < 0) {
      printf("Failed to write scanline, row: [%i]\n", row);
      TIFFClose(tif);
      exit(1);
    }
  }

  TIFFClose(tif);
}

