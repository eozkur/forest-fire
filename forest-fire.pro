TEMPLATE = app
CONFIG += console c++11
CONFIG -= appbundle qt

# -Wall & -Wextra Catch all warnings
# -ftrapv Catch the run-time overflow of signed numbers.
# -Werror Promote warnings into errors
QMAKE_CXXFLAGS += -Wall -Wextra -ftrapv # -Werror

HEADERS += \
    src/board/cell.h \
    src/board/board.h \
    src/board/cellstate.h \
    src/forestfiresimulator.h \
    tests/catch.hpp

SOURCES += \
    src/main.cpp \
    src/board/board.cpp \
    src/board/cell.cpp \
    src/forestfiresimulator.cpp \
    tests/sanity.cpp \
    tests/board/cell_tests.cpp \
    tests/board/board_tests.cpp

# include SDL libs for Windows.
LIBS += -L$$PWD/libs/sdl/lib/ -lmingw32
LIBS += -L$$PWD/libs/sdl/lib/ -lSDL2main
LIBS += -L$$PWD/libs/sdl/lib/ -lSDL2

INCLUDEPATH += $$PWD/libs/sdl/include
DEPENDPATH += $$PWD/libs/sdl/include

# Copy SDL.dll to the bin folders.
copydata.commands = $(COPY_DIR) $$shell_path($$PWD/libs/sdl/bin) $$shell_path($$OUT_PWD/debug) $$escape_expand(\n\t) $(COPY_DIR) $$shell_path($$PWD/libs/sdl/bin) $$shell_path($$OUT_PWD/release)
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
