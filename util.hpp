// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

extern "C"
{
#include <keccak/KeccakHash.h>
}
//#include "address.h"

#include <limits>
//#include <nlohmann/json.hpp>
#include <sstream>
#include <vector>

namespace evm
{
  inline void Keccak_256(
    const unsigned char* input,
    unsigned int inputByteLen,
    unsigned char* output)
  {
    // Ethereum started using Keccak and called it SHA3 before it was finalised.
    // Standard SHA3-256 (the FIPS accepted version) uses padding 0x06, but
    // Ethereum's "Keccak-256" uses padding 0x01.
    // All other constants are copied from Keccak_HashInitialize_SHA3_256 in
    // KeccakHash.h.
    Keccak_HashInstance hi;
    Keccak_HashInitialize(&hi, 1088, 512, 256, 0x01);
    Keccak_HashUpdate(
      &hi, input, inputByteLen * std::numeric_limits<unsigned char>::digits);
    Keccak_HashFinal(&hi, output);
  }

  std::string strip(const std::string& s);
  std::vector<uint8_t> to_bytes(const std::string& s);
  std::string to_hex_string(const std::vector<uint8_t>& bytes);

//  Address generate_address(const Address& sender, uint64_t nonce);

} // namespace evm
