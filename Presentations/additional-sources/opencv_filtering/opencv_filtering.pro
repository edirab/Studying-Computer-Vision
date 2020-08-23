TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
LIBS += -L/usr/lib/i386-linux-gnu   \
        -lopencv_core   \
        -lopencv_highgui \
        -lopencv_imgproc

