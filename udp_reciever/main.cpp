/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <QCoreApplication>
#include "UdpReciever.h"

using udp_reciever::UdpReciever;

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  udp_reciever::UdpReciever reciever;
  reciever.InitSocket(QHostAddress("0.0.0.0"), 45454);

  return a.exec();
}

