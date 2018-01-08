/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "SubFrameBuilder.h"

namespace udp_reciever {
void SubFrameBuilder::CreateNewFrame() {
  frame_ = QSharedPointer<Frame>(new Frame());
}

FrameBuilderStatus SubFrameBuilder::BuildHeader(QDataStream &ds, qint32 &remaining_data) {
  if(remaining_data < sizeofquint32()) return FrameBuilderStatus::RETRY;
  remaining_data -= sizeofquint32();
  quint32 header;
  ds >> header;
  if(header == 0 || header > 100) return FrameBuilderStatus::INVALID;
  frame_->SetHeader(header);

  if(remaining_data < sizeofqint32()) return FrameBuilderStatus::RETRY;
  remaining_data -= sizeofqint32();
  qint32 size;
  ds >> size;
  frame_->SetPayloadSize(size);

  return FrameBuilderStatus::NO_ERROR;
}

FrameBuilderStatus SubFrameBuilder::BuildPayload(QDataStream &ds, qint32 &remaining_data) {
  auto size = frame_->GetPayloadSize();
  if(remaining_data < size) return FrameBuilderStatus::RETRY;
  QScopedPointer<char> buff(new char[size]);
  ds.readRawData(buff.data(), size);
  QByteArray payload(buff.data(), size);

  frame_->SetPayload(payload);

  return FrameBuilderStatus::NO_ERROR;
}

FrameBuilderStatus SubFrameBuilder::BuildFooter(QDataStream &ds, qint32 &remaining_data) {
  return FrameBuilderStatus::NO_ERROR;
}

void SubFrameBuilder::UpdateFinished() {
  count_++;
  if (count_ == 2) finished_ = true;
}

QSharedPointer<Frame> SubFrameBuilder::GetFrame() {
  return frame_;
}

bool SubFrameBuilder::Finished() {
  return finished_;
}
}  // namespace udp_reciever