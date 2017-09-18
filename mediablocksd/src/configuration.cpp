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
		qDebug("Array");
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
