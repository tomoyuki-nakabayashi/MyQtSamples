/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "Frame.h"

namespace udp_receiver {
using udp_receiver::Frame;
QDataStream& operator <<(QDataStream& os, const Frame& f) {
  os << f.header << f.payload_size;
  for (auto b : f.payload)
    os << static_cast<quint8>(b);
  return os;
}

quint32 ParseUInt32(const char (&buf)[4]) {
  // This prevents buf[i] from being promoted to a signed int.
  quint32 u0 = buf[0], u1 = buf[1], u2 = buf[2], u3 = buf[3];
  quint32 uval = u3 | (u2 << 8) | (u1 << 16) | (u0 << 24);
  return uval;
}

QDataStream& operator >>(QDataStream& is, Frame& f) {
  f.status = FrameStatus::NO_ERROR;
  char buff[4];
  auto res = is.readRawData(buff, 4);
  if (res < 4) {
    f.status = FrameStatus::RETRY;
    return is;
  }
  f.header = (ParseUInt32(buff));
  if (f.header != Frame::kHeaderMagic) {
    f.status = FrameStatus::INVALID;
    return is;
  }

  res = is.readRawData(buff, 4);
  if (res < 4) {
    f.status = FrameStatus::RETRY;
    return is;
  }
  f.payload_size = (static_cast<quint32>(ParseUInt32(buff)));
  
  QScopedPointer<char> payload_buff(new char[f.payload_size]);
  res = is.readRawData(payload_buff.data(), f.payload_size);
  if (res < f.payload_size) {
    f.status = FrameStatus::RETRY;
    return is;
  }
  f.payload = QByteArray(payload_buff.data(), f.payload_size);
  f.frame_size = sizeof(f.header) + sizeof(f.payload_size) + f.payload_size;
  return is;
}
}  // namespace udp_receiver