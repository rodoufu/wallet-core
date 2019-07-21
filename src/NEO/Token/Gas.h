// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "../../Data.h"
#include "Asset.h"
#include "Neo.h"

namespace TW::NEO::Token {

class Gas : public TW::NEO::Token::Neo {
  private:
    const Data gasContract = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
  public:
    uint8_t getVersion() override { return 0x00; }
    Data contractAddress() override { return gasContract; }
    Transaction withdraw(const Signer &claimer, const Address &receiver, uint64_t amount,
                         const Signer &payer, uint64_t gasPrice, uint64_t gasLimit, uint32_t nonce);
    ~Gas() {}
};

} // namespace TW::NEO
