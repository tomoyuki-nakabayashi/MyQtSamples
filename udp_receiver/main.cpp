/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QDebug>
#include "UdpReceiver.h"
#include "Frame.h"

using udp_receiver::UdpReceiver;
using udp_receiver::Frame;

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("udp_receiver");
  QCoreApplication::setApplicationVersion("1.0");

  QCommandLineParser parser;
  parser.setApplicationDescription("Receive UDP datagram.");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addOptions({
      {{"a", "address"}, 
        QCoreApplication::translate("main", "Host address. Default: 0.0.0.0"),
        QCoreApplication::translate("main", "address"),
        QCoreApplication::translate("main", "0.0.0.0")},
      {{"p", "port"}, 
        QCoreApplication::translate("main", "Port. Default: 45454"),
        QCoreApplication::translate("main", "port"),
        QCoreApplication::translate("main", "45454")}
  });

  parser.process(app);
  const QString addr = parser.value("address");
  const quint16 port = parser.value("port").toUInt();
  qDebug() << "UDP receiver starts" << addr << "(" << port << ")";

  qRegisterMetaType<QSharedPointer<Frame>>();
  udp_receiver::UdpReceiver receiver;
  receiver.InitSocket(QHostAddress(addr), port);

  return app.exec();
}
