/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECEIVER_UDPRECEIVER_H_
#define UDP_RECEIVER_UDPRECEIVER_H_

#include <QObject>
#include <QtNetwork>
#include <QSharedPointer>
#include "Sequencer.h"

namespace udp_receiver {
class UdpReceiver : public QObject {
  Q_OBJECT

 public:
    explicit UdpReceiver(QObject *parent = 0);
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
}  // namespace udp_receiver
#endif  // UDP_RECEIVER_UDPRECEIVER_H_
