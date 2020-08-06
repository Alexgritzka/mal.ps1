#include <cstdio>
#include "aes.h"

const char EXT[] = ".gelo";
const size_t ENCRYPTION_LENGTH = 8192;

const unsigned char key[] = {0x73, 0x68, 0x30, 0x77, 0x63, 0x34, 0x73, 0x33,
                             0x38, 0x61, 0x34, 0x65, 0x34, 0x31, 0x33, 0x33,
                             0x62, 0x62, 0x63, 0x65, 0x32, 0x65, 0x61, 0x32,
                             0x33, 0x31, 0x35, 0x61, 0x31, 0x39, 0x31, 0x36};

const unsigned char iv[] = {0x0a, 0x95, 0xbd, 0x4f, 0xcc, 0x8b, 0xdf, 0xef,
                            0xcf, 0xd5, 0x50, 0x82, 0x3e, 0x0d, 0x85, 0x29,
                            0x26, 0x1b, 0xb8, 0xb5, 0x49, 0xa0, 0x12, 0x96,
                            0x58, 0x4e, 0xba, 0x35, 0x30, 0xea, 0xa7, 0xb1};

bool encrypt_file(const char* src_file) {
  char dst_file[strlen(src_file) + strlen(EXT) + 1];
  strcpy(dst_file, src_file);
  strcat(dst_file, EXT);

  AES aes(256);
  FILE* infile = std::fopen(src_file, "rb");
  if (infile == NULL) {
    return false;
  }
  std::fseek(infile, 0, SEEK_END);
  size_t size = std::ftell(infile);
  std::fseek(infile, 0, SEEK_SET);

  unsigned char buffer[size];
  std::fread(buffer, size, 1, infile);
  std::fclose(infile);

  unsigned int outLen = size;
  unsigned char* c = aes.EncryptCFB(
          &buffer[0],
          size,
          const_cast<unsigned char *>(key),
          const_cast<unsigned char *>(iv),
          outLen);

  FILE* outfile = std::fopen(dst_file, "wb");
  std::fwrite(c, outLen, 1, outfile);
  std::fclose(outfile);

  return true;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "enter argument" << std::endl;
    return 1;
  }

  const char* path = argv[1];
  encrypt_file(path);

  return 0;
}
