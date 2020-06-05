
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
#include "IntegrationTests.h"
#include <list>

using namespace std;

int main(int argc, char* argv[]){

	if (argc <= 1 || std::string(argv[1]) != "TEST") {

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
	else {
		// UNIT TESTS
		std::cout << std::endl << std::endl << "UNIT TESTS" << std::endl;
		CppUnit::TestResultCollector result;

		CppUnit::TestResult controller;
		controller.addListener(&result);

		CppUnit::BriefTestProgressListener progress;
		controller.addListener(&progress);

		std::filebuf fb;
		fb.open("..\\logs\\testOutput.txt", std::ios::out);
		std::ostream os(&fb);

		CppUnit::TestRunner runner;
		runner.addTest(ObjectListTest::suite());
		runner.addTest(MoveEntityTest::suite());

		runner.run(controller);

		CppUnit::TextOutputter textOutputter(&result, os);
		textOutputter.write();
		fb.close();

		// INTEGRATION TESTS
		std::cout << std::endl << std::endl << "INTEGRATION TESTS" << std::endl;
		list<IntegrationTest*> integrationTests;

		PickObjectListTest pickTest;
		integrationTests.push_back(&pickTest);

		UseObjectTest useTest;
		integrationTests.push_back(&useTest);

		for (IntegrationTest* test : integrationTests) {
			test->runTests();
		}
	}
	
	return 0;
}