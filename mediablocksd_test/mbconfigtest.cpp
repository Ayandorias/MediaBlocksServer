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
#include <configuration.hpp>
#include <mediablocks.hpp>
#include <QObject>
#include <QtTest>
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
 * \class MBConfigTest
 * \ingroup group_test_configuration
 *
 * \brief
 *
 */
	class MBConfigTest : public QObject
	{
		Q_OBJECT
		//// begin MBConfigTest public member methods
	public:
		MBConfigTest();
		virtual ~MBConfigTest();
		//// end MBConfigTest public member methods

		//// begin MBConfigTest public member methods (internal use only)
	public:
		//// end MBConfigTest public member methods (internal use only)

		//// begin MBConfigTest protected member methods
	protected:
		//// end MBConfigTest protected member methods

		//// begin MBConfigTest protected member methods (internal use only)
	protected:
		//// begin MBConfigTest protected member methods (internal use only)

		//// begin MBConfigTest private member methods
	private:
		QString getRooms();
		//// end MBConfigTest private member methods

	private slots:
		void factoryReset();
		void checkEmptyRoomList();
		void createNewRoom();
		void createNewRoomExists();
		void checkAllRooms();
		void updateRoom();
		void updateRoomNotExist();
		void getRoomById();
		void getRoomByIdNotExist();

		//// begin MBConfigTest public member
	public:
		//// end MBConfigTest public member

		//// begin MBConfigTest protected member
	protected:
		//// end MBConfigTest protected member

		//// begin MBConfigTest private member
	private:
		//// end MBConfigTest private member
	};
}    // namespace MediaBlocks


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
//// end MediaBlocks specific includes

//// begin using namespaces
//// end using namespaces

//// begin global definition
//// end global definition

//// begin extern declaration
//// end extern declaration

//// begin MBConfigTest static definitions
//// end MBConfigTest static definitions

//// begin MBConfigTest static functions
//// end MBConfigTest static functions

//// begin MBConfigTest public member methods
/**********************************************************************************************************************/
/**
 *
 */
MediaBlocks::MBConfigTest::MBConfigTest()
	:QObject()
{
}
/**********************************************************************************************************************/
/**
 *
 */
MediaBlocks::MBConfigTest::~MBConfigTest()
{
}
//// end MBConfigTest public member methods

//// begin MBConfigTest public member methods (internal use only)
//// end MBConfigTest public member methods (internal use only)

//// begin MBConfigTest protected member methods
//// end MBConfigTest protected member methods

//// begin MBConfigTest protected member methods (internal use only)
//// begin MBConfigTest protected member methods (internal use only)

//// begin MBConfigTest private member methods
QString MediaBlocks::MBConfigTest::getRooms() {
	MediaBlocks::Configuration config(this);
	QJsonObject obj = config.getRooms();
	QJsonDocument doc(obj);
	QString compact = doc.toJson(QJsonDocument::Compact);

	qDebug() << compact;
	return compact;
}
//// end MBConfigTest private member methods

//// begin MBConfigTest public slots
//// end MBConfigTest public slots

//// begin MBConfigTest protected slots
//// end MBConfigTest protected slots

//// begin MBConfigTest private slots
/**********************************************************************************************************************/
void MediaBlocks::MBConfigTest::factoryReset() {
	MediaBlocks::Configuration config(this);
	QJsonDocument doc = config.setFactoryReset();
	QString compact = doc.toJson(QJsonDocument::Compact);

	qDebug() << compact;
	QVERIFY(QString(compact) == "{\"devicename\":\"MediaBlocks\",\"music_db\":\"/mnt/sdcard/data/db/music.sqlite3\",\"rooms\":[],\"use_as_server\":false}");
}
/**********************************************************************************************************************/
void MediaBlocks::MBConfigTest::checkEmptyRoomList() {
	QString compact = getRooms();
	QVERIFY(QString(compact) == "{\"rooms\":[]}");
}
/**********************************************************************************************************************/
void MediaBlocks::MBConfigTest::createNewRoom() {
	MediaBlocks::Configuration config(this);

	QString room = "Office";
	QJsonObject newRoom = config.createRoom(room);
	QJsonDocument doc(newRoom);
	QString compact = doc.toJson(QJsonDocument::Compact);

	qDebug() << compact;
	QVERIFY(QString(compact) == "{\"id\":0,\"name\":\"Office\",\"port\":6001}");

	room = "Living Room";
	newRoom = config.createRoom(room);
	doc.setObject(newRoom);
	compact = doc.toJson(QJsonDocument::Compact);

	qDebug() << compact;
	QVERIFY(QString(compact) == "{\"id\":1,\"name\":\"Living Room\",\"port\":6002}");

}
/**********************************************************************************************************************/
void MediaBlocks::MBConfigTest::createNewRoomExists() {
	MediaBlocks::Configuration config(this);

	QString room = "Office";
	QJsonObject newRoom = config.createRoom(room);
	QVERIFY(newRoom.isEmpty() == true);
}
/**********************************************************************************************************************/
void MediaBlocks::MBConfigTest::checkAllRooms() {
	QString compact = getRooms();
	QVERIFY(QString(compact) == "{\"rooms\":[{\"id\":0,\"name\":\"Office\",\"port\":6001},{\"id\":1,\"name\":\"Living Room\",\"port\":6002}]}");
}
/**********************************************************************************************************************/
void MediaBlocks::MBConfigTest::updateRoom() {
	MediaBlocks::Configuration config(this);
	QJsonDocument doc = QJsonDocument::fromJson("{\"id\":0,\"name\":\"Bedroom\"}");
	QJsonObject room = doc.object();

	QJsonObject newRoom = config.updateRoom(room);
	doc.setObject(newRoom);
	QString compact = doc.toJson(QJsonDocument::Compact);
	qDebug() << compact;
	QVERIFY(QString(compact) == "{\"id\":0,\"name\":\"Bedroom\",\"port\":6001}");
}
/**********************************************************************************************************************/
void MediaBlocks::MBConfigTest::updateRoomNotExist() {
	MediaBlocks::Configuration config(this);
	QJsonDocument doc = QJsonDocument::fromJson("{\"id\":12,\"name\":\"Bedroom\"}");
	QJsonObject room = doc.object();

	QJsonObject noRoom = config.updateRoom(room);
	QVERIFY(noRoom.isEmpty() == true);
}
/**********************************************************************************************************************/
void MediaBlocks::MBConfigTest::getRoomById() {
	MediaBlocks::Configuration config(this);
	QJsonObject room = config.getRoomById(0);
	QJsonDocument doc(room);
	QString compact = doc.toJson(QJsonDocument::Compact);
	qDebug() << compact;
	QVERIFY(QString(compact) == "{\"id\":0,\"name\":\"Bedroom\",\"port\":6001}");
}
/**********************************************************************************************************************/
void MediaBlocks::MBConfigTest::getRoomByIdNotExist() {
	MediaBlocks::Configuration config(this);
	QJsonObject room = config.getRoomById(100);
	QVERIFY(room.isEmpty() == true);
}
//// end MBConfigTest private slots


QTEST_APPLESS_MAIN(MediaBlocks::MBConfigTest)

#include "mbconfigtest.moc"
