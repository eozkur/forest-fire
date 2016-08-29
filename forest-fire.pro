TEMPLATE = app
CONFIG += console c++11
CONFIG -= appbundle qt

SOURCES += src/main.cpp \
    src/cell.cpp \
    src/board.cpp \
    src/forestfiresimulator.cpp

HEADERS += \
    src/cell.h \
    src/board.h \
    src/forestfiresimulator.h \
    src/cellstate.h
