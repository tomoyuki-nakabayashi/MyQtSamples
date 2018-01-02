#ifndef SRC_UDP_PACKET_H_
#define SRC_UDP_PACKET_H_

#include <QObject>
#include <QDataStream>

namespace udp_reciever {
  class ControlData : public QObject
  {
    Q_OBJECT

    public:
      ControlData();
      explicit ControlData(const QByteArray &datagram);
      static bool canBuildControlData(QDataStream &ds, const qint32 size);
      quint32 getHeader();
    private:
      quint32 header;
      quint32 dataSize;
      quint32 payload;
  };
}
#endif //SRC_UDP_PACKET_H_