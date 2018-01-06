/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_BASEFRAMEBUILDER_H_
#define UDP_RECIEVER_BASEFRAMEBUILDER_H_

#include <memory>
#include <QObject>
#include <QDataStream>
#include "Frame.h"

namespace udp_reciever {
class BaseFrameBuilder {
 public:
    BaseFrameBuilder(): status_{FrameBuilderStatus::NO_ERROR} {}
    virtual ~BaseFrameBuilder() {}
    FrameBuilderStatus Build(QDataStream &ds, qint32 remaining_data);
    virtual std::shared_ptr<Frame> GetFrame() = 0;
  
 protected:
    FrameBuilderStatus status_;
  
 private:
    virtual void CreateNewFrame() = 0;
    virtual void BuildHeader(QDataStream &ds, qint32 &remaining_data) = 0;
    virtual void BuildPayload(QDataStream &ds, qint32 &remaining_data) = 0;
    virtual void BuildFooter(QDataStream &ds, qint32 &remaining_data) = 0;
};
}  // namespace udp_reciever
#endif  // UDP_RECIEVER_BASEFRAMEBUILDER_H_