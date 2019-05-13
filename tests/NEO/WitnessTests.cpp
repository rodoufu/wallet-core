// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <iostream>
#include <gtest/gtest.h>

#include "ReadData.h"
#include "UInt.hpp"
#include "HexCoding.h"
#include "NEO/Witness.hpp"

using namespace std;
using namespace TW;
using namespace TW::NEO;

TEST(NEOWitness, Serialize) {
    auto witness = Witness();
    string invocationScript = "bdecbb623eee6f9ade28d5a8ff5fb3ea9c9d73af039e0286201b3b0291fb4d4a";
    string verificationScript = "cbb23e6f9ade28d5a8ff3eac9d73af039e821b1b";
    witness.invocationScript = parse_hex(invocationScript);
    witness.verificationScript = parse_hex(verificationScript);
    ASSERT_EQ("20000000" + invocationScript + "14000000" + verificationScript, hex(witness.serialize()));

    invocationScript = "bdecbb623eee6f9ade28d5a8ff5fb3ea9c9d73af039e0286201b3b0291fb4d4aba";
    verificationScript = "cbb23e6f9ade28d5a8ff3eac9d73af039e821b";
    witness.invocationScript = parse_hex(invocationScript);
    witness.verificationScript = parse_hex(verificationScript);
    ASSERT_EQ("21000000" + invocationScript + "13000000" + verificationScript, hex(witness.serialize()));
}

TEST(NEOWitness, Deserialize) {
    auto witness = Witness();
    string invocationScript = "bdecbb623eee6f9ade28d5a8ff5fb3ea9c9d73af039e0286201b3b0291fb4d4a";
    string verificationScript = "cbb23e6f9ade28d5a8ff3eac9d73af039e821b1b";
    witness.deserialize(parse_hex("20000000" + invocationScript + "14000000" + verificationScript));
    ASSERT_EQ(invocationScript, hex(witness.invocationScript));
    ASSERT_EQ(verificationScript, hex(witness.verificationScript));

    invocationScript = "bdecbb623eee6f9ade28d5a8ff5fb3ea9c9d73af039e0286201b3b0291fb4d4aba";
    verificationScript = "cbb23e6f9ade28d5a8ff3eac9d73af039e821b";
    witness.deserialize(parse_hex("21000000" + invocationScript + "13000000" + verificationScript));
    ASSERT_EQ(invocationScript, hex(witness.invocationScript));
    ASSERT_EQ(verificationScript, hex(witness.verificationScript));
}