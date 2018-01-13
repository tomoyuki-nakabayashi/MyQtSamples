/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "BaseFrameBuilder.h"

namespace udp_receiver {
FrameBuilderStatus BaseFrameBuilder::Build(QByteArray &ba) {
  last_result_ = BuilderResult();
  QVariant frame_ptr = CreateNewFrame();
  auto frame = frame_ptr.value<QSharedPointer<Frame>>();
  
  last_result_.status = BuildImpl(ba, frame.data());
  if (last_result_.status != FrameBuilderStatus::NO_ERROR) {
    return last_result_.status;
  }

  last_result_.parsed_bytes = frame->GetFrameSize();
  emit FrameConstructed(QVariant::fromValue(frame));
  return FrameBuilderStatus::READY;
}

BuilderResult BaseFrameBuilder::LastResult() {
  return last_result_;
}
}  // namespace udp_receiver