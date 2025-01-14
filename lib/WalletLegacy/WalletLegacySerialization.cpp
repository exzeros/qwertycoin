// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2023, The Qwertycoin Group.
// Copyright (c) 2018, Karbo developers
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

#include <CryptoNoteCore/CryptoNoteSerialization.h>
#include <Global/Constants.h>
#include <Serialization/ISerializer.h>
#include <Serialization/SerializationOverloads.h>
#include <WalletLegacy/IWalletLegacy.h>
#include <WalletLegacy/WalletLegacySerialization.h>
#include <WalletLegacy/WalletLegacySerializer.h>
#include <WalletLegacy/WalletUnconfirmedTransactions.h>

namespace CryptoNote {

void serialize(UnconfirmedTransferDetails &utd, CryptoNote::ISerializer &serializer)
{
    serializer(utd.tx, "transaction");
    serializer(utd.amount, "amount");
    serializer(utd.outsAmount, "outs_amount");
    uint64_t time = static_cast<uint64_t>(utd.sentTime);
    serializer(time, "sent_time");
    utd.sentTime = static_cast<time_t>(time);
    uint64_t txId = static_cast<uint64_t>(utd.transactionId);
    serializer(txId, "transaction_id");
    utd.transactionId = static_cast<size_t>(txId);
    if (CryptoNote::WALLET_LEGACY_SERIALIZATION_VERSION >= 2) {
        serializer(utd.secretKey, "secret_key");
    }
}

void serialize(WalletLegacyTransaction &txi, CryptoNote::ISerializer &serializer)
{
    auto trId = static_cast<uint64_t>(txi.firstTransferId);
    serializer(trId, "first_transfer_id");
    txi.firstTransferId = static_cast<size_t>(trId);

    auto trCount = static_cast<uint64_t>(txi.transferCount);
    serializer(trCount, "transfer_count");
    txi.transferCount = static_cast<size_t>(trCount);

    serializer(txi.totalAmount, "total_amount");

    serializer(txi.fee, "fee");
    serializer(txi.hash, "hash");
    serializer(txi.isCoinbase, "is_coinbase");

    CryptoNote::serializeBlockHeight(serializer, txi.blockHeight, "block_height");

    serializer(txi.timestamp, "timestamp");
    serializer(txi.unlockTime, "unlock_time");
    serializer(txi.extra, "extra");

    if (CryptoNote::WALLET_LEGACY_SERIALIZATION_VERSION >= 2) {
        auto secretKeyRef = txi.secretKey.get();
        Crypto::SecretKey secretKey = reinterpret_cast<const Crypto::SecretKey &>(secretKeyRef);
        serializer(secretKey, "secret_key");
        txi.secretKey = secretKey;
    }

    // this field has been added later in the structure.
    // in order to not break backward binary compatibility
    // we just set it to zero
    txi.sentTime = 0;
}

void serialize(WalletLegacyTransfer &tr, CryptoNote::ISerializer &serializer)
{
    serializer(tr.address, "address");
    serializer(tr.amount, "amount");
}

} // namespace CryptoNote
