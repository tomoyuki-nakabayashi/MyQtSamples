#include <memory>
#include "FrameBuilder.h"

namespace udp_reciever {
  constexpr qint32 sizeofquint32() {return static_cast<int>(sizeof(quint32));}
  constexpr qint32 sizeofqint32() {return static_cast<int>(sizeof(qint32));}

  FrameBuilderStatus FrameBuilder::Build(QDataStream &ds, qint32 remaining_data)
  {
    if(remaining_data < sizeofquint32()) return FrameBuilderStatus::RETRY;
    remaining_data -= sizeofquint32();
    quint32 header;
    ds >> header;
    if(header != Frame::kHeaderMagic) return FrameBuilderStatus::INVALID;

    if(remaining_data < sizeofqint32()) return FrameBuilderStatus::RETRY;
    remaining_data -= sizeofqint32();
    qint32 size;
    ds >> size;

    if(remaining_data < size) return FrameBuilderStatus::RETRY;
    std::unique_ptr<char> buff(new char[size]);
    ds.readRawData(buff.get(), size);
    QByteArray payload(buff.get(), size);

    frame_ = std::shared_ptr<Frame>(new Frame(header, size, payload));
    remaining_data -= sizeofquint32() + sizeofqint32() + size;

    return FrameBuilderStatus::READY;
  }

  std::shared_ptr<Frame> FrameBuilder::GetFrame() {
    return frame_;
  }
}