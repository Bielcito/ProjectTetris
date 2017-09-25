TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    board.cpp \
    piece.cpp \
    block.cpp \
    space.cpp \
    instancegenerator.cpp \
    paintboard.cpp \
    instancesolver.cpp \
    instancereader.cpp

HEADERS += \
    board.h \
    piece.h \
    direction.h \
    block.h \
    pieces.h \
    space.h \
    instancegenerator.h \
    paintboard.h \
    instancesolver.h \
    instancereader.h
