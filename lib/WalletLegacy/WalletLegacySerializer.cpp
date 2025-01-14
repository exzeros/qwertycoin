// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018, Karbo developers
// Copyright (c) 2018-2023, The Qwertycoin Group.
//
// This file is part of Qwertycoin.
//
// Qwertycoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Qwertycoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Qwertycoin.  If not, see <http://www.gnu.org/licenses/>.

#include <stdexcept>
#include <Common/MemoryInputStream.h>
#include <Common/StdInputStream.h>
#include <Common/StdOutputStream.h>
#include <CryptoNoteCore/Account.h>
#include <CryptoNoteCore/CryptoNoteSerialization.h>
#include <Serialization/BinaryOutputStreamSerializer.h>
#include <Serialization/BinaryInputStreamSerializer.h>
#include <Serialization/SerializationOverloads.h>
#include <Wallet/WalletErrors.h>
#include <Wallet/WalletUtils.h>
#include <WalletLegacy/KeysStorage.h>
#include <WalletLegacy/WalletLegacySerializer.h>
#include <WalletLegacy/WalletUserTransactionsCache.h>

using namespace Common;

namespace CryptoNote {

uint32_t WALLET_LEGACY_SERIALIZATION_VERSION = 3;

WalletLegacySerializer::WalletLegacySerializer(CryptoNote::AccountBase &account,
                                               WalletUserTransactionsCache &transactionsCache)
    : account(account),
      transactionsCache(transactionsCache),
      walletSerializationVersion(3)
{
}

void WalletLegacySerializer::serialize(std::ostream &stream,
    const std::string &password,
    bool saveDetailed,
    const std::string &cache,
    const std::vector<Crypto::Hash> &safeTxes)
{
    // set serialization version global variable
    CryptoNote::WALLET_LEGACY_SERIALIZATION_VERSION = walletSerializationVersion;

    std::stringstream plainArchive;
    StdOutputStream plainStream(plainArchive);
    CryptoNote::BinaryOutputStreamSerializer serializer(plainStream);
    saveKeys(serializer);

    serializer(saveDetailed, "has_details");

    if (saveDetailed) {
        serializer(transactionsCache, "details");
    }

    serializer.binary(const_cast<std::string &>(cache), "cache");
    if (walletSerializationVersion >= 3) {
        uint32_t consolidateHeight = transactionsCache.getConsolidateHeight();
        serializer(consolidateHeight, "consolidate_height");
        Crypto::Hash consolidateTx = transactionsCache.getConsolidateTx();
        serializer(consolidateTx, "consolidate_tx_id");
        consolidateHeight = transactionsCache.getPrevConsolidateHeight();
        serializer(consolidateHeight, "prev_consolidate_height");
        consolidateTx = transactionsCache.getPrevConsolidateTx();
        serializer(consolidateTx, "prev_consolidate_tx_id");
        size_t s = safeTxes.size();
        serializer.beginArray(s, "safe_txes");
        for(auto h: safeTxes)
           serializer.binary(&h, sizeof(h), "");
        serializer.endArray();
    }

    std::string plain = plainArchive.str();
    std::string cipher;

    Crypto::chacha8_iv iv = encrypt(plain, password, cipher);

    uint32_t version = walletSerializationVersion;
    StdOutputStream output(stream);
    CryptoNote::BinaryOutputStreamSerializer s(output);
    s.beginObject("wallet");
    s(version, "version");
    s(iv, "iv");
    s(cipher, "data");
    s.endObject();

    stream.flush();
}

void WalletLegacySerializer::saveKeys(CryptoNote::ISerializer &serializer)
{
    CryptoNote::KeysStorage keys;
    CryptoNote::AccountKeys acc = account.getAccountKeys();

    keys.creationTimestamp = account.get_createtime();
    keys.spendPublicKey = acc.address.spendPublicKey;
    keys.spendSecretKey = acc.spendSecretKey;
    keys.viewPublicKey = acc.address.viewPublicKey;
    keys.viewSecretKey = acc.viewSecretKey;

    keys.serialize(serializer, "keys");
}

Crypto::chacha8_iv WalletLegacySerializer::encrypt(
    const std::string &plain,
    const std::string &password,
    std::string &cipher)
{
    Crypto::chacha8_key key;
    Crypto::cn_context context;
    Crypto::generate_chacha8_key(context, password, key);

    cipher.resize(plain.size());

    Crypto::chacha8_iv iv = Crypto::rand<Crypto::chacha8_iv>();
    Crypto::chacha8(plain.data(), plain.size(), key, iv, &cipher[0]);

    return iv;
}

void WalletLegacySerializer::deserialize(std::istream &stream,
    const std::string &password,
    std::string &cache,
    std::vector<Crypto::Hash> &safeTxes)
{
    StdInputStream stdStream(stream);
    CryptoNote::BinaryInputStreamSerializer serializerEncrypted(stdStream);

    serializerEncrypted.beginObject("wallet");

    uint32_t version;
    serializerEncrypted(version, "version");
    // set serialization version global variable
    CryptoNote::WALLET_LEGACY_SERIALIZATION_VERSION = version;

    Crypto::chacha8_iv iv;
    serializerEncrypted(iv, "iv");

    std::string cipher;
    serializerEncrypted(cipher, "data");

    serializerEncrypted.endObject();

    std::string plain;
    decrypt(cipher, plain, iv, password);

    MemoryInputStream decryptedStream(plain.data(), plain.size());
    CryptoNote::BinaryInputStreamSerializer serializer(decryptedStream);

    loadKeys(serializer);
    throwIfKeysMissmatch(
        account.getAccountKeys().viewSecretKey,
        account.getAccountKeys().address.viewPublicKey
    );

    if (account.getAccountKeys().spendSecretKey != NULL_SECRET_KEY) {
        throwIfKeysMissmatch(
            account.getAccountKeys().spendSecretKey,
            account.getAccountKeys().address.spendPublicKey
        );
    } else {
        if (!Crypto::check_key(account.getAccountKeys().address.spendPublicKey)) {
            throw std::system_error(make_error_code(CryptoNote::error::WRONG_PASSWORD));
        }
    }

    bool detailsSaved;

    serializer(detailsSaved, "has_details");

    if (detailsSaved) {
        serializer(transactionsCache, "details");
    }

    serializer.binary(cache, "cache");
    if (version >= 3) {
        uint32_t consolidateHeight = 0;
        serializer(consolidateHeight, "consolidate_height");
        Crypto::Hash consolidateTx;
        serializer(consolidateTx, "consolidate_tx_id");
        transactionsCache.setConsolidateHeight(consolidateHeight, consolidateTx);
        serializer(consolidateHeight, "prev_consolidate_height");
        serializer(consolidateTx, "prev_consolidate_tx_id");
        transactionsCache.setPrevConsolidateHeight(consolidateHeight, consolidateTx);
        size_t s = 0;
        serializer.beginArray(s, "safe_txes");
        safeTxes.resize(s);
        for(size_t idx = 0; idx < s; idx++) {
            serializer.binary(&safeTxes[idx], sizeof(safeTxes[idx]), "");
        }
        serializer.endArray();
    }
}

void WalletLegacySerializer::decrypt(
    const std::string &cipher,
    std::string &plain,
    Crypto::chacha8_iv iv,
    const std::string &password)
{
    Crypto::chacha8_key key;
    Crypto::cn_context context;
    Crypto::generate_chacha8_key(context, password, key);

    plain.resize(cipher.size());

    Crypto::chacha8(cipher.data(), cipher.size(), key, iv, &plain[0]);
}

void WalletLegacySerializer::loadKeys(CryptoNote::ISerializer &serializer)
{
    CryptoNote::KeysStorage keys;

    try {
        keys.serialize(serializer, "keys");
    } catch (const std::runtime_error &) {
        throw std::system_error(make_error_code(CryptoNote::error::WRONG_PASSWORD));
    }

    CryptoNote::AccountKeys acc;
    acc.address.spendPublicKey = keys.spendPublicKey;
    acc.spendSecretKey = keys.spendSecretKey;
    acc.address.viewPublicKey = keys.viewPublicKey;
    acc.viewSecretKey = keys.viewSecretKey;

    account.setAccountKeys(acc);
    account.set_createtime(keys.creationTimestamp);
}

} // namespace CryptoNote
