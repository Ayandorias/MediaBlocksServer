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
		/// Constructor
		MBConfigTest();
		/// Destructor
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
		//// end MBConfigTest private member methods

	private slots:
		void test_case1();

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
 * Copyright (C) 2011 - 2015 Bruno Pierucki
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
/**************************************************************************************************/
/**
 *
 */
MediaBlocks::MBConfigTest::MBConfigTest()
	:QObject()
{
}

/**************************************************************************************************/
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
//// end MBConfigTest private member methods

//// begin MBConfigTest public slots
//// end MBConfigTest public slots

//// begin MBConfigTest protected slots
//// end MBConfigTest protected slots

//// begin MBConfigTest private slots
void MediaBlocks::MBConfigTest::test_case1() {
	MediaBlocks::Configuration config(this);
	QString testString = config.getTestString();

	QVERIFY(testString == "Das ist ein Test");
}
//// end MBConfigTest private slots


QTEST_APPLESS_MAIN(MediaBlocks::MBConfigTest)

#include "mbconfigtest.moc"
