// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "../../Data.h"
#include "../ParamsBuilder.h"
#include "Neo.h"

#include <unordered_map>

using namespace TW;
using namespace TW::NEO;
using namespace TW::NEO::Token;

Transaction Neo::decimals(uint32_t nonce) {
    auto builder = ParamsBuilder();
    auto invokeCode = ParamsBuilder::buildNativeInvokeCode(contractAddress(), getVersion(), "decimals", Data());
    auto tx = Transaction(getVersion(), txType, nonce, (uint64_t)0, (uint64_t)0, (std::string) "", invokeCode);
    return tx;
}

Transaction Neo::balanceOf(const Address &address, uint32_t nonce) {
    auto builder = ParamsBuilder();
    auto invokeCode = ParamsBuilder::buildNativeInvokeCode(contractAddress(), getVersion(), "balanceOf", address.bytes);
    auto tx = Transaction(getVersion(), txType, nonce, (uint64_t)0, (uint64_t)0, (std::string) "", invokeCode);
    return tx;
}

Transaction Neo::transfer(const Signer &from, const Address &to, uint64_t amount,
                          const Signer &payer, uint64_t gasPrice, uint64_t gasLimit,
                          uint32_t nonce) {
    std::list<boost::any> transferParam{from.getAddress().bytes, to.bytes, amount};
    std::vector<boost::any> args{transferParam};
    auto invokeCode = ParamsBuilder::buildNativeInvokeCode(contractAddress(), getVersion(), "transfer", args);
    auto tx = Transaction(getVersion(), txType, nonce, gasPrice, gasLimit, payer.getAddress().string(), invokeCode);
    from.sign(tx);
    payer.addSign(tx);
    return tx;
}
