#include <gtest/gtest.h>
#include "SHA256.h"

TEST(SHA256Test, EmptyString) {
  std::string input = "";
  SHA256 sha256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size());
  std::string expected = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
  EXPECT_EQ(sha256.digest(), expected);
}
