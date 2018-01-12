# UDP Frame

- [ ] Translate to QByteArray
- [ ] Move HeaderMagic to FrameBuilder
- [ ] Refactor >> operator

# Sequencer

- [ ] Reduce data copy

# FrameBuilder

- [ ] Emit signal not Frame but QByteArray
- [ ] Return result as QVariant

# SubFrameBuilder

- [x] SubFrameBuilder
- [ ] Return result as QVariant

# UDP Receiver

- [ ] Handle error

# main

- [x] Command line option
- [ ] Use CommandLineParser

# TEST

- [x] Refactoring Frame usage
- [x] Test QMap(int, QVariant)
- [ ] Refactoring template method
- [ ] BuildHeader/Payload/Footer are integrated to BuildImpl