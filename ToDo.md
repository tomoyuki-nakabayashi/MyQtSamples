# UDP Frame

- [ ] Template packet
- [ ] Define as a struct
- [ ] Move HeaderMagic to FrameBuilder

# Sequencer

- [ ] Have builder finish condition
- [x] Have a concrete builder
- [x] Add datagram
- [x] Parse datagram
- [x] Remove constructed pending data

# FrameBuilder

# SubFrameBuilder

- [x] SubFrameBuilder
- [ ] Set expect id

# UDP Reciever

- [ ] Handle error
- [x] Update datagram
- [x] Create two packets from QByteArray
- [x] Recieve datagram multiple times
- [x] Switch builder
- [x] Recieve SubFrame after a Frame
- [x] Adopt State pattern

# TEST

- [x] Refactoring Frame usage