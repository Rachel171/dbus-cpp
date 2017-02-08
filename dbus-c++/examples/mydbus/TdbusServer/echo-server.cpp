#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "echo-server.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <limits.h>


#include <iostream>

static const char *ECHO_SERVER_NAME = "hsae.interface.mydbus.Echo";
static const char *ECHO_SERVER_PATH = "/hsae/interface/mydbus/Echo";

EchoServer::EchoServer(DBus::Connection &connection)
: DBus::ObjectAdaptor(connection, ECHO_SERVER_PATH)
{
}


int32_t EchoServer::Random()
{
	return rand();
}

std::string EchoServer::Hello(const std::string &name)
{
    std::cout <<"[Turkeyzhu Debug]-----echo-result--"<<name << '\n';
	return "Hello " + name + "!";

}

DBus::Variant EchoServer::Echo(const DBus::Variant &value)
{
     std::cout <<"[Turkeyzhu Debug]-----echo-Echo--"<< '\n';
	this->Echoed(value);
	return value;
}

std::vector< uint8_t > EchoServer::Cat(const std::string &file)
{
	FILE *handle = fopen(file.c_str(), "rb");

	if (!handle) throw DBus::Error("org.freedesktop.DBus.EchoDemo.ErrorFileNotFound", "file not found");

	uint8_t buff[1024];

	size_t nread = fread(buff, 1, sizeof(buff), handle);

	fclose(handle);

	return std::vector< uint8_t > (buff, buff + nread);
}

int32_t EchoServer::Sum(const std::vector<int32_t>& ints)
{
	int32_t sum = 0;

	for (size_t i = 0; i < ints.size(); ++i) sum += ints[i];

    return sum;
}


void EchoServer::myEcho(const std::map<std::string, std::string> &info)
{
//    std::map<std::string,std::string>::const_iterator it;
//    for (it=info.begin(); it!=info.end(); ++it)
//        std::cout <<"-----echo-result--"<< it->first << " => " << it->second << '\n';
    for(auto & ele : info)
    {
        std::cout <<"[Turkeyzhu Debug]-----echo-result--"<< ele.first << " => " << ele.second << '\n';
    }

    sleep(2);
    this->MessageChanged("--sigSend--haha--");   //message callback test
    std::cout <<"[Turkeyzhu Debug]-----echo-server-sigsend--"<<std::endl;
    this->DataChanged(77778);
}

std::map< std::string, std::string > EchoServer::Info()
{
	std::map< std::string, std::string > info;
	char hostname[HOST_NAME_MAX];

	gethostname(hostname, sizeof(hostname));
	info["hostname"] = hostname;
	info["username"] = getlogin();

	return info;
}



DBus::BusDispatcher dispatcher;

void niam(int sig)
{
	dispatcher.leave();
}

int main()
{
	signal(SIGTERM, niam);
	signal(SIGINT, niam);

	DBus::default_dispatcher = &dispatcher;

	DBus::Connection conn = DBus::Connection::SessionBus();
	conn.request_name(ECHO_SERVER_NAME);

    EchoServer server(conn);



	dispatcher.enter();

	return 0;
}
