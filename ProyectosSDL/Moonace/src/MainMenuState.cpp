#include "MainMenuState.h"
#include "TransitionScreen.h"
#include "ControlesState.h"
#include "CreditosState.h"
#include "ActEndingScreen.h"


MainMenuState::MainMenuState()
{
}
MainMenuState::MainMenuState(SDLApp * game):GameState(game)
{
	playMusic(Resources::MainThemePro);//al principio comienza el mainTheme
	nGame_ = [game, this]()mutable { // funcion newGame(); mutable hace que puedas modificar cosas dentro

		stopMusic(Resources::MainThemePro);//si pulsamos algun boton se para la musica

		PlayState* playState_ = new PlayState(game); //acceder al estado PlayState

		game->getStateMachine()->pushState(playState_);//pop antes??

		playState_->getScenes()[0]->enterScene();

		game->getStateMachine()->pushState(new TransitionScreen(game, game->getStateMachine()->currentState(), 1200));
	};

	lGame_ = [game, this]()mutable { //funcion LoadGame();
		stopMusic(Resources::MainThemePro);
		PlayState* playState_ = new PlayState(game, true); //acceder al estado PlayState

		game->getStateMachine()->pushState(playState_);//pop antes??

		playState_->getScenes()[playState_->getNumCurrentScene()]->enterScene(); //entra en la actual

		game->getStateMachine()->pushState(new TransitionScreen(game, game->getStateMachine()->currentState(), 1200));

	};

	eGame_ = [game, this]()mutable {
		stopMusic(Resources::MainThemePro);
		game->exitGame();//Nunca deberia de haber un estado por encima de este
	};

	controlesFunc_ = [game]()mutable {
		ControlesState* contState = new ControlesState(game);

		game->getStateMachine()->pushState(contState);

		game->getStateMachine()->pushState(new TransitionScreen(game, game->getStateMachine()->currentState(), 500));
	};

	creditosFun_ = [game]()mutable {
		CreditosState* credits = new CreditosState(game);

		game->getStateMachine()->pushState(credits);

		game->getStateMachine()->pushState(new TransitionScreen(game, game->getStateMachine()->currentState(), 500));
	};

	cout << "mainMenu" << endl;
	fondotext = new ImageRenderer(app->getResources()->getImageTexture(Resources::FondoMenu));
	logotext = app->getResources()->getImageTexture(Resources::LogoAnim);
	logotext2 = new ImageRenderer(app->getResources()->getImageTexture(Resources::LogoBitLegion));
	logotextSDL = new ImageRenderer(app->getResources()->getImageTexture(Resources::LogoSDL));

	Boton* b;
	b = new Boton(app, "NewGame", nGame_, Resources::BotonSonido);
	b->setWidth(150); b->setHeight(100);
	b->setPosition(Vector2D(app->getWindowWidth() / 2 - b->getWidth() / 2, ((app->getWindowHeight() - app->getWindowHeight() / 3) * 1 / 5)+ 250));
	b->addAnim("Feedback", { 16 }, true, -1, 100);
	b->addAnim("Stop", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,0 }, true, -1, 100);
	btext = new AnimationRenderer(app->getResources()->getImageTexture(Resources::BotonComenzar), b->getAnimations(), 4, 5, 265, 150);
	btext->playAnim("Stop");
	b->setAnimated(true);
	b->addRenderComponent(btext);
	b->addInputComponent(&ov);
	botones.push_back(b); stage.push_back(b);

	b = (new Boton(app, "Load Game", lGame_, Resources::BotonSonido));
	b->setWidth(150); b->setHeight(100);
	b->setPosition(Vector2D(app->getWindowWidth() / 2 - b->getWidth() / 2, ((app->getWindowHeight() - app->getWindowHeight() / 3) * 2 / 5)+250));
	b->addAnim("Feedback", { 16 }, true, -1, 100);
	b->addAnim("Stop", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, true, -1, 100);
	bLoadtext = new AnimationRenderer(app->getResources()->getImageTexture(Resources::BotonLoad), b->getAnimations(), 4, 5, 265, 150);
	bLoadtext->playAnim("Stop");
	b->setAnimated(true);
	b->addRenderComponent(bLoadtext);
	b->addInputComponent(&ov);
	botones.push_back(b); stage.push_back(b);

	b = (new Boton(app, "Controles", controlesFunc_, Resources::BotonSonido));
	b->setWidth(150); b->setHeight(100);
	b->setPosition(Vector2D(app->getWindowWidth() / 2 - b->getWidth() / 2, ((app->getWindowHeight() - app->getWindowHeight() / 3) * 3 / 5) + 250));
	b->addAnim("Feedback", { 16 }, true, -1, 75);
	b->addAnim("Stop", { 0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, true, -1, 100);
	b->addInputComponent(&ov);
	bControles = new AnimationRenderer(app->getResources()->getImageTexture(Resources::ControlesButton), b->getAnimations(), 4, 5, 265, 150);
	bControles->playAnim("Stop");
	b->addRenderComponent(bControles);
	b->setAnimated(true);
	botones.push_back(b); stage.push_back(b);

	b = (new Boton(app, "Exit", eGame_, Resources::BotonSonido));
	b->setWidth(150); b->setHeight(100);
	b->setPosition(Vector2D(app->getWindowWidth() / 2 - b->getWidth() / 2, ((app->getWindowHeight() - app->getWindowHeight() / 3) * 4 / 5)+250));
	b->addAnim("Feedback", { 16 }, true, -1, 75);
	b->addAnim("Stop", { 0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, true, -1, 100);
	bExittext = new AnimationRenderer(app->getResources()->getImageTexture(Resources::BotonExit), b->getAnimations(), 4, 5, 265, 150);
	bExittext->playAnim("Stop");
	b->addInputComponent(&ov);
	b->addRenderComponent(bExittext);
	b->setAnimated(true);
	botones.push_back(b);stage.push_back(b);

	b = (new Boton(app, "Creditos", creditosFun_, Resources::BotonSonido));
	b->setWidth(150); b->setHeight(100);
	b->setPosition(Vector2D(app->getWindowWidth() - b->getWidth(), app->getWindowHeight() - b->getHeight()));
	b->addAnim("Feedback", { 16 }, true, -1, 75);
	b->addAnim("Stop", { 0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, true, -1, 100);
	bExittext = new AnimationRenderer(app->getResources()->getImageTexture(Resources::CreditosBoton), b->getAnimations(), 4, 5, 265, 150);
	bExittext->playAnim("Stop");
	b->addInputComponent(&ov);
	b->addRenderComponent(bExittext);
	b->setAnimated(true);
	botones.push_back(b); stage.push_back(b);

	logo = new Entity(app);
	logo->setPosition({ (double)logo->getGame()->getWindowWidth()/2 - 300, 150 });
	logo->setWidth(600);
	logo->setHeight(190);
	logo->setAnimated(true);
	logo->delEveryRenderComponent();
	logo->addAnim("logoAnim", { 0,0,0,0,0,0,0,0,0,0,0, 1,0,1,0, 3, 3, 3, 5, 0, 0, 0, 4, 4 }, true, -1, 80);
	logo->addRenderComponent(new AnimationRenderer(logotext, logo->getAnimations(), 1, 6, 600, 203));
	stage.push_back(logo);

	logoSDL = new Entity(app);
	logoSDL->setWidth(50);
	logoSDL->setHeight(40);
	logoSDL->setPosition(Vector2D(5, app->getWindowHeight() - logoSDL->getHeight()-5));
	logoSDL->addRenderComponent(logotextSDL);
	stage.push_back(logoSDL);

	logo2 = new Entity(app);
	logo2->setWidth(40);
	logo2->setHeight(40);
	logo2->setPosition(Vector2D(logoSDL->getWidth()+20, app->getWindowHeight() - logo2->getHeight()-5));
	logo2->addRenderComponent(logotext2);
	stage.push_back(logo2);
	
	fondo = new Entity(app);
	fondo->setPosition({ 0, 0 });
	fondo->setWidth(fondo->getGame()->getWindowWidth());
	fondo->setHeight(fondo->getGame()->getWindowHeight());
	fondo->addRenderComponent(fondotext);
	stage.push_back(fondo);
}

MainMenuState::~MainMenuState()
{
	//stage.clear();
	for (int i = 0; i < botones.size(); i++) { botones.at(i)->delRenderComponent(btext); 
	botones.at(i)->delRenderComponent(bLoadtext); botones.at(i)->delRenderComponent(bExittext); botones.at(i)->delInputComponent(&ov); }
	vector<Boton*>::iterator it;
	for (it = botones.begin(); it != botones.end();it++) {
		this->deleteElement(*it);
	}
	delete(btext);
	delete(bLoadtext);
	delete(bExittext);

	for (vector<Entity*>::iterator it = ControlesState::entities.begin(); it != ControlesState::entities.end(); it++) { //borramos la variable static de controles
		delete *it;
	}
}