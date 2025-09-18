#include <bzlib.h>
#include <zlib.h>

#include <cstdlib>
#include <libcompressor/libcompressor.hpp>

/**
 * @brief Функция сжатия с помощью bzip
 *
 * @param input буфер для сжатия
 *
 * @return сжатый с помощью bzip
 */
libcompressor_Buffer libcompress_compress_Blib(libcompressor_Buffer input) {
  libcompressor_Buffer ret = {NULL, 0};
  char* data = (char*)std::malloc(input.size + 1024);
  unsigned int size;

  int err = BZ2_bzBuffToBuffCompress(data, &size, input.data, input.size, 1, 0, 0);
  if (err != BZ_OK) {
    std::free(data);
    return ret;
  }

  ret.data = data;
  ret.size = size;
  return ret;
}

/**
 * @brief Функция сжатия с помощью zlib
 *
 * @param input буфер для сжатия
 *
 * @return сжатый с помощью zlib
 */
libcompressor_Buffer libcompress_compress_Zlib(libcompressor_Buffer input) {
  libcompressor_Buffer ret = {NULL, 0};
  Bytef* data = (Bytef*)std::malloc(input.size + 1024);
  uLong size;

  int err = compress(data, &size, (Bytef*)input.data, input.size);
  if (err != Z_OK) {
    std::free(data);
    return ret;
  }

  ret.data = (char*)data;
  ret.size = size;
  return ret;
}

/**
 * @brief Функция сжатия
 *
 * Сжимает входной буфер по переданному алгоритму.
 *
 * @param algo алгоритм сжатия (zlib/bzip)
 * @param input входной буфер
 *
 * @return буфер со сжатой строкой
 */
libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input) {
  libcompressor_Buffer ret = {NULL, 0};

  if (input.size == 0) {
    return ret;
  }

  switch (algo) {
    case libcompressor_CompressionAlgorithm::libcompressor_Blib:
      ret = libcompress_compress_Blib(input);
      break;
    case libcompressor_CompressionAlgorithm::libcompressor_Zlib:
      ret = libcompress_compress_Zlib(input);
      break;
    default:
      break;
  }

  return ret;
}