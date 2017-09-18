#include <QString>
#include <QtTest>

class RPCInterfaceTest : public QObject
{
	Q_OBJECT

public:
	RPCInterfaceTest();

private Q_SLOTS:
	void initTestCase();
	void cleanupTestCase();
	void testCase1_data();
	void testCase1();
};

RPCInterfaceTest::RPCInterfaceTest(){
}

void RPCInterfaceTest::initTestCase(){
}

void RPCInterfaceTest::cleanupTestCase(){
}

void RPCInterfaceTest::testCase1_data(){
	QTest::addColumn<QString>("data");
	QTest::newRow("0") << QString();
}

void RPCInterfaceTest::testCase1(){
	QFETCH(QString, data);
	QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(RPCInterfaceTest)

#include "rpcinterfacetest.moc"
