// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Address.h"

#include "Tezos/BinaryCoding.h"
#include "../Base58.h"
#include "../Hash.h"
#include "../Ontology/ParamsBuilder.h"

using namespace TW::NEO;

bool Address::isValid(const std::string& string) {
    const auto decoded = Base58::bitcoin.decodeCheck(string);
    return !(decoded.size() != Address::size || decoded[0] != version);
}

Address::Address(const PublicKey& publicKey) {
    auto publicKeyData = publicKey.bytes;

    auto pkdata = Data(publicKeyData.begin(), publicKeyData.end());
    pkdata.insert(pkdata.begin(), 0x21);
    pkdata.push_back(0xAC);

    auto keyHash = Hash::ripemd(Hash::sha256(pkdata));
    keyHash.insert(keyHash.begin(), 0x17);

    if (keyHash.size() != Address::size) {
        throw std::invalid_argument("Invalid address key data");
    }

    std::copy(keyHash.data(), keyHash.data() + Address::size, bytes.begin());
}

Address::Address(uint8_t m, const std::vector<Data>& publicKeys) {
    auto builderData = toScriptHash(Ontology::ParamsBuilder::fromMultiPubkey(m, publicKeys));
    std::copy(builderData.begin(), builderData.end(), bytes.begin());
}

Data Address::toScriptHash(const Data& data) const {
    return Hash::ripemd(Hash::sha256(data));
}
