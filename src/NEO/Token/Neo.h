// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "../../Data.h"
#include "Asset.h"

namespace TW::NEO::Token {

class Neo : public Asset {
  private:
    static const uint8_t version = 0x00;
    const Data neoContract = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
  public:
    uint8_t getVersion() override { return 0x00; }
    Data contractAddress() override { return neoContract; }
    Transaction decimals(uint32_t nonce) override;
    Transaction balanceOf(const Address &address, uint32_t nonce) override;
    Transaction transfer(const Signer &from, const Address &to, uint64_t amount,
                         const Signer &payer, uint64_t gasPrice, uint64_t gasLimit,
                         uint32_t nonce) override;
    ~Neo() {}
};

} // namespace TW::NEO
