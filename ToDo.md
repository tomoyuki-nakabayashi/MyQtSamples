# UDP Frame

- [ ] Move HeaderMagic to FrameBuilder
- [ ] Refactor >> operator
- [ ] Throw exception in >> operator
- [x] Rename frame_size to parsed_size or something

# Sequencer

- [ ] Reduce data copy
- [x] Use functor to change state
- [x] ConstructFrame() return bool

# Biulders

- [x] Change Build() parameter to QByteArray
- [x] Change BuildImpl to use QByteArray
- [x] Use QVariant to pass frame data
- [x] Build returns BuilderResult

# FrameBuilder


# SubFrameBuilder


# ErrorRecoveryBuilder

- [x] Build a valid frame if byte array has a valid data

# UDP Receiver

- [ ] Handle error
- [x] Has FrameConstruct loop

# main

- [ ] Use CommandLineParser

# Refactoring

