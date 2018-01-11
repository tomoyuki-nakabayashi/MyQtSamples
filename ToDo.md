# UDP Frame

- [ ] Translate to QByteArray
- [x] Define as a struct
- [ ] Move HeaderMagic to FrameBuilder
- [x] Overload >> operator
- [ ] Refactor >> operator

# Sequencer

- [ ] Have builder finish condition
- [x] Have a concrete builder
- [x] Add datagram
- [x] Parse datagram
- [x] Remove constructed pending data

# FrameBuilder

- [ ] Emit signal not Frame but QByteArray

# SubFrameBuilder

- [x] SubFrameBuilder
- [ ] Set expect id

# UDP Receiver

- [ ] Handle error
- [x] Update datagram
- [x] Create two packets from QByteArray
- [x] Recieve datagram multiple times
- [x] Switch builder
- [x] Recieve SubFrame after a Frame
- [x] Adopt State pattern

# TEST

- [x] Refactoring Frame usage
- [ ] Test QMap(int, QVariant)