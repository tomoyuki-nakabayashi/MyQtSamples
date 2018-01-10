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
  ds >> *frame_;
  return frame_->status;
}

FrameBuilderStatus FrameBuilder::BuildPayload(QDataStream &ds, qint32 &remaining_data) {
  return FrameBuilderStatus::NO_ERROR;
}

FrameBuilderStatus FrameBuilder::BuildFooter(QDataStream &ds, qint32 &remaining_data) {
  return FrameBuilderStatus::NO_ERROR;
}

QSharedPointer<Frame> FrameBuilder::GetFrame() {
  return frame_;
}
}  // namespace udp_reciever