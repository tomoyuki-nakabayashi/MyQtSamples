#include <memory>
#include "FrameBuilder.h"

namespace udp_reciever {
  constexpr qint32 sizeofquint32() {return static_cast<int>(sizeof(quint32));}
  constexpr qint32 sizeofqint32() {return static_cast<int>(sizeof(qint32));}

  FrameBuilderStatus FrameBuilder::Build(QDataStream &ds)
  {
    quint32 header;
    qint32 size;

    ds >> header;
    ds >> size;
    std::unique_ptr<char> buff(new char[size]);
    ds.readRawData(buff.get(), size);
    QByteArray payload(buff.get(), size);

    frame_ = std::shared_ptr<Frame>(new Frame(header, size, payload));

    return FrameBuilderStatus::READY;
  }

  FrameBuilderStatus FrameBuilder::IsReadyToBuild(QDataStream &ds, const qint32 size)
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

  void FrameBuilder::CreateNewFrame() {
    //frame_ = std::shared_ptr<Frame>(new Frame());
  }

  std::shared_ptr<Frame> FrameBuilder::GetFrame() {
    return frame_;
  }
}