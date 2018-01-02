#include "ControlDataBuilder.h"

namespace udp_reciever {
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

  bool ControlDataBuilder::isReadyToBuild(QDataStream &ds, const qint32 size)
  {
    auto remainDataSize = size;
    quint32 h;
    qint32 len;
    QByteArray data;
    if(remainDataSize < 4) return false;
    ds >> h;
    remainDataSize -= 4;

    if(remainDataSize < 4) return false;
    ds >> len;
    remainDataSize -= 4;

    if(remainDataSize < len) return false;
    data.resize(len);
    ds >> data;

    return true;
  }
}