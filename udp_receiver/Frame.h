/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECEIVER_FRAME_H_
#define UDP_RECEIVER_FRAME_H_

#include <QByteArray>
#include <QDataStream>
#include <QMetaType>
#include <QSharedPointer>
#include <QScopedPointer>

namespace udp_receiver {
constexpr qint32 sizeofquint32() {return static_cast<int>(sizeof(quint32));}
constexpr qint32 sizeofqint32() {return static_cast<int>(sizeof(qint32));}
enum class FrameStatus {NO_ERROR = 0, READY = 1, INVALID = -1, RETRY = -2};
enum class FrameBuilderStatus {NO_ERROR = 0, READY = 1, INVALID = -1, RETRY = -2};

struct Frame {
    quint32 header;
    qint32 payload_size;
    QByteArray payload;
    FrameBuilderStatus status;
    qint32 frame_size;

 public:
    static const quint32 kHeaderMagic = 0x01234567;

 public:
    Frame(): header(), payload_size(), payload() {}
    Frame(quint32 h, qint32 s, QByteArray p)
      : header{h}, payload_size{s}, payload(p) {}
    Frame(const Frame &other)
      : header{other.header},
        payload_size{other.payload_size},
        payload(other.payload) {}
    bool operator==(const Frame &rhs) const { 
      return (header == rhs.header) && (payload_size == rhs.payload_size) && (payload == rhs.payload); 
    }
    bool operator!=(const Frame &rhs) const { return !(*this == rhs); }

    qint32 GetFrameSize() const {return sizeof(header) + sizeof(payload_size) + payload_size;}
};

inline QDataStream& operator <<(QDataStream& os, const Frame& f) {
  os << f.header << f.payload_size;
  for (auto b : f.payload)
    os << static_cast<quint8>(b);
  return os;
}

inline quint32 ParseUInt32(const char (&buf)[4]) {
  // This prevents buf[i] from being promoted to a signed int.
  quint32 u0 = buf[0], u1 = buf[1], u2 = buf[2], u3 = buf[3];
  quint32 uval = u3 | (u2 << 8) | (u1 << 16) | (u0 << 24);
  return uval;
}

inline QDataStream& operator >>(QDataStream& is, Frame& f) {
  f.status = FrameBuilderStatus::NO_ERROR;
  char buff[4];
  auto res = is.readRawData(buff, 4);
  if (res < 4) {
    f.status = FrameBuilderStatus::RETRY;
    return is;
  }
  f.header = (ParseUInt32(buff));
  if (f.header != Frame::kHeaderMagic) {
    f.status = FrameBuilderStatus::INVALID;
    return is;
  }

  res = is.readRawData(buff, 4);
  if (res < 4) {
    f.status = FrameBuilderStatus::RETRY;
    return is;
  }
  f.payload_size = (static_cast<quint32>(ParseUInt32(buff)));
  
  QScopedPointer<char> payload_buff(new char[f.payload_size]);
  res = is.readRawData(payload_buff.data(), f.payload_size);
  if (res < f.payload_size) {
    f.status = FrameBuilderStatus::RETRY;
    return is;
  }
  f.payload = QByteArray(payload_buff.data(), f.payload_size);
  f.frame_size = sizeof(f.header) + sizeof(f.payload_size) + f.payload_size;
  return is;
}
}  // namespace udp_receiver

Q_DECLARE_METATYPE(QSharedPointer<udp_receiver::Frame>)
#endif  // UDP_RECEIVER_FRAME_H_