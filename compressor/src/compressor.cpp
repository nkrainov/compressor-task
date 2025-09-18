#include <spdlog/spdlog.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <libcompressor/libcompressor.hpp>

/**
 * @brief Здесь происходит сжатие входящей строки по соотвутствующему алгоритму и её вывод на экран.
 *
 * Ожидает, что первым параметром программе передается тип сжатия (zlib/bzip).
 * Вторым - строка для сжатия.
 */
int main(int argc, char** argv) {
  if (argc != 3) {
    spdlog::error("compressor need 2 argument");
    std::exit(EXIT_FAILURE);
  }

  if (std::strcmp(argv[1], "zlib") != 0 && std::strcmp(argv[1], "bzip") != 0) {
    spdlog::error("User must use zlib or bzip only");
    std::exit(EXIT_FAILURE);
  }

  libcompressor_CompressionAlgorithm algo;
  if (std::strcmp(argv[1], "zlib") == 0)
    algo = libcompressor_CompressionAlgorithm::libcompressor_Zlib;
  else
    algo = libcompressor_CompressionAlgorithm::libcompressor_Blib;

  libcompressor_Buffer input = {argv[2], static_cast<int>(std::strlen(argv[2]))};

  libcompressor_Buffer output = libcompressor_compress(algo, input);

  if (output.size == 0 && output.data == NULL) {
    spdlog::error("error occurred during compression");
    std::exit(EXIT_FAILURE);
  }

  for (int i = 0; i < output.size; i++) {
    std::printf("%.2hhx", output.data[i]);
  }

  std::printf("\n");

  std::exit(EXIT_SUCCESS);
}