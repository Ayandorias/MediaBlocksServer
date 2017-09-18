#ifndef MB_TCP_CONNECTION_H
#define MB_TCP_CONNECTION_H

#include <mediablocks.hpp>

#include <QObject>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class MBTcpConnection : public QObject
{
    Q_OBJECT
public:
    explicit MBTcpConnection(QObject *parent = nullptr);
    bool connect();

private:
	/// Load the configuration
	bool loadConfiguration();
//    MediaBlocks::CmdValues cmdFromJsonObject(QJsonObject &obj);
	void createErrorResponse(QJsonObject &response, int32_t id, QJsonValue result, QJsonValue error);
//	void createNotAllowed(QJsonObject &response);
	void createRoomObject(QJsonObject &room, const QString &name, int32_t &port, int32_t &id);
//	void createUnknownCommand(QJsonObject &response, QJsonObject &obj);
//	void processMethodCreate(QJsonObject &obj);
//	void processMethodDelete(QJsonObject &obj);
//	void processMethodGet(QJsonObject &obj);
//	void processMethodUpdate(QJsonObject &obj);

	/// Resets the device
	void factoryReset(QJsonObject &request);


	int32_t getDevice(QJsonObject &request, QJsonObject &response);
	void resetDevice(QJsonObject &request);
	void updateDevice(QJsonObject &request);

	void createRoom(QJsonObject &request);
	void deleteRoom(QJsonObject &request);
	void getRoom(QJsonObject &request);
	int32_t getAllRooms(QJsonObject &request, QJsonObject &response);
	void updateRoom(QJsonObject &request);

	void saveSettings();
	void writeResponse(QJsonObject &response, int32_t id);

private:
	QJsonDocument _device_settings;
    QTcpServer *_server;
    QTcpSocket *_server_socket;

signals:

public slots:
    void newConnection();
    void readyRead();
};

#endif // MB_TCP_CONNECTION_H
