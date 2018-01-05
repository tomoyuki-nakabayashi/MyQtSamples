/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_FRAMEBUILDER_H_
#define UDP_RECIEVER_FRAMEBUILDER_H_

#include <QObject>
#include <QDataStream>

namespace udp_reciever {
class Frame {
 private:
    const quint32 header;
    const qint32 payloadSize;
    const QByteArray payload;

 public:
    static const quint32 kHeaderMagic = 0x01234567;

 public:
    Frame(): header(), payloadSize(), payload() {}
    Frame(quint32 h, qint32 s, QByteArray p)
      : header{h}, payloadSize{s}, payload{p} {}
    Frame(const Frame &other)
      : header{other.header},
        payloadSize{other.payloadSize},
        payload{other.payload} {}

    quint32 GetHeader() const {return header;}
    qint32 GetPayloadSize() const {return payloadSize;}
    QByteArray GetPayload() const {return payload;}
};

enum class FrameBuilderStatus {READY = 0, INVALID = -1, RETRY = -2};

class FrameBuilder : public QObject {
  Q_OBJECT

 public:
    FrameBuilder() {}
    FrameBuilderStatus IsReadyToBuild(QDataStream &ds, const qint32 size);
    Frame Build(QDataStream &ds);
};
}  // namespace udp_reciever
#endif  // UDP_RECIEVER_FRAMEBUILDER_H_
