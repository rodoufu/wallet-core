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
#include "NeoTxBuilder.h"
#include "Gas.h"

namespace TW::NEO::Token {

class GasTxBuilder : public NeoTxBuilder {
  public:
    Data withdraw(const NEO::Proto::SigningInput& input);
    Data build(const NEO::Proto::SigningInput& input);
    std::unique_ptr<Asset> createAsset();
};

} // namespace TW::NEO
