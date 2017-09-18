#ifndef HEADER_GUARD_MediaBlocks_MediaBlocks__RPCINTERFACE_HPP
#define HEADER_GUARD_MediaBlocks_MediaBlocks__RPCINTERFACE_HPP

/*
 * MediaBlocks
 *
 * Copyright (C) 2017 - 2019 Bruno Pierucki
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
 * \class RPCInterface
 * \ingroup group_connection_rpc
 *
 * \brief
 *
 */
class RPCInterface : public QObject
{
	//// begin RPCInterface public member methods
public:
	/// Constructor
	RPCInterface(QObject *parent);
	/// Destructor
	virtual ~RPCInterface();
	//// end RPCInterface public member methods

	//// begin RPCInterface public member methods (internal use only)
public:
	//// end RPCInterface public member methods (internal use only)

	//// begin RPCInterface protected member methods
protected:
	//// end RPCInterface protected member methods

	//// begin RPCInterface protected member methods (internal use only)
protected:
	//// begin RPCInterface protected member methods (internal use only)

	//// begin RPCInterface private member methods
private:
	//// end RPCInterface private member methods

	//// begin RPCInterface public member
public:
	//// end RPCInterface public member

	//// begin RPCInterface protected member
protected:
	//// end RPCInterface protected member

	//// begin RPCInterface private member
private:
	//// end RPCInterface private member
};
}    // namespace MediaBlocks
#endif // HEADER_GUARD_MediaBlocks_MediaBlocks__RPCINTERFACE_HPP
