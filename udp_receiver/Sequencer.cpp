/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "Sequencer.h"
#include "FrameBuilder.h"
#include "SubFrameBuilder.h"

namespace udp_receiver {
Sequencer::Sequencer(QObject *parent)
  :QObject(parent)
  , pending_data_()
  , builder_()
  , builder_connection_() {
  change_state_ = Sequencer::ChangeStateOnFrame;
  builder_.reset(new FrameBuilder());
  builder_connection_ = connect(builder_.data(), &FrameBuilder::FrameConstructed, 
                                this, &Sequencer::onFrameConstructed);
}

const QByteArray& Sequencer::AppendPendingData(const QByteArray &ba) {
  return pending_data_.append(ba);
}

bool Sequencer::ConstructFrame() {
  auto result = builder_->Build(pending_data_);
  if (result.status == FrameBuilderStatus::RETRY) return false;
  if (result.status == FrameBuilderStatus::INVALID) {
    //EnterRecoveryMode();
    //return true;
    return false;
  }
/*
  if (result.status == FrameBuilderStatus::RECOVERED) {
    pending_data_.remove(0, result.parsed_bytes);
    ExitRecoveryMode;
    return true;
  }
*/
  pending_data_.remove(0, result.parsed_bytes);
  change_state_(*this);
  return true;
}

void Sequencer::ConnectToBuilder() {
  disconnect(builder_connection_);
  builder_connection_ = connect(builder_.data(), &FrameBuilder::FrameConstructed,
                                this, &Sequencer::onFrameConstructed);
}

void Sequencer::ChangeStateOnFrame(Sequencer& self) {
  self.change_state_ = &Sequencer::ChangeStateOnSubFrame;
  self.builder_.reset(new SubFrameBuilder());
  self.ConnectToBuilder();
}

void Sequencer::ChangeStateOnSubFrame(Sequencer& self) {
  self.change_state_ = &Sequencer::ChangeStateOnFrame;
  self.builder_.reset(new FrameBuilder());
  self.ConnectToBuilder();
}

void Sequencer::onFrameConstructed(QVariant frame) {
  emit FrameConstructed(frame.value<QSharedPointer<Frame>>());
}
}  // namespace udp_receiver