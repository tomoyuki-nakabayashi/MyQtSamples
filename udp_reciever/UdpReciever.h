#ifndef SRC_UDP_H_
#define SRC_UDP_H_

#include <QObject>
#include <QtNetwork>
#include "ControlDataBuilder.h"

namespace udp_reciever {
  class UdpReciever : public QObject
  {
    Q_OBJECT

  public:
    explicit UdpReciever(QObject *parent = 0): QObject(parent), udpSocket(), builder() {};
    bool initSocket(const QHostAddress &address, quint16 port = 0);

  private slots:
    void processPendingDatagrams();

  signals:
    void dataRecieved(const ControlData &data);

  private:
    QUdpSocket udpSocket;
    ControlDataBuilder builder;
  };
}
#endif //SRC_UDP_H_
