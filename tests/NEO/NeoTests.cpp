// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <string>
#include <boost/any.hpp>
#include <gtest/gtest.h>

#include "NEO/Token/Neo.h"
#include "HexCoding.h"

using namespace TW;
using namespace TW::NEO;
using namespace TW::NEO::Token;

TEST(NEONeo, decimals) {
    uint32_t nonce = 0;
    auto tx = Neo().decimals(nonce);
    auto rawTx = hex(tx.serialize());
    EXPECT_EQ("00d100000000000000000000000000000000000000001700000000000000000000000000000000000000"
              "00330008646563696d616c731400000000000000000000000000000000000000010068114e454f2e4e61"
              "746976652e496e766f6b650000",
              rawTx);
}

TEST(NEONeo, queryBalance) {
    uint32_t nonce = 0;
    auto address = Address("ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD");
    auto tx = Neo().balanceOf(address, nonce);
    auto rawTx = hex(tx.serialize());
    EXPECT_EQ("00d100000000000000000000000000000000000000001700000000000000000000000000000000000000"
              "0049151746b1a18af6b7c9f8a4602f9f73eeb3030f0c29b70962616c616e63654f661400000000000000"
              "000000000000000000000000010068114e454f2e4e61746976652e496e766f6b650000",
              rawTx);
}

TEST(NEONeo, transfer) {
    auto signer1 = Signer(
        PrivateKey(parse_hex("4646464646464646464646464646464646464646464646464646464646464646")));
    auto signer2 = Signer(
        PrivateKey(parse_hex("4646464646464646464646464646464646464646464646464646464646464652")));
    auto toAddress = Address("Af1n2cZHhMZumNqKgw9sfCNoTWu9de4NDn");
    uint32_t nonce = 0;
    uint64_t amount = 1, gasPrice = 500, gasLimit = 20000;
    auto tx = Neo().transfer(signer1, toAddress, amount, signer2, gasPrice, gasLimit, nonce);
    auto rawTx = hex(tx.serialize());
    EXPECT_EQ("00d100000000f401000000000000204e0000000000001757e9d1a61f9aafa798b6c7fbeae35639681d7d"
              "f66e00c66b1517fbacc8214765d457c8e3f2b5a1d3c4981a2e9d2a6a7ccb1517feec06b79ed299ea06fc"
              "b94abac41aaf3ead76586a7ccb516a7ccb6c51c1087472616e7366657214000000000000000000000000"
              "00000000000000010068114e454f2e4e61746976652e496e766f6b6500024140fd7de8935dcf501ac72b"
              "3afd131c4815e123c7860a59e7c5c9cd870ca88560c523f8023c9f6f34ad250408c79006d7e70829637c"
              "237c95c0c6ad22b8e08f99b12321031bec1250aa8f78275f99a6663688f31085848d0ed92f1203e44712"
              "5f927b7486ac414017faf4f698d1ff7d518d40df0fad54c316201ba40916519508e29496b5c2b7040a97"
              "b7494c8cbe997a09d86bd6042b069fa167462ac396eef003f84f2a826364232103d9fd62df332403d911"
              "4f3fa3da0d5aec9dfa42948c2f50738d52470469a1a1eeac",
              rawTx);
}
