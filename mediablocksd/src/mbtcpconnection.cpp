#include "mbtcpconnection.h"

#include <QFile>

MBTcpConnection::MBTcpConnection(QObject *parent) : QObject(parent) {
	QJsonParseError error;
	QFile json(MediaBlocks::MEDIA_BLOCKS);
	if(json.open(QIODevice::ReadWrite)) {
		_device_settings = QJsonDocument::fromJson(json.readAll(), &error);
		json.close();
	}
}

bool MBTcpConnection::connect() {
	bool result = false;
	_server = new QTcpServer(nullptr);

	if(_server != nullptr) {
		QObject::connect(_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
		result = _server->listen(QHostAddress::Any, 10007);
	}

	return result;
}

/*MediaBlocks::CmdValues MBTcpConnection::cmdFromJsonObject(QJsonObject &obj) {
	QString cmd = obj[MediaBlocks::COMMAND].toString();
	MediaBlocks::CmdValues val = MediaBlocks::NONE;
	for(int32_t i = 0; i < _cmds.size(); ++i) {
		Commands *it = _cmds.at(i);
		if(cmd == it->_cmd) {
			val = it->_cmd_value;
			break;
		}
	}
	return val;
}*/

bool MBTcpConnection::loadConfiguration() {
	return true;
}

void MBTcpConnection::createErrorResponse(QJsonObject &response, int32_t id, QJsonValue result, QJsonValue error) {
	response.insert("result", result);
	response.insert("error", error);

	writeResponse(response, id);
}

void MBTcpConnection::createRoomObject(QJsonObject &room, const QString &name, int32_t &port, int32_t &id) {
	room.insert("name", name);
	room.insert("port", port);
	room.insert("id", id);
}

/*void MBTcpConnection::processMethodGet(QJsonObject &obj) {
	QJsonObject response;
	response.insert(MediaBlocks::METHOD, MediaBlocks::METHOD_GET);
	if(_device_settings.isObject()) {
		QJsonObject device = _device_settings.object();
		switch(cmdFromJsonObject(obj)) {
			case MediaBlocks::ROOM: {
				bool avail = false;
				QJsonValue value = device[MediaBlocks::CMD_ROOMLIST];
				if(value.isArray()) {
					QJsonArray array = value.toArray();
					QJsonArray::iterator it;
					for(it = array.begin(); it != array.end(); ++it) {
						QJsonValue ref = *it;
						if(ref.isObject()) {
							QJsonObject itobj = ref.toObject();
							QString name = itobj["name"].toString();
							QJsonValue objname = obj["name"];
							if(objname.isString()) {
								if(objname.toString() == name) {
									response.insert(MediaBlocks::RESPONSE, MediaBlocks::SUCCESS_200);
									response.insert(MediaBlocks::CMD_ROOMINFO, QJsonValue(itobj));
									avail = true;
									break;
								}
							}
						}
					}
					if(!avail) {
						QString name = obj["name"].toString();
						QString reason = tr("Could not find room: %1").arg(name);
						createErrorResponse(response, MediaBlocks::ERROR_404, reason);
					}
				}
				break;
			}
			case MediaBlocks::ROOMS: {
				if(device[MediaBlocks::CMD_ROOMLIST].isArray()) {
					response.insert(MediaBlocks::RESPONSE, QJsonValue(MediaBlocks::SUCCESS_200));
					response.insert(MediaBlocks::CMD_ROOMLIST, device[MediaBlocks::CMD_ROOMLIST]);
				} else {
					createErrorResponse(response, MediaBlocks::ERROR_400, tr("No valid roomlist found!"));
				}
				break;
			}
			case MediaBlocks::DEVICENAME: {
				response.insert(MediaBlocks::RESPONSE, QJsonValue(MediaBlocks::SUCCESS_200));
				response.insert(MediaBlocks::CMD_DEVICENAME, device[MediaBlocks::CMD_DEVICENAME]);
				break;
			}
			case MediaBlocks::DEVICETYPE: {
				response.insert(MediaBlocks::RESPONSE, QJsonValue(MediaBlocks::SUCCESS_200));
				response.insert(MediaBlocks::CMD_DEVICETYPE, device[MediaBlocks::CMD_DEVICETYPE]);
				break;
			}
			case MediaBlocks::MUSIC_DB: {
				response.insert(MediaBlocks::RESPONSE, QJsonValue(MediaBlocks::SUCCESS_200));
				response.insert(MediaBlocks::CMD_MUSICDB, device[MediaBlocks::CMD_MUSICDB]);
				break;
			}
			case MediaBlocks::NONE:
			default: {
				createUnknownCommand(response, obj);
			}
		}
	} else {
		createErrorResponse(response, MediaBlocks::ERROR_400, tr("Corrupt Settings"));
	}

	writeResponse(response);
}*/

/*void MBTcpConnection::processMethodUpdate(QJsonObject &obj) {
	QJsonObject response;
	response.insert(MediaBlocks::METHOD, MediaBlocks::METHOD_CREATE);
	if(_device_settings.isObject()) {
		switch(cmdFromJsonObject(obj)) {
			case MediaBlocks::ROOM: {

				break;
			}
			case MediaBlocks::NONE:
			default :{
				createUnknownCommand(response, obj);
			}
		}
	} else {
		createErrorResponse(response, MediaBlocks::ERROR_400, tr("Corrupt Settings"));
	}
	writeResponse(response);
}*/


int32_t MBTcpConnection::getDevice(QJsonObject &request, QJsonObject &response) {
	int32_t id = -1;

	QJsonValue request_id = request["id"];
	if(request_id.isDouble()) {
		id = (int32_t)request_id.toDouble();
	}
	QJsonObject device = _device_settings.object();
	QJsonValue name = device["devicename"];
	QJsonValue type = device["devicetype"];
	QJsonValue music_db = device["music_db"];

	response.insert("devicename", name);
	response.insert("devicetype", type);
	response.insert("music_db", music_db);

	return id;
}

void MBTcpConnection::resetDevice(QJsonObject &request) {
	Q_UNUSED(request)

	QFile device(MediaBlocks::MEDIA_BLOCKS_DEVICE);
	if(device.open(QIODevice::ReadOnly)) {

		device.close();
	}
}

void MBTcpConnection::updateDevice(QJsonObject &request) {
	int32_t id = -1;

	QJsonValue request_id = request["id"];
	if(request_id.isDouble()) {
		id = static_cast<int32_t>(request_id.toDouble());
	}
	QJsonObject device = _device_settings.object();
	QJsonValue paramval = request["param"];

	qDebug() << "Type: " << paramval.type();

	if(paramval.isObject()) {
		QJsonObject param = paramval.toObject();
		QJsonValue request_name = param["devicename"];
		QJsonValue request_type = param["devicetype"];
		QJsonValue request_db = param["music_db"];

		if(!request_db.isNull()) {
			device.take("music_db");
			device.insert("music_db", request_db);
		} else if(!request_name.isNull()) {
			device.take("devicename");
			device.insert("devicename", request_name);
		} else if(!request_type.isNull()) {
			device.take("devicetype");
			QString type = request_type.toString();
			if(type == "client" || type == "server") {
				device.insert("devicetype", request_type);
			} else {
				QJsonObject response;
				createErrorResponse(response, id, QJsonValue(-1), QJsonValue("Devicetype could not recognized"));
				return;
			}
		}

		_device_settings.setObject(device);
		qDebug() << _device_settings.toJson();
		saveSettings();
	}
}

void MBTcpConnection::createRoom(QJsonObject &request) {
	QJsonObject response;
	QJsonValue param;
	bool avail = false;
	int32_t reqid = -1;
	QJsonValue request_id = request["id"];
	int32_t port = -1;
	int32_t id = -1;

	if(request_id.isDouble()) {
		reqid = static_cast<int32_t>(request_id.toDouble());
	}

	if(_device_settings.isObject()) { // [1]
		QJsonObject device = _device_settings.object();
		QString name;
		QJsonValue objname;
		QJsonValueRef value = device[MediaBlocks::ROOMLIST];
		if(value.isArray()) { // [2]

			QJsonArray array = value.toArray();
			QJsonArray::iterator it;
			for(it = array.begin(); it != array.end(); ++it) { // [3]
				QJsonValue ref = *it;
				if(ref.isObject()) { // [4]
					QJsonObject itobj = ref.toObject();
					if(itobj["name"].isString()) { // [5]
						name = itobj["name"].toString();
						if(itobj["port"].isDouble()) { // [6]
							// Checking Ports for the Rooms.
							if(itobj["port"].toInt() > port) {
								port = itobj["port"].toInt();
							}
							if(itobj["id"].isDouble()) { // [7]
								// Checking ID for the Rooms.
								if(itobj["id"].toInt() > id) {
									id = itobj["id"].toInt();
								}
								param = request["param"];
								if(param.isObject()) { // [8]
									QJsonObject obj = param.toObject();
									objname = obj["name"];
									if(objname.isString()) {
										if(objname.toString() == name) {
											createErrorResponse(response, reqid, MediaBlocks::ERROR_461, tr("Ressource allready available"));
											avail = true;
											break;
										}
									}
								} // [8]
							} // [7]
						} // [6]
					} // [5]
				} // [4]
			} // [3]
			if(avail == false) {
				++port;
				++id;
				QJsonObject room;
				if(objname.isString()) {
					createRoomObject(room, objname.toString(), port, id);
					response.insert("param", room);
					array.append(room);

					device.remove(MediaBlocks::ROOMLIST);
					device.insert(MediaBlocks::ROOMLIST, QJsonValue(array));
					writeResponse(response, reqid);
				}
			}
		} // [2]

		// Write modified Json Object to Json Document.
		_device_settings.setObject(device);
		// Save the document.
		saveSettings();
	} // [1]
}

void MBTcpConnection::deleteRoom(QJsonObject &request) {
	int32_t request_id = -1;
	QJsonValue param = request["param"];
	QJsonValue reqid = request["id"];
	if(reqid.isDouble()) {
		request_id = reqid.toInt();
		if(param.isObject()) {
			QJsonObject obj = param.toObject();
			QJsonValue room_id = obj["id"];
			if(room_id.isDouble()) {
				int32_t id = room_id.toInt();
				QJsonObject device = _device_settings.object();
				QJsonValue value = device[MediaBlocks::ROOMLIST];
				if(value.isArray()) {
					QJsonArray array = value.toArray();
					QJsonArray::iterator it;
					for(it = array.begin(); it != array.end(); ++it) {
						QJsonValue ref = *it;
						if(ref.isObject()) {
							QJsonObject room = ref.toObject();
							QJsonValue ref_id = room["id"];
							if(ref_id.isDouble()) {
								if(id == ref_id.toInt()) {
									// Found Room to Delete
									QJsonObject response;
									QJsonObject delroom;
									delroom.insert("id", QJsonValue(id));
									response.insert("param", delroom);
									writeResponse(response, request_id);

									array.erase(it);
									device.remove(MediaBlocks::ROOMLIST);
									device.insert(MediaBlocks::ROOMLIST, QJsonValue(array));

									_device_settings.setObject(device);
									saveSettings();
									return;
								}
							}
						}
					}
				}
			}
		}
	}
	QJsonObject response;
	createErrorResponse(response, request_id, MediaBlocks::ERROR_400, tr("Can't delete room!"));
}

void MBTcpConnection::getRoom(QJsonObject &request) {
	int32_t id = -1;
	int32_t room_id = -1;

	QJsonObject response;
	QJsonValue request_id = request["id"];
	QJsonValue param = request["param"];

	if(param.isObject()) {
		QJsonObject obj = param.toObject();
		QJsonValue rid = obj["id"];
		if(rid.isDouble()) {
			room_id = rid.toInt();
		}
	}

	if(request_id.isDouble()) {
		id = request_id.toInt();
	}

	QJsonObject device = _device_settings.object();
	QJsonValue value = device[MediaBlocks::ROOMLIST];

	if(value.isArray()) {
		QJsonArray array = value.toArray();
		QJsonArray::iterator it;
		for(it = array.begin(); it != array.end(); ++it) {
			QJsonValue ref = *it;
			if(ref.isObject()) {
				QJsonObject obj = ref.toObject();
				QJsonValue refid = obj["id"];
				if(refid.isDouble()) {
					if(refid.toInt() == room_id) {
						//QJsonValueRef value = device[MediaBlocks::ROOMLIST];
						response.insert("param", obj);
						writeResponse(response, id);
						return;
					}
				}
			}
		}
	}
	createErrorResponse(response, id, MediaBlocks::ERROR_404, tr("No valid room found!"));
}

int32_t MBTcpConnection::getAllRooms(QJsonObject &request, QJsonObject &response) {
	int32_t id = -1;
	QJsonValue request_id = request["id"];
	if(request_id.isDouble()) {
		id = request_id.toInt();
	}

	QJsonObject device = _device_settings.object();
	if(device[MediaBlocks::ROOMLIST].isArray()) {
		QJsonValueRef value = device[MediaBlocks::ROOMLIST];
		response.insert("param", value);
	}
}

void MBTcpConnection::updateRoom(QJsonObject &request) {
	QJsonObject response;
	int32_t request_id = -1;
	QJsonValue param = request["param"];
	QJsonValue reqid = request["id"];
	if(reqid.isDouble()) {
		request_id = reqid.toInt();
		if(param.isObject()) {
			QJsonObject obj = param.toObject();
			QJsonValue room_id = obj["id"];
			if(room_id.isDouble()) {
				int32_t id = room_id.toInt();
				QJsonObject device = _device_settings.object();
				QJsonValue value = device[MediaBlocks::ROOMLIST];
				if(value.isArray()) {
					QJsonArray array = value.toArray();
					QJsonArray::iterator it;
					for(it = array.begin(); it != array.end(); ++it) {
						QJsonValue ref = *it;
						if(ref.isObject()) {
							QJsonObject room = ref.toObject();
							QJsonValue ref_id = room["id"];
							if(ref_id.isDouble()) {
								if(id == ref_id.toInt()) {
									printf("Raum gefunden: %d\n", id);
									QJsonValue ref_port = room["port"];
									if(ref_port.isDouble()) {
										int32_t port = ref_port.toInt();
										array.erase(it);

										QJsonObject newroom;
										QJsonValue objname = obj["name"];
										if(objname.isString()) {
											createRoomObject(newroom, objname.toString(), port, id);
											response.insert("param", newroom);
											array.append(newroom);

											device.remove(MediaBlocks::ROOMLIST);
											device.insert(MediaBlocks::ROOMLIST, QJsonValue(array));
											writeResponse(response, request_id);
										}
										_device_settings.setObject(device);
										saveSettings();
										return;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	createErrorResponse(response, request_id, MediaBlocks::ERROR_400, tr("Can't update room!"));
}

void MBTcpConnection::saveSettings() {
	QFile json(MediaBlocks::MEDIA_BLOCKS);
	if(json.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
		json.write(_device_settings.toJson());
		json.close();
	}
}

void MBTcpConnection::writeResponse(QJsonObject &response, int32_t id) {

	response.insert("jsonrpc", QJsonValue("2.0"));
	response.insert("id", QJsonValue(id));

	QJsonDocument doc;
	doc.setObject(response);
	_server_socket->write(doc.toJson());
}

void MBTcpConnection::newConnection() {
	_server_socket = _server->nextPendingConnection();
	QObject::connect(_server_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MBTcpConnection::readyRead() {
	int32_t id = -1;
	QJsonObject response;
	QByteArray ba;
	QJsonParseError error;
	while(_server_socket->canReadLine()) {
		ba += _server_socket->readLine();
	}

	QJsonDocument json = QJsonDocument::fromJson(ba, &error);
	if(error.error == 0) {
		if(json.isObject()) {
			QJsonObject obj = json.object();
			QJsonValue jsonrpc = obj["jsonrpc"];
			if(!jsonrpc.isNull() && jsonrpc.toString() == "2.0") {
				QJsonValue rpc_method = obj["method"].toString();
				if(rpc_method.isString()) {
					QString method = rpc_method.toString();

					if(method == MediaBlocks::MBSERVER_DEVICE_GET){
						id = getDevice(obj, response);
					} else if(method == MediaBlocks::MBSERVER_DEVICE_RESET){
						resetDevice(obj);
					} else if(method == MediaBlocks::MBSERVER_DEVICE_UPDATE){
						updateDevice(obj);
					} else if(method == MediaBlocks::MBSERVER_DEVICE_SERVICE_REBOOT_SET){
					} else if(method == MediaBlocks::MBSERVER_DEVICE_SERVICE_UPDATE_GET){
					} else if(method == MediaBlocks::MBSERVER_DEVICE_SERVICE_UPDATE_SET){
					} else if(method == MediaBlocks::MBSERVER_DEVICE_SETTINGS_NETWORK_GET){
					} else if(method == MediaBlocks::MBSERVER_DEVICE_SETTINGS_NETWORK_UPDATE){
					} else if(method == MediaBlocks::MBSERVER_DEVICE_SETTINGS_WLAN_GET){
					} else if(method == MediaBlocks::MBSERVER_DEVICE_SETTINGS_WLAN_UPDATE){
					} else if(method == MediaBlocks::MBSERVER_FLOOR_CREATE){
					} else if(method == MediaBlocks::MBSERVER_FLOOR_DELETE){
					} else if(method == MediaBlocks::MBSERVER_FLOOR_GET){
					} else if(method == MediaBlocks::MBSERVER_FLOOR_GET_ALL){
					} else if(method == MediaBlocks::MBSERVER_FLOOR_UPDATE){
					} else if(method == MediaBlocks::MBSERVER_ROOM_CREATE){
						createRoom(obj);
					} else if(method == MediaBlocks::MBSERVER_ROOM_DELETE){
						deleteRoom(obj);
					} else if(method == MediaBlocks::MBSERVER_ROOM_GET){
						getRoom(obj);
					} else if(method == MediaBlocks::MBSERVER_ROOM_GET_ALL){
						getAllRooms(obj, response);
					} else if(method == MediaBlocks::MBSERVER_ROOM_UPDATE){
						updateRoom(obj);
					}

					writeResponse(response, id);
				}
			} else {
				qDebug() << "Kein JSON RPC Object\n";
			}
		}
	} else {
		_server_socket->write(QByteArray("Can't validate command!"));
	}
	_server_socket->disconnectFromHost();
	_server_socket->waitForDisconnected();
}
