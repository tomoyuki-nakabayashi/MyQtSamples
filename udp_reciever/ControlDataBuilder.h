#ifndef SRC_CONTROL_DATA_BUILDER_H_
#define SRC_CONTROL_DATA_BUILDER_H_

#include <QObject>
#include <QDataStream>

namespace udp_reciever {
  class ControlData {
    private:
      const quint32 header;
      const qint32 payloadSize;
      const QByteArray payload;

    public:
      static const quint32 kHeaderMagic = 0x01234567;

    public:
      ControlData(): header(), payloadSize(), payload() {}
      ControlData(quint32 h, qint32 s, QByteArray p)
        : header{h}, payloadSize{s}, payload{p} {}
      quint32 GetHeader() const {return header;}
      qint32 GetPayloadSize() const {return payloadSize;}
      QByteArray GetPayload() const {return payload;}
  };

  enum class DataBuilderStatus {READY = 0, INVALID = -1, RETRY = -2};

  class ControlDataBuilder : public QObject
  {
    Q_OBJECT

    public:
      ControlDataBuilder() {}
      DataBuilderStatus isReadyToBuild(QDataStream &ds, const qint32 size);
      ControlData build(QDataStream &ds);
  };
}

Q_DECLARE_METATYPE(udp_reciever::ControlData*)
#endif //SRC_CONTROL_DATA_BUILDER_H_