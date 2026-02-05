#include "../include/utils/loadTif.hpp"

#include "../include/utils/utils.hpp"
#include <cassert>

void* loadTif(
  const char* path,
  u32* width,
  u32* height,
  u16* channels,
  u16* depth,
  u16* sampleFormat,
  bool flipVertically
) {
  assert(path);
  assert(width);
  assert(height);
  assert(channels);
  assert(depth);
  assert(sampleFormat);

  TIFF* tif = TIFFOpen(path, "r");
  if (!tif)
    error("[loadTif] Can't open file [{}]\n", path);

  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, width);
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, height);
  TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, channels);
  TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, depth);
  TIFFGetField(tif, TIFFTAG_SAMPLEFORMAT, sampleFormat); // 1 - uint, 2 - sint, 3 - float, 4 - undefined
  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

  const u32& w = *width;
  const u32& h = *height;
  const size_t nbits = *channels * *depth;
  void* buf = nullptr;

  switch (*sampleFormat) {
    case SAMPLEFORMAT_UINT:
      switch (nbits) {
        case 8:
          buf = loadBuf<u8>(tif, w, h, flipVertically);
          break;
        case 16:
          buf = loadBuf<u16>(tif, w, h, flipVertically);
          break;
        case 32:
          buf = loadBuf<u32>(tif, w, h, flipVertically);
          break;
        default:
          error("[loadTif] Unexpected number of bits [{} x {}] (channels x depth)", *channels, *depth);
      }
    case SAMPLEFORMAT_INT:
      switch (nbits) {
        case 8:
          buf = loadBuf<s8>(tif, w, h, flipVertically);
          break;
        case 16:
          buf = loadBuf<s16>(tif, w, h, flipVertically);
          break;
        case 32:
          buf = loadBuf<s32>(tif, w, h, flipVertically);
          break;
        default:
          error("[loadTif] Unexpected number of bits [{} x {}] (channels x depth)", *channels, *depth);
      }
    case SAMPLEFORMAT_IEEEFP:
      switch (nbits) {
        case 32:
          buf = loadBuf<float>(tif, w, h, flipVertically);
          break;
        case 64:
          buf = loadBuf<double>(tif, w, h, flipVertically);
          break;
        default:
          error("[loadTif] Unexpected number of bits [{} x {}] (channels x depth)", *channels, *depth);
      }
    case SAMPLEFORMAT_VOID:
      error("[loadTif] Undefined sample format");
  }

  TIFFClose(tif);

  return buf;
}

s16* loadTif_R16I(
  const char* path,
  u32* width,
  u32* height,
  bool flipVertically
) {

  assert(path);
  assert(width);
  assert(height);

  TIFF* tif = TIFFOpen(path, "r");
  if (!tif)
    error("[loadTif_R16I] Can't open file [{}]\n", path);

  u16 channels, depth, sampleFormat;

  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, width);
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, height);
  TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &channels);
  TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &depth);
  TIFFGetField(tif, TIFFTAG_SAMPLEFORMAT, &sampleFormat); // 1 - uint, 2 - sint, 3 - float, 4 - undefined
  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

  if (channels != 1)     error("[loadTif_R16UI] Unexpected number of channels [{}]", channels);
  if (depth != 16)       error("[loadTif_R16UI] Unexpected depth [{}]", depth);
  if (sampleFormat != 2) error("[loadTif_R16UI] Unexpected sample format [{}]", sampleFormat);

  const u32& w = *width;
  const u32& h = *height;
  s16* buf = loadBuf<s16>(tif, w, h, flipVertically);

  TIFFClose(tif);

  return buf;
}

u16* loadTif_R16UI(
  const char* path,
  u32* width,
  u32* height,
  bool flipVertically
) {
  assert(path);
  assert(width);
  assert(height);

  TIFF* tif = TIFFOpen(path, "r");
  if (!tif)
    error("[loadTif_R16UI] Can't open file [{}]\n", path);

  u16 channels, depth, sampleFormat;

  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, width);
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, height);
  TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &channels);
  TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &depth);
  TIFFGetField(tif, TIFFTAG_SAMPLEFORMAT, &sampleFormat); // 1 - uint, 2 - sint, 3 - float, 4 - undefined
  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

  if (channels != 1)     error("[loadTif_R16UI] Unexpected number of channels [{}] ({})", channels, path);
  if (depth != 16)       error("[loadTif_R16UI] Unexpected depth [{}] ({})", depth, path);
  if (sampleFormat != 1) error("[loadTif_R16UI] Unexpected sample format [{}] ({})", sampleFormat, path);

  const u32& w = *width;
  const u32& h = *height;
  u16* buf = loadBuf<u16>(tif, w, h, flipVertically);

  TIFFClose(tif);

  return buf;
}

