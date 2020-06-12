
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "SDLApp.h"
#include <Tracker.h>
#include <ITrackerAsset.h>
#include <FilePersistence.h>
#include <ServerPersistence.h>
#include <JsonSerializer.h>
#include <CSVSerializer.h>
#include "UnitTests.h"
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/XmlOutputter.h>
#include "IntegrationTests.h"
#include <list>

using namespace std;

int main(int argc, char* argv[]){

	if (argc <= 1 || (std::string(argv[1]) != "UNIT_TEST" && std::string(argv[1]) != "INTEGRATION_TEST")) {

		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		// trackerAssets -> recogemos eventos de dificultad, claridad y sesion
		DifficultyTracker difficultyTracker;
		ClarityTracker clarityTracker;
		SessionTracker sessionTracker;

		// serializadores -> formatos json y csv
		JsonSerializer jsonSerializer;
		CSVSerializer csvSerializer;

		// persistencias -> en archivo y servidor
		FilePersistence filePersistence({&jsonSerializer, &csvSerializer});
		ServerPersistence serverPersistence({ &jsonSerializer, &csvSerializer });

		// inicializacion del sistema de telemetria
		Tracker::GetInstance().Init({&difficultyTracker, &clarityTracker, &sessionTracker }, { &serverPersistence, &filePersistence });

		SDLApp g(1280, 720);
		g.run();
		g.closeSDL();

		Tracker::GetInstance().End();

		filePersistence.release();
		serverPersistence.release();
		_CrtDumpMemoryLeaks(); //esta instruccion le vale a Diego para ver la basura. No quiteis el comentario pls T_T
	}
	else if(std::string(argv[1]) == "UNIT_TEST"){
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
	}
	else if (std::string(argv[1]) == "INTEGRATION_TEST") {
		// INTEGRATION TESTS
		std::cout << std::endl << std::endl << "INTEGRATION TESTS" << std::endl;
		CppUnit::TestResultCollector result;

		CppUnit::TestResult controller;
		controller.addListener(&result);

		CppUnit::BriefTestProgressListener progress;
		controller.addListener(&progress);

		std::filebuf fb;
		fb.open("..\\logs\\integrationTestsOutput.txt", std::ios::out);
		std::ostream os(&fb);

		CppUnit::TestRunner runner;
		runner.addTest(PickObjectListTest::suite());
		runner.addTest(UseObjectTest::suite());

		runner.run(controller);
		CppUnit::TextOutputter textOutputter(&result, os);
		textOutputter.write();
		fb.close();
	}
	
	return 0;
}