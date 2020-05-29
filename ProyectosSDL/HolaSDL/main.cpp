
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
#include <string>
#include <list>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace std;

class Task {

public:
	int id;
	std::string title;
	Task(int id, std::string title) {
		if (id > 1000) {
			this->id = id % 1000;
		}
		else {
			this->id = id;
		}
		title = title;
	}
};

// implementa interfaz
class TaskTest : public CppUnit::TestFixture {
	Task* t;

public:
	void setUp() {
		t = new Task(10, "kk");
	}

	void tearDown() {
		delete t;
	}

	void testTaskAttributes() {
		CPPUNIT_ASSERT(t->id == 10);
	}

	void testIDValue() {
		CPPUNIT_ASSERT(t->id < 1000);
	}

	static CppUnit::Test* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite();
		suite->addTest(new CppUnit::TestCaller<TaskTest>("kk1", &TaskTest::testTaskAttributes));
		suite->addTest(new CppUnit::TestCaller<TaskTest>("kk2", &TaskTest::testIDValue));

		return suite;
	}
};

int main(int argc, char* argv[]){
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//// trackerAssets -> recogemos eventos de dificultad, claridad y sesion
	//DifficultyTracker difficultyTracker;
	//ClarityTracker clarityTracker;
	//SessionTracker sessionTracker;

	//// serializadores -> formatos json y csv
	//JsonSerializer jsonSerializer;
	//CSVSerializer csvSerializer;

	//// persistencias -> en archivo y servidor
	//FilePersistence filePersistence({&jsonSerializer, &csvSerializer});
	//ServerPersistence serverPersistence({ &jsonSerializer, &csvSerializer });

	//// inicializacion del sistema de telemetria
	//Tracker::GetInstance().Init({&difficultyTracker, &clarityTracker, &sessionTracker }, { &serverPersistence, &filePersistence });

	//SDLApp g(1280, 720);
	//g.run();
	//g.closeSDL();

	//Tracker::GetInstance().End();

	//filePersistence.release();
	//serverPersistence.release();
	//_CrtDumpMemoryLeaks(); //esta instruccion le vale a Diego para ver la basura. No quiteis el comentario pls T_T

	CppUnit::TextUi::TestRunner run;
	run.addTest(TaskTest::suite());

	if(run.run())
		std::cout << "BIEN" << std::endl;
	else
		std::cout << "MAL" << std::endl;

	return 0;
}