/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_UDPRECIEVER_H_
#define UDP_RECIEVER_UDPRECIEVER_H_

#include <memory>
#include <QObject>
#include <QtNetwork>
#include "FrameBuilder.h"

namespace udp_reciever {
class TestClass : public QObject {
  Q_OBJECT

 public:
    qint32 test;

 public:
    static TestClass* self;
    explicit TestClass(qint32 t, QObject *parent = 0): QObject(parent), test{t} {}
    static TestClass* GetInstance() {return self;}

};

class UdpReciever : public QObject {
  Q_OBJECT

 public:
    explicit UdpReciever(QObject *parent = 0)
      : QObject(parent), udp_socket_(), builder_() {}
    bool InitSocket(const QHostAddress &address, quint16 port = 0);

 private slots:
    void ProcessPendingDatagrams();

 signals:
    void DataRecieved(std::shared_ptr<Frame> frame);

 private:
    QUdpSocket udp_socket_;
    FrameBuilder builder_;
};
}  // namespace udp_reciever
#endif  // UDP_RECIEVER_UDPRECIEVER_H_
