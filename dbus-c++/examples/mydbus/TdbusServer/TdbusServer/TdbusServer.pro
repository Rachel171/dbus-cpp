TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG  += c++11


INCLUDEPATH += /home/turkeyzhu/mycode/dbusC++/dbus-cpp/buildout/include/dbus-c++-1

LIBS += -L/home/turkeyzhu/mycode/dbusC++/dbus-cpp/buildout/lib/ \
-ldbus-c++-1

LIBS += -lpthread

SOURCES += \
    ../echo-server.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../echo-server.h \
    ../EchoAdaptor.h \
    ../EchoProxy.h




