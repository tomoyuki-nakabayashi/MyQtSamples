/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_FRAMEBUILDER_H_
#define UDP_RECIEVER_FRAMEBUILDER_H_

#include <memory>
#include <QObject>
#include <QDataStream>

namespace udp_reciever {
struct Frame {
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
};

enum class FrameBuilderStatus {READY = 0, INVALID = -1, RETRY = -2};

class FrameBuilder : public QObject {
  Q_OBJECT

 public:
    FrameBuilder() {}
    FrameBuilderStatus IsReadyToBuild(QDataStream &ds, const qint32 size);
    FrameBuilderStatus Build(QDataStream &ds);
    void CreateNewFrame();
    std::shared_ptr<Frame> GetFrame();
  
 private:
    std::shared_ptr<Frame> frame_;
};
}  // namespace udp_reciever
#endif  // UDP_RECIEVER_FRAMEBUILDER_H_
