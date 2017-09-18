/*
 * MediaBlocks
 *
 * Copyright (C) 2011 - 2015 Bruno Pierucki
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
/**************************************************************************************************/
/**
 *
 */
MediaBlocks::Configuration::Configuration(QObject *parent)
	:QObject(parent)
{
	loadConfiguration();
}

/**************************************************************************************************/
/**
 *
 */
MediaBlocks::Configuration::~Configuration()
{
}


QString MediaBlocks::Configuration::getTestString() {
	return QString("Das ist ein Test");
}
//// end Configuration public member methods

//// begin Configuration public member methods (internal use only)
//// end Configuration public member methods (internal use only)

//// begin Configuration protected member methods
//// end Configuration protected member methods

//// begin Configuration protected member methods (internal use only)
//// begin Configuration protected member methods (internal use only)

//// begin Configuration private member methods
/***************************************************************************************************/
/**
 *
 */
bool MediaBlocks::Configuration::loadConfiguration() {
	QJsonParseError error;
	QFile json(MediaBlocks::MEDIA_BLOCKS);
	if(json.open(QIODevice::ReadWrite)) {
		_deviceSettings = QJsonDocument::fromJson(json.readAll(), &error);
		json.close();
	}
}
//// end Configuration private member methods

//// begin Configuration public slots
//// end Configuration public slots

//// begin Configuration protected slots
//// end Configuration protected slots

//// begin Configuration private slots
//// end Configuration private slots
