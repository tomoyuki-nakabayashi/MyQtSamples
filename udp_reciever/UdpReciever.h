#ifndef SRC_UDP_H_
#define SRC_UDP_H_

#include <QObject>
#include <QtNetwork>

namespace udp_reciever {
  class UdpReciever : public QObject
  {
    Q_OBJECT

  public:
    explicit UdpReciever(QObject *parent = 0): QObject(parent), udpSocket() {};
    bool initSocket(const QHostAddress &address, quint16 port = 0);

  private slots:
    void processPendingDatagrams();

  private:
    QUdpSocket udpSocket;
  };
}
#endif //SRC_UDP_H_
