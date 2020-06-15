
#include <iostream>
#include "UnitTests.h"
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/XmlOutputter.h>

using namespace std;

int main(int argc, char* argv[]) {

	// UNIT TESTS
	std::cout << std::endl << std::endl << "UNIT TESTS" << std::endl;
	CppUnit::TestResultCollector result;

	CppUnit::TestResult controller;
	controller.addListener(&result);

	CppUnit::BriefTestProgressListener progress;
	controller.addListener(&progress);

	CppUnit::TestRunner runner;
	runner.addTest(ObjectListTest::suite());
	runner.addTest(MoveEntityTest::suite());
	runner.run(controller);

	std::filebuf fb;
	fb.open("..\\logs\\unitTestsOutput.txt", std::ios::out);
	std::ostream textOs(&fb);
	CppUnit::TextOutputter textOutputter(&result, textOs);
	textOutputter.write();
	fb.close();

	fb.open("..\\logs\\unitTestsOutput.xml", std::ios::out);
	std::ostream xmlOs(&fb);
	CppUnit::XmlOutputter xmlOutputter(&result, xmlOs);
	xmlOutputter.write();
	fb.close();

	return 0;
}