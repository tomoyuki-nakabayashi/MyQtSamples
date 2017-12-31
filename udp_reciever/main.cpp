#include <QCoreApplication>
#include "UdpReciever.h"

using namespace udp_reciever;

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  udp_reciever::UdpReciever udpReciever;
  udpReciever.initSocket(QHostAddress("0.0.0.0"), 45454);

  return a.exec();
}

