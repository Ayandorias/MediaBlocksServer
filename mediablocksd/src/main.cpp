#include <QCoreApplication>

#include <mbtcpconnection.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	MBTcpConnection server;
	server.connect();

	return a.exec();
}
