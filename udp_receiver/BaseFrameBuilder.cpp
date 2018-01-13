/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "BaseFrameBuilder.h"

namespace udp_receiver {
BuilderResult BaseFrameBuilder::Build(QByteArray &ba) {
  last_result_ = BuilderResult();
  QVariant frame_ptr = CreateNewFrame();
  
  last_result_ = BuildImpl(ba, frame_ptr);
  if (last_result_.status != FrameBuilderStatus::NO_ERROR) {
    return last_result_;
  }

  emit FrameConstructed(frame_ptr);
  last_result_.status = FrameBuilderStatus::READY;
  return last_result_;
}

BuilderResult BaseFrameBuilder::LastResult() {
  return last_result_;
}
}  // namespace udp_receiver