#ifndef HEADER_GUARD_MediaBlocks_MediaBlocks__INTERFACE_HPP
#define HEADER_GUARD_MediaBlocks_MediaBlocks__INTERFACE_HPP

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
 * \class Interface
 * \ingroup group_interfaces
 *
 * \brief
 *
 */
class Interface : public QObject
{
	Q_OBJECT
	//// begin Interface public member methods
public:
	explicit Interface(QObject *parent = nullptr);
	virtual ~Interface();
	//// end Interface public member methods

	//// begin Interface public member methods (internal use only)
public:
	//// end Interface public member methods (internal use only)

	//// begin Interface protected member methods
protected:
	//// end Interface protected member methods

	//// begin Interface protected member methods (internal use only)
protected:
	//// begin Interface protected member methods (internal use only)

	//// begin Interface private member methods
private:
	//// end Interface private member methods

	//// begin Interface public member
public:
	//// end Interface public member

	//// begin Interface protected member
protected:
	//// end Interface protected member

	//// begin Interface private member
private:
	//// end Interface private member
};
}    // namespace MediaBlocks
#endif // HEADER_GUARD_MediaBlocks_MediaBlocks__INTERFACE_HPP
