// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "NeoTxBuilder.h"

using namespace TW;
using namespace TW::NEO;
using namespace TW::NEO::Token;

Data NeoTxBuilder::decimals(const NEO::Proto::SigningInput &input) {
    auto transaction = createAsset()->decimals(input.nonce());
    auto encoded = transaction.serialize();
    return encoded;
}

Data NeoTxBuilder::balanceOf(const NEO::Proto::SigningInput &input) {
    auto queryAddress = Address(input.query_address());
    auto transaction = createAsset()->balanceOf(queryAddress, input.nonce());
    auto encoded = transaction.serialize();
    return encoded;
}

Data NeoTxBuilder::transfer(const NEO::Proto::SigningInput &input) {
    auto payerSigner = Signer(PrivateKey(input.payer_private_key()));
    auto fromSigner = Signer(PrivateKey(input.owner_private_key()));
    auto toAddress = Address(input.to_address());
    auto tranferTx = createAsset()->transfer(fromSigner, toAddress, input.amount(), payerSigner,
                                    input.gas_price(), input.gas_limit(), input.nonce());
    auto encoded = tranferTx.serialize();
    return encoded;
}

Data NeoTxBuilder::build(const NEO::Proto::SigningInput &input) {
    auto method = std::string(input.method().begin(), input.method().end());
    if (method == "transfer") {
        return transfer(input);
    } else if (method == "balanceOf") {
        return balanceOf(input);
    } else if (method == "decimals") {
        return decimals(input);
    }
    return Data();
}

std::unique_ptr<Asset> NeoTxBuilder::createAsset() {
    return std::unique_ptr<Asset>(new Neo());
}
