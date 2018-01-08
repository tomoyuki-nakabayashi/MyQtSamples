/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "FrameBuilder.h"

namespace udp_reciever {
void FrameBuilder::CreateNewFrame() {
  frame_ = QSharedPointer<Frame>(new Frame());
}

FrameBuilderStatus FrameBuilder::BuildHeader(QDataStream &ds, qint32 &remaining_data) {
  if(remaining_data < sizeofquint32()) return FrameBuilderStatus::RETRY;
  remaining_data -= sizeofquint32();
  quint32 header;
  ds >> header;
  if(header != Frame::kHeaderMagic) return FrameBuilderStatus::INVALID;
  frame_->SetHeader(header);

  if(remaining_data < sizeofqint32()) return FrameBuilderStatus::RETRY;
  remaining_data -= sizeofqint32();
  qint32 size;
  ds >> size;
  frame_->SetPayloadSize(size);

  return FrameBuilderStatus::NO_ERROR;
}

FrameBuilderStatus FrameBuilder::BuildPayload(QDataStream &ds, qint32 &remaining_data) {
  auto size = frame_->GetPayloadSize();
  if(remaining_data < size) return FrameBuilderStatus::RETRY;
  QScopedPointer<char> buff(new char[size]);
  ds.readRawData(buff.data(), size);
  QByteArray payload(buff.data(), size);

  frame_->SetPayload(payload);

  return FrameBuilderStatus::NO_ERROR;
}

FrameBuilderStatus FrameBuilder::BuildFooter(QDataStream &ds, qint32 &remaining_data) {
  return FrameBuilderStatus::NO_ERROR;
}

void FrameBuilder::UpdateFinished() {
  // if (something())
  finished_ = true;
}

QSharedPointer<Frame> FrameBuilder::GetFrame() {
  return frame_;
}

bool FrameBuilder::Finished() {
  return finished_;
}
}  // namespace udp_reciever