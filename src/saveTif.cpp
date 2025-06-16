#include "../include/utils/saveTif.hpp"

#include "../include/utils/utils.hpp"

void saveTif(
  const char* path,
  const u32& width,
  const u32& height,
  const u16& channels,
  const u16& depth,
  const u16& sampleFormat,
  const void* pixels
) {
  TIFF* tif = TIFFOpen(path, "r");
  if (!tif)
    error("[saveTif] Can't open file [{}]", path);

  TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);
  TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);
  TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, channels);
  TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, depth);
  TIFFSetField(tif, TIFFTAG_SAMPLEFORMAT, sampleFormat); // 1 - uint, 2 - sint, 3 - float, 4 - undefined
  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

  const size_t nbits = channels * depth;
  switch (sampleFormat) {
    case SAMPLEFORMAT_UINT:
      switch (nbits) {
        case 8:
          saveBuf<u8>(tif, width, height, pixels);
          break;
        case 16:
          saveBuf<u16>(tif, width, height, pixels);
          break;
        case 32:
          saveBuf<u32>(tif, width, height, pixels);
          break;
        default:
          error("[saveTif] Unexpected number of bits [{} x {}] (channels x depth)", channels, depth);
      }
    case SAMPLEFORMAT_INT:
      switch (nbits) {
        case 8:
          saveBuf<s8>(tif, width, height, pixels);
          break;
        case 16:
          saveBuf<s16>(tif, width, height, pixels);
          break;
        case 32:
          saveBuf<s32>(tif, width, height, pixels);
          break;
        default:
          error("[saveTif] Unexpected number of bits [{} x {}] (channels x depth)", channels, depth);
      }
    case SAMPLEFORMAT_IEEEFP:
      switch (nbits) {
        case 32:
          saveBuf<float>(tif, width, height, pixels);
          break;
        case 64:
          saveBuf<double>(tif, width, height, pixels);
          break;
        default:
          error("[saveTif] Unexpected number of bits [{} x {}] (channels x depth)", channels, depth);
      }
    case SAMPLEFORMAT_VOID:
      error("[saveTif] Undefined sample format");
  }

  TIFFClose(tif);
}

void saveTif_R16UI(
  const char* path,
  const u32& width,
  const u32& height,
  const u16* pixels
) {
  TIFF* tif = TIFFOpen(path, "w");
  if (!tif)
    error("[saveTif_R16UI] Can't open file [{}]", path);

  TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);
  TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);
  TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
  TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 16);
  TIFFSetField(tif, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_UINT);
  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

  saveBuf<u16>(tif, width, height, pixels);

  TIFFClose(tif);
}

