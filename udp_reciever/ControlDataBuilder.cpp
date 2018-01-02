#include "ControlDataBuilder.h"

namespace udp_reciever {
  ControlDataBuilder::ControlDataBuilder(const QByteArray &datagram)
  {
    QDataStream qDS(datagram);
    qDS >> header;
    qDS >> dataSize;
    qDS >> payload;
  }

  bool ControlDataBuilder::canBuildControlData(QDataStream &ds, const qint32 size)
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

  quint32 ControlDataBuilder::getHeader()
  {
    return header;
  }
}