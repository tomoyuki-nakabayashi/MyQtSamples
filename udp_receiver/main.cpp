/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <QCoreApplication>
#include "UdpReceiver.h"
#include "Frame.h"

using udp_receiver::UdpReceiver;
using udp_receiver::Frame;

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  qRegisterMetaType<QSharedPointer<Frame>>();

  QStringList options = QCoreApplication::arguments();
  options.removeAt(0);

  const auto addr = (options.size() > 0) ? options.at(0) : "0.0.0.0";
  const auto port = (options.size() == 2) ? options.at(1).toUShort() : 45454;

  udp_receiver::UdpReceiver receiver;
  receiver.InitSocket(QHostAddress(addr), port);

  return a.exec();
}
