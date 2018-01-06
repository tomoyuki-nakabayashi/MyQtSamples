/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_FRAME_H_
#define UDP_RECIEVER_FRAME_H_

#include <memory>
#include <QByteArray>

namespace udp_reciever {
constexpr qint32 sizeofquint32() {return static_cast<int>(sizeof(quint32));}
constexpr qint32 sizeofqint32() {return static_cast<int>(sizeof(qint32));}

class Frame {
    quint32 header_;
    qint32 payload_size_;
    QByteArray payload_;

 public:
    static const quint32 kHeaderMagic = 0x01234567;

 public:
    Frame(): header_(), payload_size_(), payload_() {}
    Frame(quint32 h, qint32 s, QByteArray p)
      : header_{h}, payload_size_{s}, payload_{p} {}
    Frame(const Frame &other)
      : header_{other.header_},
        payload_size_{other.payload_size_},
        payload_{other.payload_} {}
    bool operator==(const Frame &rhs) const { 
      return (header_ == rhs.header_) && (payload_size_ == rhs.payload_size_) && (payload_ == rhs.payload_); 
    }
    bool operator!=(const Frame &rhs) const { return !(*this == rhs); }

    quint32 GetHeader() const {return header_;}
    qint32 GetPayloadSize() const {return payload_size_;}
    QByteArray GetPayload() const {return payload_;}
    void SetHeader(quint32 h) {header_ = h;}
    void SetPayloadSize(quint32 s) {payload_size_ = s;}
    void SetPayload(QByteArray p) {payload_ = p;}
    qint32 GetFrameSize() const {return sizeof(header_) + sizeof(payload_size_) + payload_size_;}
};
}  // namespace udp_reciever

#endif  // UDP_RECIEVER_FRAME_H_