// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <memory>
#include <TrustWalletCore/TWNEOProto.h>

#include "../../proto/NEO.pb.h"
#include "Neo.h"
#include "Asset.h"

namespace TW::NEO::Token {

class TxBuilder {
  public:
    virtual Data decimals(const NEO::Proto::SigningInput &input) = 0;
    virtual Data balanceOf(const NEO::Proto::SigningInput& input) = 0;
    virtual Data transfer(const NEO::Proto::SigningInput& input) = 0;
    virtual Data build(const NEO::Proto::SigningInput& input) = 0;
    virtual std::unique_ptr<Asset> createAsset() = 0;
    virtual ~TxBuilder() = 0;
};

} // namespace TW::NEO
