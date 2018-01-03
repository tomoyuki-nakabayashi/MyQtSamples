#ifndef SRC_SUB_DATA_BUILDER_H_
#define SRC_SUB_DATA_BUILDER_H_

#include <QObject>
#include <QDataStream>

namespace udp_reciever {
  struct SubData {
    quint32 id;
    qint32 payloadSize;
    QByteArray payload;
    SubData(quint32 i, qint32 s, QByteArray p)
      : id{i}, payloadSize(s), payload(p) {}
  };

  class SubDataBuilder : public QObject
  {
    Q_OBJECT

    public:
      SubDataBuilder() {}
  };
}
#endif //SRC_SUB_DATA_BUILDER_H_