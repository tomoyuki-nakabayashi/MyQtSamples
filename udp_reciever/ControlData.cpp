#include "ControlData.h"

namespace udp_reciever {
  ControlData::ControlData(const QByteArray &datagram)
  {
    QDataStream qDS(datagram);
    qDS >> header;
    qDS >> dataSize;
    qDS >> payload;
  }

  quint32 ControlData::getHeader()
  {
    return header;
  }
}