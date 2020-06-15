#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

class ObjectList;
class MainCharacter;
class ItemInventario;
class GOUnlockeable;


class PickObjectListTest: public CppUnit::TestFixture {
private:
	MainCharacter* player;
	ObjectList* objectList;
	ItemInventario* item;

	void pickObject();
	void pickObjectTest();
	void pickInactiveObjectTest();

public:
	PickObjectListTest();
	~PickObjectListTest();

	virtual void setUp();
	virtual void tearDown();


	static CppUnit::Test* suite();
};

class UseObjectTest : public CppUnit::TestFixture {
private:
	MainCharacter* player;
	ItemInventario* item;
	GOUnlockeable* unlockable;

	void useObject();
	void useObjectCorrectTag();
	void useObjectIncorrectTag();

public:
	UseObjectTest();
	~UseObjectTest();

	virtual void setUp();
	virtual void tearDown();

	static CppUnit::Test* suite();
};