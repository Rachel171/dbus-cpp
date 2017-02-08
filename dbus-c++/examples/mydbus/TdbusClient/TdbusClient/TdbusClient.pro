TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


CONFIG  += c++11

INCLUDEPATH += /home/turkeyzhu/mycode/dbusC++/dbus-cpp/buildout/include/dbus-c++-1
#INCLUDEPATH += /../../buildout/include/dbus-c++-1

LIBS += -L/home/turkeyzhu/mycode/dbusC++/dbus-cpp/buildout/lib/ \
#LIBS += -L/../../buildout/lib/ \
-ldbus-c++-1

LIBS += -lpthread

SOURCES += \
    ../echo-client.cpp

include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    ../echo-introspect.xml

HEADERS += \
    ../EchoAdaptor.h \
    ../echo-client.h \
    ../EchoProxy.h

