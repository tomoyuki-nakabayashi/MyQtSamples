/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "BaseFrameBuilder.h"

namespace udp_receiver {
FrameBuilderStatus BaseFrameBuilder::Build(QDataStream &ds, qint32 remaining_data) {
  auto frame = CreateNewFrame();
  
  auto status = BuildImpl(ds, frame);
  if (status != FrameBuilderStatus::NO_ERROR) return status;

  return FrameBuilderStatus::READY;
}
}  // namespace udp_receiver