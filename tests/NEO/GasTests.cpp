// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <string>
#include <gtest/gtest.h>

#include "NEO/Token/Gas.h"
#include "HexCoding.h"

using namespace TW;
using namespace TW::NEO;
using namespace TW::NEO::Token;

TEST(NEOGas, decimals) {
    uint32_t nonce = 0;
    auto tx = Gas().decimals(nonce);
    auto rawTx = hex(tx.serialize());
    EXPECT_EQ("00d100000000000000000000000000000000000000001700000000000000000000000000000000000000"
              "00330008646563696d616c731400000000000000000000000000000000000000020068114e454f2e4e61"
              "746976652e496e766f6b650000",
              rawTx);
}

TEST(NEOGas, balanceOf) {
    uint32_t nonce = 0;
    auto address = Address("ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD");
    auto tx = Gas().balanceOf(address, nonce);
    auto rawTx = hex(tx.serialize());
    EXPECT_EQ("00d100000000000000000000000000000000000000001700000000000000000000000000000000000000"
              "0049151746b1a18af6b7c9f8a4602f9f73eeb3030f0c29b70962616c616e63654f661400000000000000"
              "000000000000000000000000020068114e454f2e4e61746976652e496e766f6b650000",
              rawTx);
}

TEST(NEOGas, transfer) {
    auto signer1 = Signer(
        PrivateKey(parse_hex("4646464646464646464646464646464646464646464646464646464646464646")));
    auto signer2 = Signer(
        PrivateKey(parse_hex("4646464646464646464646464646464646464646464646464646464646464652")));
    auto toAddress = Address("Af1n2cZHhMZumNqKgw9sfCNoTWu9de4NDn");
    uint32_t nonce = 0;
    uint64_t amount = 1, gasPrice = 500, gasLimit = 20000;
    auto tx = Gas().transfer(signer1, toAddress, amount, signer2, gasPrice, gasLimit, nonce);
    auto rawTx = hex(tx.serialize());
    EXPECT_EQ("00d100000000f401000000000000204e0000000000001757e9d1a61f9aafa798b6c7fbeae35639681d7d"
              "f66e00c66b1517fbacc8214765d457c8e3f2b5a1d3c4981a2e9d2a6a7ccb1517feec06b79ed299ea06fc"
              "b94abac41aaf3ead76586a7ccb516a7ccb6c51c1087472616e7366657214000000000000000000000000"
              "00000000000000020068114e454f2e4e61746976652e496e766f6b6500024140c1e98c1c060f43fb1056"
              "25de670907cd5d8e99204a40f3362726b31a430b967d70d06fcd06e2ac42e176f903bc86d99ec4d827e9"
              "be06bb7c92e75ed3754c5c2a2321031bec1250aa8f78275f99a6663688f31085848d0ed92f1203e44712"
              "5f927b7486ac4140f1d0aded8254d121011bec7d1f3faa42192a0888008c7d80380785691ada03950cea"
              "fe7ab823bfd363160f5e503a0d12c6fd30ecc133c6395c81295ffb76a717232103d9fd62df332403d911"
              "4f3fa3da0d5aec9dfa42948c2f50738d52470469a1a1eeac",
              rawTx);
}

TEST(NEOGas, withdraw) {
    auto signer1 = Signer(
        PrivateKey(parse_hex("4646464646464646464646464646464646464646464646464646464646464646")));
    auto signer2 = Signer(
        PrivateKey(parse_hex("4646464646464646464646464646464646464646464646464646464646464652")));
    uint32_t nonce = 0;
    uint64_t amount = 1, gasPrice = 500, gasLimit = 20000;
    auto tx =
        Gas().withdraw(signer1, signer1.getAddress(), amount, signer2, gasPrice, gasLimit, nonce);
    auto rawTx = hex(tx.serialize());
    EXPECT_EQ(
        "00d100000000f401000000000000204e0000000000001757e9d1a61f9aafa798b6c7fbeae35639681d7df68900"
        "c66b1517fbacc8214765d457c8e3f2b5a1d3c4981a2e9d2a6a7ccb151700000000000000000000000000000000"
        "000000016a7ccb1517fbacc8214765d457c8e3f2b5a1d3c4981a2e9d2a6a7ccb516a7ccb6c0c7472616e736665"
        "7246726f6d1400000000000000000000000000000000000000020068114e454f2e4e61746976652e496e766f6b"
        "650002414054d447bbcf83d4320e88d96de5fa99e76272672727ec0ab98eab506b78403f1719e3b2916e727f62"
        "4c8bd2daccd530fdecc575d1494bc9ef70a6c8fb32f638e82321031bec1250aa8f78275f99a6663688f3108584"
        "8d0ed92f1203e447125f927b7486ac41406be49ed54d34e0c25f461605837fdf0f9cc6b39cc604849f40391313"
        "015b66d52aa858bed87227f06465ac0813a11b7d9e4c5b6f4844aee50e9cf7b24421c37f232103d9fd62df3324"
        "03d9114f3fa3da0d5aec9dfa42948c2f50738d52470469a1a1eeac",
        rawTx);
}
