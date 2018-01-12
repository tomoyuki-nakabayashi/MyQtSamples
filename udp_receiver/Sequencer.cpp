/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "Sequencer.h"
#include "FrameBuilder.h"
#include "SubFrameBuilder.h"

namespace udp_receiver {
Sequencer::Sequencer(QObject *parent)
  :QObject(parent), state_(Sequence::FRAME), pending_data_(),
   builder_(QSharedPointer<BaseFrameBuilder> (new FrameBuilder())) {
     connect(builder_.data(), &FrameBuilder::FrameConstructed, this, &Sequencer::onFrameConstructed);
   }

const QByteArray& Sequencer::AppendPendingData(const QByteArray &ba) {
  return pending_data_.append(ba);
}

void Sequencer::ConstructFrame() {
  QDataStream build_stream(pending_data_);
  while (builder_->Build(build_stream, pending_data_.size()) == FrameBuilderStatus::READY) {
/* 
    auto frame = builder_->GetFrame();
    pending_data_.remove(0, frame->GetFrameSize());
 */
    auto state = GetNextState();
    ChangeSequence(state);
  }
}

Sequencer::Sequence Sequencer::GetNextState() {
  switch (state_) {
    case Sequence::FRAME:
      return Sequence::SUB_FRAME;
      break;
    case Sequence::SUB_FRAME:
      return Sequence::FRAME;
      break;
    case Sequence::RECOVERING:
      // TODO
      break;
    case Sequence::UNCHANGED:
      // Anything wrong. state_ never fall in this state.
      break;
  }
  return Sequence::UNCHANGED;
}

void Sequencer::ChangeSequence(Sequencer::Sequence next) {
  switch (next) {
    case Sequence::FRAME:
      state_ = Sequence::FRAME;
      builder_.reset(new FrameBuilder());
      break;
    case Sequence::SUB_FRAME:
      state_ = Sequence::SUB_FRAME;
      builder_.reset(new SubFrameBuilder());
      break;
    case Sequence::RECOVERING:
      // TODO
      break;
    case Sequence::UNCHANGED:
      // Nothing to do
      break;
  }
}

void Sequencer::onFrameConstructed(QVariant frame) {
  emit FrameConstructed(frame.value<QSharedPointer<Frame>>());
}
}  // namespace udp_receiver