#include "IntegrationTests.h"
#include "ObjectList.h"
#include "ItemInventario.h"
#include "IntegrationTests.h"
#include "MainCharacter.h"
#include "GOUnlockeable.h"

void PickObjectListTest::pickObjectTest()
{
	player->setPosition({ 0, 0 });
	item->setPosition({ 0, 0 });
	item->setActive(true);

	int tam1 = player->getList()->getLength();
	pickObject();
	int tam2 = player->getList()->getLength();

	CPPUNIT_ASSERT(tam2 == tam1 - 1);
	/*if (tam1 + 1 == tam2) {
		std::cout << "PickObjectTest: OK" << std::endl;
	}
	else {
		std::cout << "PickObjectTest: failed" << std::endl;
	}*/
}

void PickObjectListTest::pickInactiveObjectTest()
{
	player->setPosition({ 0, 0 });
	item->setPosition({ 0, 0 });
	item->setActive(false);

	int tam1 = player->getList()->getLength();
	pickObject();
	int tam2 = player->getList()->getLength();

	CPPUNIT_ASSERT(tam2 == tam1);
	/*if (tam1 == tam2) {
		std::cout << "PickInactiveObjectTest: OK" << std::endl;
	}
	else {
		std::cout << "PickInactiveObjectTest: failed" << std::endl;
	}*/
}

void PickObjectListTest::pickObject()
{
	if (item->inRange(player->getPosition().getX())) {
		item->act(player);
	}
}

PickObjectListTest::PickObjectListTest()
{
	setUp();
}

void PickObjectListTest::setUp()
{
	objectList = new ObjectList();
	player = new MainCharacter(objectList);
	item = new ItemInventario(nullptr, 0, 0, 10, 10, "test item", "test item", nullptr);
}

void PickObjectListTest::tearDown()
{
	if (objectList != nullptr) delete objectList; objectList = nullptr;
	if (player != nullptr) delete player; player = nullptr;
}

CppUnit::Test* PickObjectListTest::suite()
{
	CppUnit::TestSuite* suite = new CppUnit::TestSuite();
	suite->addTest(new CppUnit::TestCaller<PickObjectListTest>("pickObjectTest_Integration", &PickObjectListTest::pickObjectTest));
	suite->addTest(new CppUnit::TestCaller<PickObjectListTest>("pickInactiveObjectTest_Integration", &PickObjectListTest::pickInactiveObjectTest));
	
	return suite;
}

PickObjectListTest::~PickObjectListTest()
{
	tearDown();
}

void UseObjectTest::useObject()
{
	item->use(player);
	unlockable->act(player);
}

void UseObjectTest::useObjectCorrectTag()
{
	player->setPosition({ 0, 0 });
	unlockable->setPosition({ 0, 0 });
	unlockable->setKey("test item");
	unlockable->setOpened(false);
	item->setTag("test item");

	useObject();

	CPPUNIT_ASSERT(unlockable->isOpened());
	/*if (unlockable->isOpened()) {
		std::cout << "UseObjectCorrectTag: OK" << std::endl;
	}
	else {
		std::cout << "UseObjectCorrectTag: failed" << std::endl;
	}*/
}

void UseObjectTest::useObjectIncorrectTag()
{
	player->setPosition({ 0, 0 });
	unlockable->setPosition({ 0, 0 });
	unlockable->setKey("no test item");
	unlockable->setOpened(false);
	item->setTag("test item");

	useObject();

	CPPUNIT_ASSERT(!unlockable->isOpened());
	/*if (!unlockable->isOpened()) {
		std::cout << "UseObjectIncorrectTag: OK" << std::endl;
	}
	else {
		std::cout << "UseObjectIncorrectTag: failed" << std::endl;
	}*/
}

UseObjectTest::UseObjectTest()
{
	setUp();
}

void UseObjectTest::setUp()
{
	player = new MainCharacter();
	item = new ItemInventario(nullptr, 0, 0, 10, 10, "test item", "test item", nullptr);
	unlockable = new GOUnlockeable(nullptr, 0, 0, 10, 10, nullptr, "test item");
}

void UseObjectTest::tearDown()
{
	if (item != nullptr){
		delete item; 
		item = nullptr;
	}

	if (player != nullptr){ 
		delete player; 
		player = nullptr; 
	}
}

CppUnit::Test* UseObjectTest::suite()
{
	CppUnit::TestSuite* suite = new CppUnit::TestSuite();
	suite->addTest(new CppUnit::TestCaller<UseObjectTest>("pickObjectTest_Integration", &UseObjectTest::useObjectCorrectTag));
	suite->addTest(new CppUnit::TestCaller<UseObjectTest>("pickInactiveObjectTest_Integration", &UseObjectTest::useObjectIncorrectTag));

	return suite;
}

UseObjectTest::~UseObjectTest()
{
	tearDown();
}
