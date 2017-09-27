/*
 * MediaBlocks
 *
 * Copyright (C) 2017 - 2019 Bruno Pierucki
 *
 * Author: Bruno Pierucki <bp@nebenwelten.net>
 */

//// begin includes
//// end includes

//// begin MediaBlocks specific includes
#include <configuration.hpp>

#include <QFile>
//// end MediaBlocks specific includes

//// begin using namespaces
//// end using namespaces

//// begin global definition
//// end global definition

//// begin extern declaration
//// end extern declaration

//// begin Configuration static definitions
//// end Configuration static definitions

//// begin Configuration static functions
//// end Configuration static functions

//// begin Configuration public member methods
/**********************************************************************************************************************/
/**
 *
 */
MediaBlocks::Configuration::Configuration(QObject *parent)
	:QObject(parent)
{
	load();
}
/**********************************************************************************************************************/
/**
 *
 */
MediaBlocks::Configuration::~Configuration()
{
}
/**********************************************************************************************************************/
/**
 * \brief Creates a new room
 *
 * Creates a new room on the device, if the server is active.
 *
 * \param obj The JSON object with the room information
 *
 * \return The new room object with all information.
 */
QJsonObject MediaBlocks::Configuration::createRoom(QJsonObject &obj) {
	QJsonObject device = _deviceSettings.object();
	QString name;
	QJsonObject result;
	QJsonValue value = obj["roomname"];

	if(value.isString()) {
		QString room = obj["roomname"].toString();
		QJsonValueRef value = device[MediaBlocks::ROOMLIST];
		if(value.isArray()) {
			QJsonArray array = value.toArray();
			QJsonArray::iterator it;
			int32_t id = -1;
			int32_t port = 6000;
			bool avail = false;
			for(it = array.begin(); it != array.end(); ++it) {
				QJsonValue ref = *it;
				if(ref.isObject()) {
					QJsonObject itobj = ref.toObject();
					if(itobj["name"].isString()) {
						name = itobj["name"].toString();
						if(itobj["port"].isDouble()) {
							// Checking Ports for the Rooms.
							if(itobj["port"].toInt() > port) {
								port = itobj["port"].toInt();
							}
							if(itobj["id"].isDouble()) {
								// Checking ID for the Rooms.
								if(itobj["id"].toInt() > id) {
									id = itobj["id"].toInt();
								}
								if(room == name) {
									avail = true;
									break;
								}
							}
						}
					}
				}
			}
			if(avail == false) {
				++port;
				++id;
				result.insert("name", room);
				result.insert("port", port);
				result.insert("id", id);

				array.append(result);
				device.remove(MediaBlocks::ROOMLIST);
				device.insert(MediaBlocks::ROOMLIST, QJsonValue(array));
			} else {
				createStatusMessage(result, Found);
			}
		}

		// Write modified Json Object to Json Document.
		_deviceSettings.setObject(device);
		// Save the document.
		save();
	} else {
		createStatusMessage(result, NotAvailable);
	}

	return result;
}
/**********************************************************************************************************************/
QJsonObject MediaBlocks::Configuration::deleteRoomById(QJsonObject obj) {
	QJsonObject result;
	QJsonObject device = _deviceSettings.object();
	QJsonValue value = device[MediaBlocks::ROOMLIST];
	QJsonValue id = obj["id"];
	if(value.isArray() && id.isDouble()) {
		QJsonArray array = value.toArray();
		QJsonArray::iterator it;
		bool avail = false;
		for(it = array.begin(); it != array.end(); ++it) {
			QJsonValue ref = *it;
			if(ref.isObject()) {
				QJsonObject room = ref.toObject();
				QJsonValue ref_id = room["id"];
				if(ref_id.isDouble()) {
					if(id.toInt() == ref_id.toInt()) {
						// Found Room to Delete
						array.erase(it);
						device.remove(MediaBlocks::ROOMLIST);
						device.insert(MediaBlocks::ROOMLIST, QJsonValue(array));

						_deviceSettings.setObject(device);
						save();
						createStatusMessage(result, Ok);
						avail = true;
						break;
					}
				}
			}
		}
		if(!avail) {
			createStatusMessage(result, NotFound);
		}
	} else {
		createStatusMessage(result, NotAvailable);
	}
	return result;
}
/**********************************************************************************************************************/
/**
 * @brief Actual configuration
 *
 * Gets the actual configuration of the device
 *
 * @return The actual configuration.
 */
QJsonDocument MediaBlocks::Configuration::getConfiguration() {
	return _deviceSettings;
}
/**********************************************************************************************************************/
/**
 * @brief Gets  a room
 *
 * Retrieves the information about a given with the given id
 * @param id The room id in the device
 *
 * @return The room with the given id, otherwise an empty object.
 */
QJsonObject MediaBlocks::Configuration::getRoomById(QJsonObject obj) {
	QJsonObject room;
	QJsonValue id = obj["id"];
	QJsonObject device = _deviceSettings.object();
	QJsonValue value = device[MediaBlocks::ROOMLIST];

	if(value.isArray() && id.isDouble()) {
		int32_t room_id = id.toInt();
		QJsonArray array = value.toArray();
		QJsonArray::iterator it;
		bool avail = false;
		for(it = array.begin(); it != array.end(); ++it) {
			QJsonValue ref = *it;
			if(ref.isObject()) {
				QJsonObject object = ref.toObject();
				QJsonValue refid = object["id"];
				if(refid.isDouble()) {
					if(refid.toInt() == room_id) {
						room = object;
						avail = true;
						break;
					}
				}
			}
		}
		if(!avail) {
			createStatusMessage(room, NotFound);
		}
	} else {
		createStatusMessage(room, NotAvailable);
	}
	return room;
}
/**********************************************************************************************************************/
/**
 * @brief Get all rooms
 *
 * Retrieves a list of all rooms that are available on the device
 *
 * @return The list of rooms
 */
QJsonObject MediaBlocks::Configuration::getRooms() {
	QJsonObject obj;
	QJsonObject device = _deviceSettings.object();
	if(device[MediaBlocks::ROOMLIST].isArray()) {
		QJsonArray array = device[MediaBlocks::ROOMLIST].toArray();
		obj.insert("rooms", array);
	}

	return obj;
}
/**********************************************************************************************************************/
QJsonObject MediaBlocks::Configuration::setDeviceName(QJsonObject &obj) {
	QJsonObject device;
	QJsonValue value = obj["devicename"];
	if(value.isString()) {
		QString name = value.toString();
		device = _deviceSettings.object();
		device.remove("devicename");
		device.insert("devicename", QJsonValue(name));

		_deviceSettings.setObject(device);
		save();
	} else {
		createStatusMessage(device, NotAvailable);
	}

	return device;
}
/**********************************************************************************************************************/
/**
 * @brief Reset the device
 *
 * Resets the device to the factory settings.
 *
 * @return The new configuration
 */
QJsonDocument MediaBlocks::Configuration::setFactoryReset() {
	QJsonObject device;
	device.insert("devicename", QJsonValue("MediaBlocks"));
	device.insert("music_db", QJsonValue("/mnt/sdcard/data/db/music.sqlite3"));
	device.insert("rooms", QJsonValue(QJsonArray()));
	device.insert("use_as_server", QJsonValue(false));

	_deviceSettings.setObject(device);
	save();

	return _deviceSettings;
}
/**********************************************************************************************************************/
QJsonObject MediaBlocks::Configuration::setMusicDb(QJsonObject obj) {
	QJsonObject device;
	QJsonValue value = obj["music_db"];
	if(value.isString()) {
		QString name = value.toString();
		device = _deviceSettings.object();
		device.remove("music_db");
		device.insert("music_db", QJsonValue(name));

		_deviceSettings.setObject(device);
		save();
	} else {
		createStatusMessage(device, NotAvailable);
	}

	return device;
}
/**********************************************************************************************************************/
/**
 * @brief Updates an existing room
 *
 * Updates an existing room with the given parameters
 *
 * @param room The room to update
 * @return The updated room object on success, otherwise an empty object .
 */
QJsonObject MediaBlocks::Configuration::updateRoom(QJsonObject room) {
	QJsonObject newroom;
	QJsonValue param = room;

	if(param.isObject()) {
		QJsonObject obj = param.toObject();
		QJsonValue room_id = obj["id"];
		if(room_id.isDouble()) {
			int32_t id = room_id.toInt();
			QJsonObject device = _deviceSettings.object();
			QJsonValue value = device[MediaBlocks::ROOMLIST];
			if(value.isArray()) {
				QJsonArray array = value.toArray();
				QJsonArray::iterator it;
				bool avail = false;

				for(it = array.begin(); it != array.end(); ++it) {
					QJsonValue ref = *it;
					if(ref.isObject()) {
						QJsonObject room = ref.toObject();
						QJsonValue ref_id = room["id"];
						if(ref_id.isDouble()) {
							if(id == ref_id.toInt()) {
								// Found room
								QJsonValue ref_port = room["port"];
								if(ref_port.isDouble()) {
									int32_t port = ref_port.toInt();
									array.erase(it);

									QJsonValue objname = obj["name"];
									if(objname.isString()) {
										newroom.insert("name", objname.toString());
										newroom.insert("port", port);
										newroom.insert("id", id);
										array.append(newroom);

										device.remove(MediaBlocks::ROOMLIST);
										device.insert(MediaBlocks::ROOMLIST, QJsonValue(array));
									}
									_deviceSettings.setObject(device);
									save();
									avail = true;
									break;
								}
							}
						}
					}
				}
				if(!avail) {
					createStatusMessage(newroom, NotFound);
				}
			}
		} else {
			createStatusMessage(newroom, NotAvailable);

		}
	}
	return newroom;
}
/**********************************************************************************************************************/
QJsonObject MediaBlocks::Configuration::useAsServer(QJsonObject obj) {
	QJsonObject device;
	QJsonValue value = obj["use_as_server"];
	if(value.isBool()) {
		bool server = value.toBool();
		device = _deviceSettings.object();
		device.remove("use_as_server");
		device.insert("use_as_server", QJsonValue(server));

		_deviceSettings.setObject(device);
		save();
	} else {
		createStatusMessage(device, NotAvailable);
	}

	return device;
}
//// end Configuration public member methods

//// begin Configuration public member methods (internal use only)
//// end Configuration public member methods (internal use only)

//// begin Configuration protected member methods
//// end Configuration protected member methods

//// begin Configuration protected member methods (internal use only)
//// begin Configuration protected member methods (internal use only)

//// begin Configuration private member methods
/**********************************************************************************************************************/
/**
 * @brief Clears the message object
 *
 * Erase all content of the given QJsonObject
 * @param message The messag to clear
 * @return True on success, false otherwise
 */
bool MediaBlocks::Configuration::clearMessage(QJsonObject &message) {
	if(!message.isEmpty()) {
		QJsonObject::iterator it;
		for(it = message.end(); it != message.begin(); --it) {
			message.erase(it);
		}
	}

	return message.isEmpty();
}
/**********************************************************************************************************************/
/**
 * @brief Creates an error Message
 * @param message
 */
void MediaBlocks::Configuration::createStatusMessage(QJsonObject &message, StatusCodes code) {
	QString msg;
	switch(code) {
		case Found: {
			msg = tr("Resource available!");
			break;
		}
		case NotFound: {
			msg = tr("Resource not found!");
			break;
		}
		case BadRequest: {
			msg = tr("Request contains an error!");
			break;
		}
		case NotAvailable: {
			msg = tr("Request is not available!");
			break;
		}
		case Ok: {
			msg = tr("Request processed successfully");
			break;
		}
	}

	message.insert("code", QJsonValue(code));
	message.insert("message", msg);
}
/**********************************************************************************************************************/
/**
 * @brief Loads the configuration
 *
 * Loads the comfiguration of the device
 *
 * @return True if successful, false otherwise
 */
bool MediaBlocks::Configuration::load() {
	QJsonParseError error;
	bool result = false;
	QFile json(MediaBlocks::MEDIA_BLOCKS);
	if((result = json.open(QIODevice::ReadWrite))) {
		_deviceSettings = QJsonDocument::fromJson(json.readAll(), &error);
		json.close();
	}

	return result;
}
/**********************************************************************************************************************/
/**
 * @brief Save configuration
 *
 * Saves the configuration of the device
 *
 * @return True if successful, false otherwise.
 */
bool MediaBlocks::Configuration::save() {
	bool result = false;
	QFile json(MediaBlocks::MEDIA_BLOCKS);
	if((result = json.open(QIODevice::ReadWrite | QIODevice::Truncate))) {
		json.write(_deviceSettings.toJson());
		json.close();
		result = true;
		emit changed();
	}

	return result;
}
//// end Configuration private member methods

//// begin Configuration public slots
//// end Configuration public slots

//// begin Configuration protected slots
//// end Configuration protected slots

//// begin Configuration private slots
//// end Configuration private slots

//// begin signal documentation
/**
 * @fn void changed()
 * @brief Signal when configuration is changed
 *
 * Thsi signal is emitted, when the configuration of the device was changed successfully.
 */
//// end signal documentation
