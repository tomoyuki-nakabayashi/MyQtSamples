# UDP Packet

- [x] Create UDP Packet
- [x] Change ControlData to ControlDataBuilder
- [x] Create ControlData as struct
- [x] Create instance from QByteArray
- [ ] Have whole data size
- [x] Verify isReadyToBuild (true case)
- [] Verify isReadyToBuild (false case)
- [ ] AbstractDataStreamSequencer
  - [ ] Have pending data size & QDataStream
- [ ] Deal with another data type
- [ ] PeriodicDataStreamSequencer
- [ ] AbstractDataBuilder
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