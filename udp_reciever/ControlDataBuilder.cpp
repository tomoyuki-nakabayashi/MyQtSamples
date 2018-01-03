#include "ControlDataBuilder.h"

namespace udp_reciever {
  constexpr qint32 sizeofquint32() {return static_cast<int>(sizeof(quint32));}
  constexpr qint32 sizeofqint32() {return static_cast<int>(sizeof(qint32));}

  ControlData ControlDataBuilder::build(QDataStream &ds)
  {
    quint32 header;
    qint32 payloadSize;
    QByteArray payload;

    ds >> header;
    ds >> payloadSize;
    payload.resize(payloadSize);
    ds >> payload;

    return ControlData(header, payloadSize, payload);
  }

  DataBuilderStatus ControlDataBuilder::isReadyToBuild(QDataStream &ds, const qint32 size)
  {
    auto remainDataSize = size;
    if(remainDataSize < sizeofquint32()) return DataBuilderStatus::RETRY;
    quint32 h;
    ds >> h;
    if(h != ControlData::kHeaderMagic) return DataBuilderStatus::INVALID;
    remainDataSize -= sizeofquint32();

    if(remainDataSize < sizeofqint32()) return DataBuilderStatus::RETRY;
    qint32 len;
    ds >> len;
    remainDataSize -= sizeofqint32();

    if(remainDataSize < len) return DataBuilderStatus::RETRY;

    return DataBuilderStatus::READY;
  }
}