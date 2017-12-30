#ifndef SRC_UDP_H
#define SRC_UDP_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QUdpSocket;
QT_END_NAMESPACE

namespace udp_reciever {
  class UdpReciever : public QObject
  {
    Q_OBJECT

  public:
    explicit UdpReciever(QObject *parent = 0);
/* 
  private slots:
    void processPendingDatagrams();
 */
  private:
    QUdpSocket *udpSocket;
  };
}
#endif //SRC_UDP_H
