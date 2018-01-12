/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "SubFrameBuilder.h"

namespace udp_receiver {
void SubFrameBuilder::CreateNewFrame() {
  frame_ = QSharedPointer<Frame>(new Frame());
}

FrameBuilderStatus SubFrameBuilder::BuildHeader(QDataStream &ds, qint32 &remaining_data) {
  ds >> *frame_;
  return frame_->status;
}

FrameBuilderStatus SubFrameBuilder::BuildPayload(QDataStream &ds, qint32 &remaining_data) {
  return FrameBuilderStatus::NO_ERROR;
}

FrameBuilderStatus SubFrameBuilder::BuildFooter(QDataStream &ds, qint32 &remaining_data) {
  return FrameBuilderStatus::NO_ERROR;
}

QSharedPointer<Frame> SubFrameBuilder::GetFrame() {
  return frame_;
}
}  // namespace udp_receiver