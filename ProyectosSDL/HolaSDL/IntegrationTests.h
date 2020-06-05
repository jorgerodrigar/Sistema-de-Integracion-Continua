#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

class ObjectList;
class MainCharacter;
class ItemInventario;
class GOUnlockeable;

class IntegrationTest {
public:
	virtual void runTests() = 0;

	virtual void setUp() = 0;
	virtual void tearDown() = 0;
};

class PickObjectListTest: public IntegrationTest {
private:
	MainCharacter* player;
	ObjectList* objectList;
	ItemInventario* item;

	void pickObject();
	void pickObjectTest();
	void pickInactiveObjectTest();

public:
	PickObjectListTest();
	virtual void runTests();
	virtual void setUp();
	virtual void tearDown();
	~PickObjectListTest();
};

class UseObjectTest : public IntegrationTest {
private:
	MainCharacter* player;
	ItemInventario* item;
	GOUnlockeable* unlockable;

	void useObject();
	void useObjectCorrectTag();
	void useObjectIncorrectTag();

public:
	UseObjectTest();
	virtual void runTests();
	virtual void setUp();
	virtual void tearDown();
	~UseObjectTest();
};