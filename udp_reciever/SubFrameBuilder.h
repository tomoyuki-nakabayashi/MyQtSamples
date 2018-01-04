#ifndef UDP_RECIEVER_SUBFRAMEBUILDER_H_
#define UDP_RECIEVER_SUBFRAMEBUILDER_H_

#include <QObject>
#include <QDataStream>

namespace udp_reciever {
  struct SubFrame {
    quint32 id;
    qint32 payloadSize;
    QByteArray payload;
    SubFrame(quint32 i, qint32 s, QByteArray p)
      : id{i}, payloadSize(s), payload(p) {}
  };

  class SubFrameBuilder : public QObject
  {
    Q_OBJECT

    public:
      SubFrameBuilder() {}
  };
}  // udp_reciever
#endif  // UDP_RECIEVER_SUBFRAMEBUILDER_H_