#ifndef __DEMO_ECHO_CLIENT_H
#define __DEMO_ECHO_CLIENT_H

#include <dbus-c++/dbus.h>
//#include <dbus-c++/error.h>
#include "EchoProxy.h"
#include <cstdio>

class EchoClient
//: public org::freedesktop::DBus::EchoDemo_proxy,
: public hsae::interface::mydbus::Echo_proxy,
  public DBus::IntrospectableProxy,
  public DBus::ObjectProxy
{
public:

//    static EchoClient * GetInstance()
//    {
//       static EchoClient p;
//       return &p;
//    }

    EchoClient(DBus::Connection &connection, const char *path, const char *name);
    void ClientConnect(DBus::Connection &connection, const char *path, const char *name);

    virtual void Echoed(const DBus::Variant &value);
    virtual void MessageChanged(const std::string& message);
    virtual void DataChanged(const double& Data);
};

#endif//__DEMO_ECHO_CLIENT_H
