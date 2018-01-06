# UDP Frame

- [x] Create UDP Packet
- [x] Change ControlData to ControlDataBuilder
- [x] Create ControlData as struct
- [x] Create instance from QByteArray
- [x] Have whole data size
- [ ] Template packet
- [ ] Separate file

# Sequencer

- [ ] AbstractDataStreamSequencer
  - [ ] Have pending data size & QDataStream
- [ ] Deal with another data type
- [ ] PeriodicDataStreamSequencer

# FrameBuilder

- [x] Verify isReadyToBuild (true case)
- [x] GetFrame
- [x] Refactoring FrameBuilder::Build()
- [x] Builder has builder status
- [ ] Refactoring FrameBuilder::BuildHeader()
- [ ] BaseFrameBuilder
- [x] SubFrameBuilder
- [ ] AbstractData

# UDP Reciever

- [x] Use builder and emit DataCreated
- [ ] Handle error
- [x] Retreave signal argument
- [ ] Update datagram
- [x] Create two packets from QByteArray
- [ ] Update QByteArray
- [ ] Recieve datagram multiple times
- [ ] Switch builder