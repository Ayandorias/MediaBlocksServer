#ifndef HEADER_GUARD_MediaBlocks_MediaBlocks__CONFIGURATION_HPP
#define HEADER_GUARD_MediaBlocks_MediaBlocks__CONFIGURATION_HPP

/*
 * MediaBlocks
 *
 * Copyright (C) 2011 - 2015 Bruno Pierucki
 *
 * Author: Bruno Pierucki <bp@nebenwelten.net>
 *
 */
//// begin includes
//// end includes

//// begin MediaBlocks specific includes
#include <mediablocks.hpp>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QObject>
//// end MediaBlocks specific includes

//// begin using namespaces
//// end using namespaces

//// begin global definition
//// end global definition

//// begin forward declarations
//// end forward declarations

//// begin extern declaration
//// end extern declaration

namespace MediaBlocks
{
/**
 * \class Configuration
 * \ingroup group_configuration_data
 *
 * \brief
 *
 */
class Configuration : public QObject
{
	//// begin Configuration public member methods
public:
	/// Constructor
	Configuration(QObject *parent);
	/// Destructor
	virtual ~Configuration();

	QString getTestString();
	//// end Configuration public member methods

	//// begin Configuration public member methods (internal use only)
public:
	//// end Configuration public member methods (internal use only)

	//// begin Configuration protected member methods
protected:
	//// end Configuration protected member methods

	//// begin Configuration protected member methods (internal use only)
protected:
	//// begin Configuration protected member methods (internal use only)

	//// begin Configuration private member methods
private:
	/// Loads the system configuration
	bool loadConfiguration();
	//// end Configuration private member methods

	//// begin Configuration public member
public:
	//// end Configuration public member

	//// begin Configuration protected member
protected:
	//// end Configuration protected member

	//// begin Configuration private member
private:
	QJsonDocument _deviceSettings;
	//// end Configuration private member
};
}    // namespace MediaBlocks
#endif // HEADER_GUARD_MediaBlocks_MediaBlocks__CONFIGURATION_HPP
