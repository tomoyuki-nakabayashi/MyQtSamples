#ifndef SRC_UDP_PACKET_H_
#define SRC_UDP_PACKET_H_

#include <QObject>
#include <QDataStream>

namespace udp_reciever {
  struct ControlData {
    quint32 header;
    qint32 payloadSize;
    QByteArray payload;
    ControlData(quint32 h, qint32 s, QByteArray p)
      : header{h}, payloadSize(s), payload(p) {}
  };

  class ControlDataBuilder : public QObject
  {
    Q_OBJECT

    public:
      ControlDataBuilder() {}
      bool isReadyToBuild(QDataStream &ds, const qint32 size);
      ControlData build(QDataStream &ds);
  };
}
#endif //SRC_UDP_PACKET_H_