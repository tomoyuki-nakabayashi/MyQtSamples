#ifndef SRC_UDP_PACKET_H_
#define SRC_UDP_PACKET_H_

#include <QObject>

namespace udp_reciever {
  class ControlData : public QObject
  {
    Q_OBJECT

    public:
      ControlData();
  };
}
#endif //SRC_UDP_PACKET_H_