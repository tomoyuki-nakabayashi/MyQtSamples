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

struct Frame {
    quint32 header;
    qint32 payload_size;
    QByteArray payload;
    FrameStatus status;
    qint32 frame_size;
    qint32 skipped;

 public:
    static const quint32 kHeaderMagic = 0x01234567;

 public:
    explicit Frame(quint32 h = 0, qint32 s = 0, QByteArray p = {})
      : header{h}, payload_size{s}, payload(p), frame_size{}, skipped{} {}
    Frame(const Frame &other)
      : header{other.header},
        payload_size{other.payload_size},
        payload(other.payload) {}
    bool operator==(const Frame &rhs) const { 
      return (header == rhs.header) && (payload_size == rhs.payload_size) && (payload == rhs.payload); 
    }
    bool operator!=(const Frame &rhs) const { return !(*this == rhs); }

    qint32 GetFrameSize() const {return sizeof(header) + sizeof(payload_size) + payload_size + skipped;}
};

QDataStream& operator <<(QDataStream& os, const Frame& f);
QDataStream& operator >>(QDataStream& is, Frame& f);
}  // namespace udp_receiver

Q_DECLARE_METATYPE(QSharedPointer<udp_receiver::Frame>)
#endif  // UDP_RECEIVER_FRAME_H_