# UDP Frame

- [x] Create UDP Packet
- [x] Change ControlData to ControlDataBuilder
- [x] Create ControlData as struct
- [x] Create instance from QByteArray
- [x] Have whole data size
- [ ] Template packet
- [ ] Define as a struct
- [x] Separate file
- [x] Overload operator <<
- [ ] Overload operator >>

# Sequencer

- [ ] AbstractDataStreamSequencer
  - [ ] Have pending data size & QDataStream
- [ ] Deal with another data type
- [ ] PeriodicDataStreamSequencer

# FrameBuilder

- [x] Test BaseFrameBuilder interface
- [x] Use QSharedPointer
- [x] Verify isReadyToBuild (true case)
- [x] GetFrame
- [x] Refactoring FrameBuilder::Build()
- [x] Builder has builder status
- [x] Refactoring FrameBuilder::BuildHeader()
- [x] BaseFrameBuilder
- [ ] BaseFrameBuilder Finished
- [ ] FrameBuilder Finished
- [ ] SubFrameBuilder Finished

# SubFrameBuilder

- [x] SubFrameBuilder
- [ ] Set expect id

# UDP Reciever

- [x] Use builder and emit DataCreated
- [ ] Handle error
- [x] Retreave signal argument
- [ ] Update datagram
- [x] Create two packets from QByteArray
- [x] Recieve datagram multiple times
- [x] Switch builder
- [x] Recieve SubFrame after a Frame
- [ ] Recieve SubFrames after a Frame
- [ ] Recieve Frame after successive SubFrames
- [x] Adopt State pattern

# TEST

- [x] Refactoring Frame usage