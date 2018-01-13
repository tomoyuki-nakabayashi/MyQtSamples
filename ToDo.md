# UDP Frame

- [ ] Translate to QByteArray
- [ ] Move HeaderMagic to FrameBuilder
- [ ] Refactor >> operator

# Sequencer

- [ ] Reduce data copy
- [x] NEXT!!! remove pending data
- [ ] Use functor to change state
- [x] Use QScopedPointer instead QSharedPointer

# Biulders

- [x] Remove GetFrame
- [x] Remove parameter remaining_data

# FrameBuilder

- [x] Return LastResult

# SubFrameBuilder

- [x] Return LastResult

# UDP Receiver

- [ ] Handle error

# main

- [ ] Use CommandLineParser

# Refactoring

- [x] Template method handle pointer handler