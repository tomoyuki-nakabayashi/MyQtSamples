/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_SUBFRAMEBUILDER_H_
#define UDP_RECIEVER_SUBFRAMEBUILDER_H_

#include <QObject>
#include <QDataStream>

namespace udp_reciever {
  struct SubFrame {
    const quint32 header;
    const qint32 payloadSize;
    const QByteArray payload;
    SubFrame(): header(), payloadSize(), payload() {}
    SubFrame(quint32 i, qint32 s, QByteArray p)
      : header{i}, payloadSize(s), payload(p) {}
  };

  class SubFrameBuilder : public QObject
  {
    Q_OBJECT

    public:
      SubFrameBuilder() {}
  };
}  // udp_reciever
#endif  // UDP_RECIEVER_SUBFRAMEBUILDER_H_