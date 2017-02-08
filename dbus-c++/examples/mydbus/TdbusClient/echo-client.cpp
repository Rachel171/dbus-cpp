#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "echo-client.h"
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

static const char *ECHO_SERVER_NAME = "hsae.interface.mydbus.Echo";
static const char *ECHO_SERVER_PATH = "/hsae/interface/mydbus/Echo";

EchoClient::EchoClient(DBus::Connection &connection, const char *path, const char *name)
: DBus::ObjectProxy(connection, path, name)
{
}

void EchoClient::ClientConnect(DBus::Connection &connection, const char *path, const char *name)
{

}

void EchoClient::Echoed(const DBus::Variant &value)
{
    cout << "[Turkeyzhu Debug]-----------Echoed!";
}

void EchoClient::DataChanged(const double &Data)
{
     cout << "[Turkeyzhu Debug]--client--get-DataChanged!--"<<Data<<endl;
}

void EchoClient::MessageChanged(const string &message)
{
     cout << "[Turkeyzhu Debug]--client--get-MessageChanged!--"<<message.c_str()<<endl;
}

/*
 * For some strange reason, libdbus frequently dies with an OOM
 */

static const int THREADS = 1;

static bool spin = true;

void map_insert(map <string, string > *mapissue, string index, string x)
{
    mapissue->insert(map <string, string >::value_type(index, x));
}

void *greeter_thread(void *arg)
{

	DBus::Connection *conn = reinterpret_cast<DBus::Connection *>(arg);

     cout  << "[Turkeyzhu Debug]--conn->connected()==false)---test--0 " << endl;

	EchoClient client(*conn, ECHO_SERVER_PATH, ECHO_SERVER_NAME);
      cout  << "[Turkeyzhu Debug]--conn->connected()==false)---test--1 " << endl;


    int ret=0;
    bool clientconnect=false;
    bool busClientConnect=false;


    cout  << "[Turkeyzhu Debug]--ret-is--" <<ret<<"--clientconnect--"<<clientconnect <<"--busClientConnect--" <<busClientConnect<<endl;


    clientconnect=client.conn().connected();
    busClientConnect=client.conn().has_name(ECHO_SERVER_NAME);

//            dbus_bus_name_has_owner
    cout  << "[Turkeyzhu Debug]--ret-is--" <<ret
          <<"--clientconnect--"<<clientconnect
         <<"--busClientConnect--" <<busClientConnect
        <<endl;



          while (busClientConnect!=1)
          {
              sleep (2);
              cout  << "[Turkeyzhu Debug]--conn->connected()==false)--4 " << endl;
              EchoClient client(*conn, ECHO_SERVER_PATH, ECHO_SERVER_NAME);
              busClientConnect=client.conn().has_name(ECHO_SERVER_NAME);
          }


	char idstr[16];

	snprintf(idstr, sizeof(idstr), "%lu", pthread_self());

    for (int i = 0; i <2 && spin; ++i)
	{
        cout <<"[Turkeyzhu Debug]--thread--id--send"<< client.Hello(idstr) << endl;
	}

    std::map<string,string>  testmap;

    map_insert(&testmap,"mytot","I am a Geeker leader .");

    testmap.insert(map<string,string>::value_type("mytot1","ok"));

    client.myEcho(testmap);
    cout <<"[Turkeyzhu Debug]--thread id is--"<< idstr<< endl;

	return NULL;
}

DBus::BusDispatcher dispatcher;

void niam(int sig)
{
	spin = false;

	dispatcher.leave();
}

int main()
{
	signal(SIGTERM, niam);
	signal(SIGINT, niam);

	DBus::_init_threading();

	DBus::default_dispatcher = &dispatcher;

	DBus::Connection conn = DBus::Connection::SessionBus();

	pthread_t threads[THREADS];

	for (int i = 0; i < THREADS; ++i)
	{
        //cout  << "[Turkeyzhu Debug]--I--am--here-------haha!--thread-- " <<i<< endl;
		pthread_create(threads+i, NULL, greeter_thread, &conn);
	}

	dispatcher.enter();

    cout << "[Turkeyzhu Debug]---terminating" << endl;

	for (int i = 0; i < THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	return 0;
}
