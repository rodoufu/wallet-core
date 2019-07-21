// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <gtest/gtest.h>

#include "NEO/Address.h"
#include "NEO/ParamsBuilder.h"
#include "NEO/Token/Neo.h"
#include "HexCoding.h"
#include "PublicKey.h"

using namespace TW;
using namespace TW::NEO;
using namespace TW::NEO::Token;

TEST(NEOParamsBuilder, pushInt) {
    std::vector<uint64_t> numVector{0,
                                    1,
                                    2,
                                    127,
                                    128,
                                    129,
                                    65534,
                                    65535,
                                    65536,
                                    65537,
                                    4294967294,
                                    4294967295,
                                    4294967296,
                                    68719476735,
                                    68719476736,
                                    72057594037927935,
                                    1152921504606846975};
    std::vector<std::string> codeVector{"00",
                                        "51",
                                        "52",
                                        "017f",
                                        "028000",
                                        "028100",
                                        "03feff00",
                                        "03ffff00",
                                        "03000001",
                                        "03010001",
                                        "05feffffff00",
                                        "05ffffffff00",
                                        "050000000001",
                                        "05ffffffff0f",
                                        "050000000010",
                                        "08ffffffffffffff00",
                                        "08ffffffffffffff0f"};
    for (auto index = 0; index < numVector.size(); index++) {
        auto builder = ParamsBuilder();
        builder.push(numVector[index]);
        EXPECT_EQ(codeVector[index], hex(builder.getBytes()));
    }
}

TEST(NEOParamsBuilder, balanceInvokeCode) {
    auto balanceParam = Address("ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD").bytes;
    auto invokeCode = ParamsBuilder::buildNativeInvokeCode(Neo().contractAddress(), 0x00, "balanceOf", balanceParam);
    auto hexInvokeCode =
        "151746b1a18af6b7c9f8a4602f9f73eeb3030f0c29b70962616c616e63654f6614000000000000000000000000"
        "00000000000000010068114e454f2e4e61746976652e496e766f6b65";
    EXPECT_EQ(hexInvokeCode, hex(invokeCode));
}

TEST(NEOParamsBuilder, transferInvokeCode) {
    auto fromAddress = Address("ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD").bytes;
    auto toAddress = Address("Af1n2cZHhMZumNqKgw9sfCNoTWu9de4NDn").bytes;
    uint64_t amount = 1;
    std::list<boost::any> transferParam{fromAddress, toAddress, amount};
    std::vector<boost::any> args{transferParam};
    auto invokeCode =
        ParamsBuilder::buildNativeInvokeCode(Neo().contractAddress(), 0x00, "transfer", args);
    auto hexInvokeCode =
        "00c66b151746b1a18af6b7c9f8a4602f9f73eeb3030f0c29b76a7ccb1517feec06b79ed299ea06fcb94abac41a"
        "af3ead76586a7ccb516a7ccb6c51c1087472616e73666572140000000000000000000000000000000000000001"
        "0068114e454f2e4e61746976652e496e766f6b65";
    EXPECT_EQ(hexInvokeCode, hex(invokeCode));
}
