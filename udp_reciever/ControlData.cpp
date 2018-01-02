#include "ControlData.h"

namespace udp_reciever {
  ControlData::ControlData(const QByteArray &datagram)
  {
    QDataStream qDS(datagram);
    qDS >> header;
    qDS >> dataSize;
    qDS >> payload;
  }

  bool ControlData::canBuildControlData(QDataStream &ds, const qint32 size)
  {
    auto remainDataSize = size;
    quint32 h, len, data;
    if(remainDataSize <= 4) return false;
    ds >> h;
    remainDataSize -= 4;

    if(remainDataSize <= 4) return false;
    ds >> len;
    remainDataSize -= 4;

    ds >> data;

    return true;
  }

  quint32 ControlData::getHeader()
  {
    return header;
  }
}