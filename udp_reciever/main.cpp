/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <QCoreApplication>
#include "UdpReciever.h"
#include "Frame.h"

using udp_reciever::UdpReciever;
using udp_reciever::Frame;

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  qRegisterMetaType<QSharedPointer<Frame>>();
  udp_reciever::UdpReciever reciever;
  reciever.InitSocket(QHostAddress("0.0.0.0"), 45454);

  return a.exec();
}
