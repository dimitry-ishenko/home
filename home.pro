QT += core gui widgets
CONFIG += c++14

TARGET = home
TEMPLATE = app

MOC_DIR = moc
UI_DIR = moc
OBJECTS_DIR = tmp

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES +=          \
    src/main.cpp    \
