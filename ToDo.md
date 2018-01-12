# UDP Frame

- [ ] Translate to QByteArray
- [ ] Move HeaderMagic to FrameBuilder
- [ ] Refactor >> operator

# Sequencer

- [ ] Reduce data copy
- [x] Receive frame by signal
- [x] Connect FrameBuilder signal
- [ ] NEXT!!! remove pending data

# FrameBuilder

- [x] Return result as QVariant
- [ ] Return LastResult

# SubFrameBuilder

- [x] SubFrameBuilder
- [x] Return result as QVariant
- [ ] Return LastResult

# UDP Receiver

- [ ] Handle error

# main

- [x] Command line option
- [ ] Use CommandLineParser

# Refactoring

- [x] Refactoring Frame usage
- [x] Test QMap(int, QVariant)
- [x] Refactoring template method
- [x] BuildHeader/Payload/Footer are integrated to BuildImpl
- [ ] Template method handle pointer handler