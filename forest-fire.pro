TEMPLATE = app
CONFIG += console c++11
CONFIG -= appbundle
CONFIG -= qt

SOURCES += main.cpp \
    cell.cpp \
    board.cpp \
    forestfiresimulator.cpp

HEADERS += \
    cell.h \
    board.h \
    forestfiresimulator.h \
    cellstate.h
