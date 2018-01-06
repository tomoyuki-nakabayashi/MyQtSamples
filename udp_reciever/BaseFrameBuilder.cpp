/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "BaseFrameBuilder.h"

namespace udp_reciever {
FrameBuilderStatus BaseFrameBuilder::Build(QDataStream &ds, qint32 remaining_data) {
  status_ = FrameBuilderStatus::NO_ERROR;

  CreateNewFrame();
  BuildHeader(ds, remaining_data);
  BuildPayload(ds, remaining_data);
  BuildFooter(ds, remaining_data);

  if (status_ == FrameBuilderStatus::NO_ERROR)
    status_ = FrameBuilderStatus::READY;

  return status_;
}
}  // namespace udp_reciever