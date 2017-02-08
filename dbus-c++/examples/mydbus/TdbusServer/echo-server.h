#ifndef __DEMO_ECHO_SERVER_H
#define __DEMO_ECHO_SERVER_H

//#include <dbus-c++/dbus.h>
#include <cstdio>
#include "EchoProxy.h"
#include "EchoAdaptor.h"

class EchoServer
: public hsae::interface::mydbus::Echo_adaptor,
  public DBus::IntrospectableAdaptor,
  public DBus::ObjectAdaptor
{
public:

    EchoServer(DBus::Connection &connection);

//    void EchoServerconnect();

    int32_t Random();

    std::string Hello(const std::string &name);

	DBus::Variant Echo(const DBus::Variant &value);

	std::vector< uint8_t > Cat(const std::string &file);

	int32_t Sum(const std::vector<int32_t> & ints);

	std::map< std::string, std::string > Info();
    virtual void myEcho(const std::map< std::string, std::string >& info);
};

#endif//__DEMO_ECHO_SERVER_H
