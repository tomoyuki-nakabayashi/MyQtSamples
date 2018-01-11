/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "BaseFrameBuilder.h"

namespace udp_receiver {
FrameBuilderStatus BaseFrameBuilder::Build(QDataStream &ds, qint32 remaining_data) {
  CreateNewFrame();
  
  auto status = BuildHeader(ds, remaining_data);
  if (status != FrameBuilderStatus::NO_ERROR) return status;

  status = BuildPayload(ds, remaining_data);
  if (status != FrameBuilderStatus::NO_ERROR) return status;

  BuildFooter(ds, remaining_data);
  if (status != FrameBuilderStatus::NO_ERROR) return status;

  return FrameBuilderStatus::READY;
}
}  // namespace udp_receiver