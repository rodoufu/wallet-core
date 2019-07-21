// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <memory>
#include <TrustWalletCore/TWNEOProto.h>

#include "../../proto/NEO.pb.h"
#include "TxBuilder.h"
#include "Neo.h"

namespace TW::NEO::Token {

class NeoTxBuilder : public TxBuilder {
  public:
    Data decimals(const NEO::Proto::SigningInput &input);
    Data balanceOf(const NEO::Proto::SigningInput& input);
    Data transfer(const NEO::Proto::SigningInput& input);
    Data build(const NEO::Proto::SigningInput& input);
    std::unique_ptr<Asset> createAsset();
};

} // namespace TW::NEO
