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
 * @brief Creates a new room
 *
 * Creates a new room on the device, if the server is active.
 *
 * @param room The room to create
 *
 * @return The new room object with all information.
 */
QJsonObject MediaBlocks::Configuration::createRoom(QString &room) {
	QJsonObject device = _deviceSettings.object();
	int32_t port = 6000;
	int32_t id = -1;
	QString name;
	bool avail = false;
	QJsonObject result;
	QJsonValueRef value = device[MediaBlocks::ROOMLIST];
	if(value.isArray()) {
		QJsonArray array = value.toArray();
		QJsonArray::iterator it;
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
		}
	}

	// Write modified Json Object to Json Document.
	_deviceSettings.setObject(device);
	// Save the document.
	save();

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
QJsonObject MediaBlocks::Configuration::getRoomById(int32_t id) {
	int32_t room_id = id;
	QJsonObject room;
	QJsonObject device = _deviceSettings.object();
	QJsonValue value = device[MediaBlocks::ROOMLIST];

	if(value.isArray()) {
		QJsonArray array = value.toArray();
		QJsonArray::iterator it;
		for(it = array.begin(); it != array.end(); ++it) {
			QJsonValue ref = *it;
			if(ref.isObject()) {
				QJsonObject object = ref.toObject();
				QJsonValue refid = object["id"];
				if(refid.isDouble()) {
					if(refid.toInt() == room_id) {
						room = object;
						break;
					}
				}
			}
		}
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
								}
							}
						}
					}
				}
			}
		}
	}
	return newroom;
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
