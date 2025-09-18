#pragma once

/**
 * @brief enum для описание способ сжатия
 */
enum class libcompressor_CompressionAlgorithm { libcompressor_Zlib, libcompressor_Blib };

/**
 * @brief структура для буфера для сжатия
 */
struct libcompressor_Buffer {
  char* data;
  int size;
};

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
libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input);