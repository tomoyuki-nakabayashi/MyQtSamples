#ifndef SRC_UDP_PACKET_H_
#define SRC_UDP_PACKET_H_

#include <QObject>
#include <QDataStream>

namespace udp_reciever {
  struct ControlData {
    quint32 header;
    qint32 payloadSize;
    QByteArray payload;
    explicit ControlData(QDataStream &ds) {
      ds >> header;
      ds >> payloadSize;
      payload.resize(payloadSize);
      ds >> payload;
    }
  };

  class ControlDataBuilder : public QObject
  {
    Q_OBJECT

    public:
      ControlDataBuilder();
      explicit ControlDataBuilder(const QByteArray &datagram);
      static bool canBuildControlData(QDataStream &ds, const qint32 size);
      quint32 getHeader();
    private:
      quint32 header;
      quint32 dataSize;
      QByteArray payload;
  };
}
#endif //SRC_UDP_PACKET_H_