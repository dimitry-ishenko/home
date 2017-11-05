QT += core gui widgets
CONFIG += c++14

TARGET = home
TEMPLATE = app

MOC_DIR = moc
UI_DIR = moc
OBJECTS_DIR = tmp

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES +=                  \
    firmata/client.cpp      \
    firmata/debounce.cpp    \
    firmata/encoder.cpp     \
    firmata/pin.cpp         \
    firmata/pins.cpp        \
    firmata/serial_port.cpp \
    firmata/types.cpp       \
    gui/control.cpp         \
    src/encoder.cpp         \
    src/led.cpp             \
    src/main.cpp            \
    src/temp.cpp            \

HEADERS +=                  \
    firmata/asio_or_boost.hpp \
    firmata/call_chain.hpp  \
    firmata/client.hpp      \
    firmata/debounce.hpp    \
    firmata/encoder.hpp     \
    firmata/io_base.hpp     \
    firmata/pin.hpp         \
    firmata/pins.hpp        \
    firmata/serial_port.hpp \
    firmata/types.hpp       \
    gui/control.hpp         \
    src/clamp.hpp           \
    src/color.hpp           \
    src/encoder.hpp         \
    src/led.hpp             \
    src/temp.hpp            \

FORMS +=                    \
    gui/control.ui          \
