// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

import TrustWalletCore
import XCTest

class NEOAddressTests: XCTestCase {

    func testInvalid() {
        XCTAssertNil(NEOAddress(string: "abc"))
        XCTAssertNil(NEOAddress(string: "dshadghasdghsadadsadjsad"))
    }

    func testIsValid() {
        XCTAssertFalse(NEOAddress.isValidString(string: "abc"))
        XCTAssertFalse(NEOAddress.isValidString(string: "0x5aAeb6053F3E94C9b9A09f33669435E7Ef1BeAed"))
        XCTAssertTrue(NEOAddress.isValidString(string: "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD"))
    }

    func testFromPublicKey() {
        let publicKey = PublicKey(data: Data(hexString: "031bec1250aa8f78275f99a6663688f31085848d0ed92f1203e447125f927b7486")!, type: .nist256p1)!
        let address = NEOAddress(publicKey: publicKey)
        XCTAssertEqual(address.description, "AeicEjZyiXKgUeSBbYQHxsU1X3V5Buori5")
    }

    func testFromPrivateKey() {
        let privateKey = PrivateKey(data: Data(hexString: "4cbd05e59cbe5faba43bbf5a15fdaf27ad72c232f8d88d987c6b3d4d98300af5")!)!
        let address = NEOAddress(publicKey: privateKey.getPublicKeyNist256p1())
        XCTAssertEqual(address.description, "AH11LGtFk6VU9Z7suuM5eNpho1bAoE5Gbz")
    }

    func testDescription() {
        let address = NEOAddress(string: "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD")!
        XCTAssertEqual(address.description, "ANDfjwrUroaVtvBguDtrWKRMyxFwvVwnZD")
    }

    func testFromPrivateKey2() {
        let key = PrivateKey(data: Data(hexString: "4646464646464646464646464646464646464646464646464646464646464646")!)!
        let pubkey = key.getPublicKeySecp256k1(compressed: true)
        let address = NEOAddress(publicKey: pubkey)
        XCTAssertEqual(address.description, "AKyqorS5EiAEz9XpmBGrFCyhNURS82TRQz")
    }

    func testFromPrivateKey3() {
        let key = PrivateKey(data: Data(hexString: "9c3d42d0515f0406ed350ab2abf3eaf761f8907802469b64052ac17e2250ae13")!)!
        let pubkey = key.getPublicKeySecp256k1(compressed: true)
        let address = NEOAddress(publicKey: pubkey)
        XCTAssertEqual(address.description, "ARjxtNSEJt9LE4TJUob5yM8UBtopQvuBrK")
    }
}
