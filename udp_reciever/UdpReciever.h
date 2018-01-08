/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_UDPRECIEVER_H_
#define UDP_RECIEVER_UDPRECIEVER_H_

#include <QObject>
#include <QtNetwork>
#include <QSharedPointer>
#include "Sequencer.h"

namespace udp_reciever {
class UdpReciever : public QObject {
  Q_OBJECT

 public:
    explicit UdpReciever(QObject *parent = 0);
    bool InitSocket(const QHostAddress &address, quint16 port = 0);

signals:
    void DataRecieved(QSharedPointer<Frame> frame);

 private slots:
    void ProcessPendingDatagrams();
    void onFrameConstructed(QSharedPointer<Frame> frame);

 private:
    QUdpSocket udp_socket_;
    Sequencer sequencer_;

};
}  // namespace udp_reciever
#endif  // UDP_RECIEVER_UDPRECIEVER_H_
