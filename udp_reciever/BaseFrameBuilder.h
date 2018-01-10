/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECIEVER_BASEFRAMEBUILDER_H_
#define UDP_RECIEVER_BASEFRAMEBUILDER_H_

#include <QObject>
#include <QDataStream>
#include <QSharedPointer>
#include "Frame.h"

namespace udp_reciever {
//enum class FrameBuilderStatus {NO_ERROR = 0, READY = 1, INVALID = -1, RETRY = -2};

class BaseFrameBuilder: public QObject {
  Q_OBJECT
 public:
    explicit BaseFrameBuilder(QObject *parent = Q_NULLPTR): QObject(parent) {}
    virtual ~BaseFrameBuilder() {}
    FrameBuilderStatus Build(QDataStream &ds, qint32 remaining_data);
    virtual QSharedPointer<Frame> GetFrame() = 0;
  
 private:
    virtual void CreateNewFrame() = 0;
    virtual FrameBuilderStatus BuildHeader(QDataStream &ds, qint32 &remaining_data) = 0;
    virtual FrameBuilderStatus BuildPayload(QDataStream &ds, qint32 &remaining_data) = 0;
    virtual FrameBuilderStatus BuildFooter(QDataStream &ds, qint32 &remaining_data) = 0;
};
}  // namespace udp_reciever
#endif  // UDP_RECIEVER_BASEFRAMEBUILDER_H_