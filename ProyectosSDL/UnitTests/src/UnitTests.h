#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

class ObjectList;

class ObjectListTest : public CppUnit::TestFixture {
private:
	ObjectList* objectList;

	// adds an item to the object list
	void addItem(std::string tag, bool permanent = false);
	void addItemTest();
	void addPermanentItemTest();
	void deleteItemTest();
	void deletePermanentItemTest();
	void deleteUnexistentItemTest();
	void deleteFromEmptyListTest();

public:
	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};

class Entity;

class MoveEntityTest : public CppUnit::TestFixture {
private:
	Entity* entity;

	void positionTest();
	void velocityTest();

public:
	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};