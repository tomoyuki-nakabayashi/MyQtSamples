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
struct BuilderResult {
  FrameBuilderStatus status;
  qint32 size;

  explicit BuilderResult(FrameBuilderStatus stat = FrameBuilderStatus::NO_ERROR, qint32 s = 0)
    : status{stat}, size{s} {}
};

class BaseFrameBuilder: public QObject {
  Q_OBJECT
 public:
    explicit BaseFrameBuilder(QObject *parent = Q_NULLPTR)
      : QObject(parent), last_result_() {}
    virtual ~BaseFrameBuilder() {}
    FrameBuilderStatus Build(QDataStream &ds);
    BuilderResult LastResult();

 signals:
    void FrameConstructed(QVariant frame);

 private:
    virtual QSharedPointer<Frame> CreateNewFrame() = 0;
    virtual FrameBuilderStatus BuildImpl(QDataStream &ds, Frame *frame) = 0;

 private:
    BuilderResult last_result_;
};
}  // namespace udp_receiver
#endif  // UDP_RECEIVER_BASEFRAMEBUILDER_H_