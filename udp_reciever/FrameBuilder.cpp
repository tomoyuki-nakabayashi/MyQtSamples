/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "FrameBuilder.h"

namespace udp_reciever {
void FrameBuilder::CreateNewFrame() {
  frame_ = std::shared_ptr<Frame>(new Frame());
}

void FrameBuilder::BuildHeader(QDataStream &ds, qint32 &remaining_data) {
  if (status_ != FrameBuilderStatus::NO_ERROR) return;
  if(remaining_data < sizeofquint32()) {
    status_ = FrameBuilderStatus::RETRY;
    return;
  }
  remaining_data -= sizeofquint32();
  quint32 header;
  ds >> header;
  if(header != Frame::kHeaderMagic) {
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

void FrameBuilder::BuildPayload(QDataStream &ds, qint32 &remaining_data) {
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

void FrameBuilder::BuildFooter(QDataStream &ds, qint32 &remaining_data) {
  return;
}

std::shared_ptr<Frame> FrameBuilder::GetFrame() {
  return frame_;
}
}  // namespace udp_reciever