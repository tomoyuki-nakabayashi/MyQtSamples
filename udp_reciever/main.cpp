#include <QCoreApplication>
#include "UdpReciever.h"

using namespace udp_reciever;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    udp_reciever::UdpReciever udpReciever;
    udpReciever.initSocket();

    return a.exec();
}

