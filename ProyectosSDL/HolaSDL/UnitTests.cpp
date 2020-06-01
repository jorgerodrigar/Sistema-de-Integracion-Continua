#include "UnitTests.h"
#include "ObjectList.h"
#include "ItemInventario.h"
#include "Entity.h"

void ObjectListTest::addItem(std::string tag, bool permanent)
{
	ItemInventario item(nullptr, 0, 0, 10, 10, tag, tag, nullptr, permanent);
	objectList->addItem(&item);
}

void ObjectListTest::addItemTest()
{
	unsigned char tam1 = objectList->getLength();
	addItem("test item");
	unsigned char tam2 = objectList->getLength();

	CPPUNIT_ASSERT(tam2 == tam1 + 1);
}

void ObjectListTest::addPermanentItemTest()
{
	unsigned char tam1 = objectList->getLength();
	addItem("permanent test item", true);
	unsigned char tam2 = objectList->getLength();

	CPPUNIT_ASSERT(tam2 == tam1 + 1);
}

void ObjectListTest::deleteItemTest()
{
	addItem("test item");
	unsigned char tam1 = objectList->getLength();
	objectList->deleteItem("test item");
	unsigned char tam2 = objectList->getLength();

	CPPUNIT_ASSERT(tam2 == tam1 - 1);
}

void ObjectListTest::deletePermanentItemTest()
{
	addItem("permanent test item", true);
	unsigned char tam1 = objectList->getLength();
	objectList->deleteItem("permanent test item");
	unsigned char tam2 = objectList->getLength();

	CPPUNIT_ASSERT(tam2 == tam1 - 1);
}

void ObjectListTest::deleteUnexistentItemTest()
{
	addItem("existent test item", true);
	unsigned char tam1 = objectList->getLength();
	objectList->deleteItem("unexistent test item");
	unsigned char tam2 = objectList->getLength();

	CPPUNIT_ASSERT(tam2 == tam1);
}

void ObjectListTest::deleteFromEmptyListTest()
{
	unsigned char tam1 = objectList->getLength();
	objectList->deleteItem("unexistent test item");
	unsigned char tam2 = objectList->getLength();

	CPPUNIT_ASSERT(tam2 == tam1);
}

void ObjectListTest::setUp()
{
	objectList = new ObjectList();
}

void ObjectListTest::tearDown()
{
	delete objectList;
}

CppUnit::Test* ObjectListTest::suite()
{
	CppUnit::TestSuite* suite = new CppUnit::TestSuite();
	suite->addTest(new CppUnit::TestCaller<ObjectListTest>("addToListTest", &ObjectListTest::addItemTest));
	suite->addTest(new CppUnit::TestCaller<ObjectListTest>("addPermanentToListTest", &ObjectListTest::addPermanentItemTest));
	suite->addTest(new CppUnit::TestCaller<ObjectListTest>("deleteListTest", &ObjectListTest::deleteItemTest));
	suite->addTest(new CppUnit::TestCaller<ObjectListTest>("deletePermanentListTest", &ObjectListTest::deletePermanentItemTest));
	suite->addTest(new CppUnit::TestCaller<ObjectListTest>("deleteUnexistentListTest", &ObjectListTest::deleteUnexistentItemTest));
	suite->addTest(new CppUnit::TestCaller<ObjectListTest>("deleteFromEmptyListTest", &ObjectListTest::deleteFromEmptyListTest));

	return suite;
}

//-----------------------------------------------------------------------------------------------------

void MoveEntityTest::positionTest()
{
	double x = rand() % 100;
	double y = rand() % 100;

	entity->setPosition({ x, y });
	Vector2D pos = entity->getPosition();

	CPPUNIT_ASSERT(pos.getX() == x && pos.getY() == y);
}

void MoveEntityTest::velocityTest()
{
	double x = rand() % 100;
	double y = rand() % 100;

	entity->setVelocity({ x, y });
	Vector2D vel = entity->getVelocity();

	CPPUNIT_ASSERT(vel.getX() == x && vel.getY() == y);
}

void MoveEntityTest::setUp()
{
	entity = new Entity();
}

void MoveEntityTest::tearDown()
{
	delete entity;
}

CppUnit::Test* MoveEntityTest::suite()
{
	CppUnit::TestSuite* suite = new CppUnit::TestSuite();
	suite->addTest(new CppUnit::TestCaller<MoveEntityTest>("positionTest", &MoveEntityTest::positionTest));
	suite->addTest(new CppUnit::TestCaller<MoveEntityTest>("velocityTest", &MoveEntityTest::velocityTest));

	return suite;
}
