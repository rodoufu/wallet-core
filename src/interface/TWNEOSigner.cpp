// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <memory>
#include <unordered_map>
#include <TrustWalletCore/TWNEOSigner.h>

#include "../NEO/Token/GasTxBuilder.h"
#include "../NEO/Token/NeoTxBuilder.h"

using namespace std;
using namespace TW;
using namespace TW::NEO;
using namespace TW::NEO::Token;

TW_NEO_Proto_SigningOutput TWNEOSignerSign(TW_NEO_Proto_SigningInput data) {
    Proto::SigningInput input;
    input.ParseFromArray(TWDataBytes(data), static_cast<int>(TWDataSize(data)));
    auto contract = std::string(input.contract().begin(), input.contract().end());
    auto output = Proto::SigningOutput();

    unordered_map<std::string, unique_ptr<TxBuilder>> contractTxBuilder;
    contractTxBuilder.emplace("NEO", std::unique_ptr<TxBuilder>(new NeoTxBuilder()));
//    contractTxBuilder.emplace("GAS", std::unique_ptr<TxBuilder>(new GasTxBuilder()));

    if (contractTxBuilder.find(contract) != contractTxBuilder.end()) {
        auto encoded = contractTxBuilder[contract]->build(input);
        output.set_encoded(encoded.data(), encoded.size());
    }

    auto serialized = output.SerializeAsString();
    return TWDataCreateWithBytes(reinterpret_cast<const uint8_t *>(serialized.data()), serialized.size());
}
