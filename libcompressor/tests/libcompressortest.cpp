#include <gtest/gtest.h>
#include <stdio.h>

#include <cstring>
#include <libcompressor/libcompressor.hpp>

TEST(compressor_test, buf_is_not_empty) {
  libcompressor_Buffer buf = {(char*)"input", static_cast<int>(std::strlen("input"))};

  libcompressor_Buffer res_bzip = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Blib, buf);
  ASSERT_TRUE(res_bzip.data != NULL);

  libcompressor_Buffer res_zlib = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Zlib, buf);
  ASSERT_TRUE(res_zlib.data != NULL);
}

TEST(compressor_test, buf_is_empty) {
  libcompressor_Buffer buf = {NULL, 0};

  libcompressor_Buffer res_bzip = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Blib, buf);
  ASSERT_TRUE(res_bzip.data == NULL);

  libcompressor_Buffer res_zlib = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Zlib, buf);
  ASSERT_TRUE(res_zlib.data == NULL);
}

TEST(compressor_test, zlib_result_is_correct) {
  char* str = (char*)"test_string";
  unsigned char exp_ans[] = {
      0x78, 0x9c, 0x2b, 0x49, 0x2d, 0x2e, 0x89, 0x2f, 0x2e, 0x29, 0xca, 0xcc, 0x4b, 0x07, 0x00, 0x1c, 0x79, 0x04, 0xb7,
  };
  int size = 19;

  libcompressor_Buffer buf = {str, static_cast<int>(std::strlen(str))};

  libcompressor_Buffer res_zlib = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Zlib, buf);

  ASSERT_TRUE(res_zlib.data != NULL && res_zlib.size == size);
  for (int i = 0; i < size; i++) {
    ASSERT_TRUE(static_cast<unsigned char>(res_zlib.data[i]) == exp_ans[i]);
  }
}

TEST(compressor_test, bzip_result_is_correct) {
  char* str = (char*)"test_string";
  unsigned char exp_ans[] = {
      0x42, 0x5a, 0x68, 0x31, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0x4a, 0x7c, 0x69, 0x05, 0x00, 0x00,
      0x04, 0x83, 0x80, 0x00, 0x00, 0x82, 0xa1, 0x1c, 0x00, 0x20, 0x00, 0x22, 0x03, 0x68, 0x84, 0x30,
      0x22, 0x50, 0xdf, 0x04, 0x99, 0xe2, 0xee, 0x48, 0xa7, 0x0a, 0x12, 0x09, 0x4f, 0x8d, 0x20, 0xa0,
  };
  int size = 48;

  libcompressor_Buffer buf = {str, static_cast<int>(std::strlen(str))};

  libcompressor_Buffer res_bzip = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Blib, buf);
  ASSERT_TRUE(res_bzip.data != NULL && size == res_bzip.size);

  for (int i = 0; i < size; i++) {
    ASSERT_TRUE(static_cast<unsigned char>(res_bzip.data[i]) == exp_ans[i]);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}