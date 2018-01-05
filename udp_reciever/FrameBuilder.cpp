#include <memory>
#include "FrameBuilder.h"

namespace udp_reciever {
  constexpr qint32 sizeofquint32() {return static_cast<int>(sizeof(quint32));}
  constexpr qint32 sizeofqint32() {return static_cast<int>(sizeof(qint32));}

  Frame FrameBuilder::build(QDataStream &ds)
  {
    quint32 header;
    qint32 payloadSize;

    ds >> header;
    ds >> payloadSize;
    std::unique_ptr<char> buff(new char[payloadSize]);
    ds.readRawData(buff.get(), payloadSize);
    QByteArray payload(buff.get(), payloadSize);

    return Frame(header, payloadSize, payload);
  }

  FrameBuilderStatus FrameBuilder::isReadyToBuild(QDataStream &ds, const qint32 size)
  {
    auto remainDataSize = size;
    if(remainDataSize < sizeofquint32()) return FrameBuilderStatus::RETRY;
    quint32 h;
    ds >> h;
    if(h != Frame::kHeaderMagic) return FrameBuilderStatus::INVALID;
    remainDataSize -= sizeofquint32();

    if(remainDataSize < sizeofqint32()) return FrameBuilderStatus::RETRY;
    qint32 len;
    ds >> len;
    remainDataSize -= sizeofqint32();

    if(remainDataSize < len) return FrameBuilderStatus::RETRY;
    // proceed QDataStream index
    auto buf = new char[len];
    ds.readRawData(buf, len);
    delete[] buf;

    return FrameBuilderStatus::READY;
  }
}