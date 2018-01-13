/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "BaseFrameBuilder.h"

namespace udp_receiver {
FrameBuilderStatus BaseFrameBuilder::Build(QByteArray &ba) {
  QDataStream ds(ba);
  last_result_ = BuilderResult();
  QSharedPointer<Frame> frame = CreateNewFrame();
  
  last_result_.status = BuildImpl(ds, frame.data());
  if (last_result_.status != FrameBuilderStatus::NO_ERROR) {
    return last_result_.status;
  }

  last_result_.size = frame->GetFrameSize();
  emit FrameConstructed(QVariant::fromValue(frame));
  return FrameBuilderStatus::READY;
}

BuilderResult BaseFrameBuilder::LastResult() {
  return last_result_;
}
}  // namespace udp_receiver