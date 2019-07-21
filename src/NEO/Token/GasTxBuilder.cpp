// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "GasTxBuilder.h"

using namespace TW;
using namespace TW::NEO;
using namespace TW::NEO::Token;

Data GasTxBuilder::withdraw(const NEO::Proto::SigningInput &input) {
    auto payer = Signer(PrivateKey(input.payer_private_key()));
    auto owner = Signer(PrivateKey(input.owner_private_key()));
    auto toAddress = Address(input.to_address());
    auto transaction = Gas().withdraw(owner, toAddress, input.amount(), payer, input.gas_price(),
                                      input.gas_limit(), input.nonce());
    auto encoded = transaction.serialize();
    return encoded;
}

Data GasTxBuilder::build(const NEO::Proto::SigningInput &input) {
    auto method = std::string(input.method().begin(), input.method().end());
    if (method == "withdraw") {
        return GasTxBuilder::withdraw(input);
    }
    return NeoTxBuilder::build(input);
}

std::unique_ptr<Asset> GasTxBuilder::createAsset() {
    return std::unique_ptr<Asset>(new Gas());
}
