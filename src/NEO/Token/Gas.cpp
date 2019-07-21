// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <list>

#include "../../Data.h"
#include "../ParamsBuilder.h"
#include "Gas.h"

using namespace TW;
using namespace TW::NEO;
using namespace TW::NEO::Token;

Transaction Gas::withdraw(const Signer &claimer, const Address &receiver, uint64_t amount,
                          const Signer &payer, uint64_t gasPrice, uint64_t gasLimit,
                          uint32_t nonce) {
    auto ontContract = Address("AFmseVrdL9f9oyCzZefL9tG6UbvhUMqNMV");
    std::list<boost::any> args{claimer.getAddress().bytes, ontContract.bytes, receiver.bytes, amount};
    auto invokeCode = ParamsBuilder::buildNativeInvokeCode(contractAddress(), 0x00, "transferFrom", args);
    auto tx = Transaction(getVersion(), txType, nonce, gasPrice, gasLimit, payer.getAddress().string(), invokeCode);
    claimer.sign(tx);
    payer.addSign(tx);
    return tx;
}