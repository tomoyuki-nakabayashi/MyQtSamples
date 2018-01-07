/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_UDPRECIEVER_H_
#define UDP_RECIEVER_UDPRECIEVER_H_

#include <QObject>
#include <QtNetwork>
#include "Frame.h"

namespace udp_reciever {
class UdpReciever : public QObject {
  Q_OBJECT

 public:
    explicit UdpReciever(QObject *parent = 0): QObject(parent), udp_socket_() {}
    bool InitSocket(const QHostAddress &address, quint16 port = 0);

 private slots:
    void ProcessPendingDatagrams();

 signals:
    void DataRecieved(QSharedPointer<Frame> frame);

 private:
    QUdpSocket udp_socket_;
};
}  // namespace udp_reciever
#endif  // UDP_RECIEVER_UDPRECIEVER_H_
