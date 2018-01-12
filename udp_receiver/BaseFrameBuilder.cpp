/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "BaseFrameBuilder.h"

namespace udp_receiver {
FrameBuilderStatus BaseFrameBuilder::Build(QDataStream &ds, qint32 remaining_data) {
  QSharedPointer<Frame> frame = CreateNewFrame();
  
  auto status = BuildImpl(ds, frame);
  if (status != FrameBuilderStatus::NO_ERROR) return status;

  emit FrameConstructed(QVariant::fromValue(frame));
  return FrameBuilderStatus::READY;
}
}  // namespace udp_receiver