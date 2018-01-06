#include "SubFrameBuilder.h"

namespace udp_reciever {
void SubFrameBuilder::CreateNewFrame() {
  frame_ = std::shared_ptr<Frame>(new Frame());
}

void SubFrameBuilder::BuildHeader(QDataStream &ds, qint32 &remaining_data) {
  if (status_ != FrameBuilderStatus::NO_ERROR) return;
  if(remaining_data < sizeofquint32()) {
    status_ = FrameBuilderStatus::RETRY;
    return;
  }
  remaining_data -= sizeofquint32();
  quint32 header;
  ds >> header;
  if(header == 0 || header > 100) {
    status_ = FrameBuilderStatus::INVALID;
    return;
  }
  frame_->SetHeader(header);

  if(remaining_data < sizeofqint32()) {
    status_ = FrameBuilderStatus::RETRY;
    return;
  }
  remaining_data -= sizeofqint32();
  qint32 size;
  ds >> size;
  frame_->SetPayloadSize(size);
}

void SubFrameBuilder::BuildPayload(QDataStream &ds, qint32 &remaining_data) {
  if (status_ != FrameBuilderStatus::NO_ERROR) return;
  auto size = frame_->GetPayloadSize();
  if(remaining_data < size) {
    status_ = FrameBuilderStatus::RETRY;
    return;
  }
  std::unique_ptr<char> buff(new char[size]);
  ds.readRawData(buff.get(), size);
  QByteArray payload(buff.get(), size);

  frame_->SetPayload(payload);
}

void SubFrameBuilder::BuildFooter(QDataStream &ds, qint32 &remaining_data) {
  return;
}

FrameBuilderStatus SubFrameBuilder::Build(QDataStream &ds, qint32 remaining_data) {
  status_ = FrameBuilderStatus::NO_ERROR;

  CreateNewFrame();
  BuildHeader(ds, remaining_data);
  BuildPayload(ds, remaining_data);
  BuildFooter(ds, remaining_data);

  if (status_ == FrameBuilderStatus::NO_ERROR)
    status_ = FrameBuilderStatus::READY;

  return status_;
}

std::shared_ptr<Frame> SubFrameBuilder::GetFrame() {
  return frame_;
}
}  // namespace udp_reciever