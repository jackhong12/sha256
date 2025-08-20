#include <cstddef>
#include <string>
#include <vector>

class SHA256 {
  typedef unsigned int word;

public:
  SHA256(const unsigned char *Data, size_t Len) {
    std::vector<unsigned char> PaddingData = padding(Data, Len);

    for (size_t i = 0; i < PaddingData.size(); i += 64) {
      std::vector<word> W(64, 0);

      // Load the first 16 words from the padding data
      for (size_t j = 0; j < 16; ++j)
        for (size_t k = 0; k < 4; ++k)
          W[j] |=
              (static_cast<word>(PaddingData[i + j * 4 + k]) << (24 - k * 8));

      // Extend the first 16 words into the remaining 48 words
      for (size_t j = 16; j < 64; ++j) {
        word s0 = (W[j - 15] >> 7) ^ (W[j - 15] >> 18) ^ (W[j - 15] >> 3);
        word s1 = (W[j - 2] >> 17) ^ (W[j - 2] >> 19) ^ (W[j - 2] >> 10);
        W[j] = W[j - 16] + s0 + W[j - 7] + s1;
      }

      update(W);
    }
  }

  std::string digest() const {
    std::string result;
    result.reserve(32);
    for (size_t i = 0; i < 8; ++i) {
      for (int j = 3; j >= 0; --j) {
        result += static_cast<char>((H[i] >> (j * 8)) & 0xff);
      }
    }
    return result;
  }

private:
  void update(std::vector<word> &W) {
    word a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6],
         h = H[7];

    for (size_t j = 0; j < 64; ++j) {
      word S0 = (a >> 2) ^ (a >> 13) ^ (a >> 22);
      word maj = (a & b) ^ (a & c) ^ (b & c);
      word temp2 = S0 + maj;
      word S1 = (e >> 6) ^ (e >> 11) ^ (e >> 25);
      word ch = (e & f) ^ (~e & g);
      word temp1 = h + S1 + ch + K[j] + W[j];

      h = g;
      g = f;
      f = e;
      e = d + temp1;
      d = c;
      c = b;
      b = a;
      a = temp1 + temp2;
    }

    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
    H[5] += f;
    H[6] += g;
    H[7] += h;
  }

  std::vector<unsigned char> padding(const unsigned char *Data, size_t Len) {
    size_t PaddingLen = Len + 9;
    if (PaddingLen % 64 != 0)
      PaddingLen += 64 - (PaddingLen % 64);

    std::vector<unsigned char> PaddingData(PaddingLen, 0);
    for (size_t i = 0; i < Len; ++i)
      PaddingData[i] = Data[i];

    PaddingData[Len] = 0x80; // Append a single '1' bit (0x80 in hex)

    int Offset = 0;
    while (Len) {
      // Append the length of the original data in bits
      PaddingData[PaddingLen - 1 - Offset] = Len & 0xff;
      Len >>= 8;
    }

    return PaddingData;
  }

  word H[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
               0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

  const word K[64] = {
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
      0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
      0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
      0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
      0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
      0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
      0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
      0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
      0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
      0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
};
