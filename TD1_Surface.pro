QT += core
QT -= gui

CONFIG += c++11

TARGET = TD1_Surface
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    point3d.cpp \
    surface3d.cpp \
    triangle3d.cpp \
    node3d.cpp \
    grid3d.cpp \
    sphere3d.cpp \
    implicitobject.cpp \
    doublesphere.cpp \
    pointlist.cpp

HEADERS += \
    point3d.h \
    surface3d.h \
    triangle3d.h \
    node3d.h \
    grid3d.h \
    sphere3d.h \
    implicitobject.h \
    doublesphere.h \
    pointlist.h
