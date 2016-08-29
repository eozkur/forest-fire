TEMPLATE = app
CONFIG += console c++11
CONFIG -= appbundle qt

HEADERS += \
    src/board/cell.h \
    src/board/board.h \
    src/board/cellstate.h \
    src/forestfiresimulator.h

SOURCES += \
    src/main.cpp \
    src/board/board.cpp \
    src/board/cell.cpp \
    src/forestfiresimulator.cpp
