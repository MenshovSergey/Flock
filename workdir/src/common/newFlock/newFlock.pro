#-------------------------------------------------
#
# Project created by QtCreator 2013-10-22T22:27:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newFlock
TEMPLATE = app


SOURCES += main.cpp\
        world.cpp \
    Static_Object.cpp \
    Dynamic_Object.cpp \
    MyWorld1.cpp \
    my.cpp

HEADERS  += world.h \
    DynamicObject.h \
    Object.h \
    StaticObject.h \
    Flock.h \
    Manager.h \
    State.h \
    MyWorld1.h \
    my.h

FORMS    += world.ui
