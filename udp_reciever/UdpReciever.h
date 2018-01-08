/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_UDPRECIEVER_H_
#define UDP_RECIEVER_UDPRECIEVER_H_

#include <QObject>
#include <QtNetwork>
#include <QSharedPointer>
#include "BaseFrameBuilder.h"
#include "Frame.h"

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

 private:
    enum class Sequence {RECOVERING = -1, FRAME = 0, SUB_FRAME = 1, UNCHANGED};
    Sequence state_;
    QUdpSocket udp_socket_;
    QSharedPointer<BaseFrameBuilder> builder_;

 private:
    void ChangeSequence(Sequence next);
    Sequence GetNextState();
};
}  // namespace udp_reciever
#endif  // UDP_RECIEVER_UDPRECIEVER_H_
