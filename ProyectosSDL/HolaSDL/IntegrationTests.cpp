#include "IntegrationTests.h"
#include "ObjectList.h"
#include "ItemInventario.h"
#include "IntegrationTests.h"
#include "MainCharacter.h"

void PickObjectListTest::pickObjectTest()
{
	player->setPosition({ 0, 0 });
	item->setPosition({ 0, 0 });
	item->setActive(true);

	int tam1 = player->getList()->getLength();
	pickObject();
	int tam2 = player->getList()->getLength();

	if (tam1 + 1 == tam2) {
		std::cout << "PickObjectTest: OK" << std::endl;
	}
	else {
		std::cout << "PickObjectTest: failed" << std::endl;
	}
}

void PickObjectListTest::pickInactiveObjectTest()
{
	player->setPosition({ 0, 0 });
	item->setPosition({ 0, 0 });
	item->setActive(false);

	int tam1 = player->getList()->getLength();
	pickObject();
	int tam2 = player->getList()->getLength();

	if (tam1 == tam2) {
		std::cout << "PickInactiveObjectTest: OK" << std::endl;
	}
	else {
		std::cout << "PickInactiveObjectTest: failed" << std::endl;
	}
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

void PickObjectListTest::runTests()
{
	pickObjectTest();
	pickInactiveObjectTest();
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

PickObjectListTest::~PickObjectListTest()
{
	tearDown();
}
