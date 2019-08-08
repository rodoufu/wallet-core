// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

import TrustWalletCore
import XCTest

class NEOTests: XCTestCase {

    func testBalanceOf() {

        let input = NEOSigningInput.with {
            $0.contract = "NEO"
            $0.method = "balanceOf"
            $0.queryAddress = "AbArunq3PGYmQv4xhduTKva7r2ppUqeaDi"
            $0.nonce = 3486522027
        }

        let output = NEOSigner.sign(input: input)
        let result = output.encoded.hexString
        XCTAssertEqual("", result)
    }
}
