/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#ifndef UDP_RECEIVER_BASEFRAMEBUILDER_H_
#define UDP_RECEIVER_BASEFRAMEBUILDER_H_

#include <QObject>
#include <QVariant>
#include <QDataStream>
#include <QSharedPointer>
#include "Frame.h"

namespace udp_receiver {
//enum class FrameBuilderStatus {NO_ERROR = 0, READY = 1, INVALID = -1, RETRY = -2};

class BaseFrameBuilder: public QObject {
  Q_OBJECT
 public:
    explicit BaseFrameBuilder(QObject *parent = Q_NULLPTR): QObject(parent) {}
    virtual ~BaseFrameBuilder() {}
    FrameBuilderStatus Build(QDataStream &ds, qint32 remaining_data);
    virtual QSharedPointer<Frame> GetFrame() = 0;

 signals:
    void NotifyFrameConstructed(QVariant frame);

 private:
    virtual QSharedPointer<Frame> CreateNewFrame() = 0;
    virtual FrameBuilderStatus BuildImpl(QDataStream &ds, QSharedPointer<Frame>) = 0;
};
}  // namespace udp_receiver
#endif  // UDP_RECEIVER_BASEFRAMEBUILDER_H_