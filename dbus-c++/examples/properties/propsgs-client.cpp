#include "propsgs-client.h"
#include <iostream>
#include <signal.h>
#include <pthread.h>

using namespace hsae::protocol::interface;

static const char *PROPS_SERVER_NAME = "hsae.protocol.interface.props";
static const char *PROPS_SERVER_PATH = "/hsae/protocol/interface/props";

PropsClient::PropsClient(DBus::Connection &connection, const char *path, const char *name)
: DBus::ObjectProxy(connection, path, name)
{
std::cout << "----I am here------------------init'\n";
}

void PropsClient::MessageChanged(const std::string& message)
{
	std::cout << "MessageChanged signal, new value: " << message << "\n";
};

void PropsClient::DataChanged(const double& data)
{
	std::cout << "DataChanged signal, new value:" << data << "\n";
};

void *test_property_proxy(void * input)
{
std::cout << "----I am here------------------11'\n";
	PropsClient *client = static_cast<PropsClient*>(input);
std::cout << "----I am here------------------22' \n";

if(client==NULL)
{
	std::cout << "----I am here-----------------client-NULL-point'\n";
	return NULL;
}
std::cout << "----I am here------------------33'\n";
	
	client->Message("message set by property access----");
	client->Data(1.1);
	std::cout << "wrote property 'Data'\n";

	

	return NULL;
}

DBus::BusDispatcher dispatcher;

void niam(int sig)
{
	dispatcher.leave();
	pthread_exit(NULL);
}

int main()
{
	signal(SIGTERM, niam);
	signal(SIGINT, niam);

	DBus::default_dispatcher = &dispatcher;
std::cout << "----I am here------------------1'\n";

	DBus::_init_threading();
std::cout << "----I am here------------------2'\n";

	DBus::Connection conn = DBus::Connection::SessionBus();
std::cout << "----I am here------------------3'\n";

	PropsClient client (conn, PROPS_SERVER_PATH, PROPS_SERVER_NAME);
std::cout << "----I am here------------------4'\n";

	pthread_t thread;
	pthread_create(&thread, NULL, test_property_proxy, &client);
std::cout << "----I am here------------------5'\n";
	dispatcher.enter();
std::cout << "----I am here------------------6'\n";
	return 0;
}
