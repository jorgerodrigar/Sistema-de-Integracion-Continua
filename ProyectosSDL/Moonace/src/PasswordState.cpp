#include "PasswordState.h"
#include "AnimationRenderer.h"


PasswordState::PasswordState()
{
}


PasswordState::~PasswordState()
{
	if (f != nullptr) { delete f; f = nullptr; }

	if (fondo != nullptr) { fondo->delRenderComponent(&img); delete fondo; }

	if (timerFail != nullptr) { delete timerFail; }

	if (botonSalir != nullptr) { botonSalir->delInputComponent(&press); delete botonSalir; }

	stage.clear();
}

PasswordState::PasswordState(SDLApp * app, int PosFontX, int PosFontY, string password, int id, int txt, bool swap): Puzzle(app, id, swap), password_(password), posFontX_(PosFontX), posFontY_(PosFontY)
{
	numPuzzle--;
	press = MouseEventAnimComponent(SDL_MOUSEBUTTONDOWN, "Pressed", "Stop", SDL_BUTTON_LEFT);

	f = new Font("..//images/Dialogos/Moonace-Regular.ttf", 50);
	resetPassword();

	exitFun_ = [app]() mutable { app->getStateMachine()->popState(false); };
	botonSalir = new Boton(app, "exitButton", exitFun_, Resources::BotonSonido);
	botonSalir->setWidth(56);
	botonSalir->setHeight(53);
	botonSalir->setPosition(Vector2D(40, 40));
	botonSalir->addAnim("Stop", { 0 }, true, -1, 100);
	botonSalir->addAnim("Pressed", { 1 }, true, -1, 100);
	botonSalir->addRenderComponent(new AnimationRenderer(app->getResources()->getImageTexture(Resources::SalirPassWord), botonSalir->getAnimations(), 1, 2, 56, 53));
	botonSalir->addInputComponent(&press);
	botonSalir->setAnimated(true);

	this->stage.push_back(botonSalir);

	if (txt != -1) {
		img = ImageRenderer(app->getResources()->getImageTexture(Resources::ImageId(txt)));
		fondo = new Entity(app);
		fondo->setWidth(app->getWindowWidth());
		fondo->setHeight(app->getWindowHeight());
		fondo->addRenderComponent(&img);
		this->stage.push_back(fondo);
	}

	function<void()> fun = [this]() mutable { reset(); };

	timerFail = new GOTimer(2000, fun);
	this->stage.push_back(timerFail);
}

void PasswordState::handleEvent(SDL_Event & e)
{
	if (!checking) {
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym >= SDLK_a && e.key.keysym.sym <= SDLK_z) {

				userPass_.at(i) = ((char)e.key.keysym.sym);
				i++;

				if (i >= password_.size()) {
					checkPassword();
				}
			}
		}
	}

	GameState::handleEvent(e);
}

void PasswordState::render()
{
	GameState::render();

	Texture text(app->getRenderer(), userPass_, *f, colorFuente); //fuente dinamica
	text.render(app->getRenderer(), posFontX_, posFontY_); //se llama al render de la fuente Dinamica
}

bool PasswordState::checkPassword()
{
	if (userPass_ != password_ && !checking) {
		playSoundEffect(Resources::WrongPuzle);
		timerFail->startTimer();
		checking = true;
		i = 0;
		return false;
	}
	else if(!checking){
		Puzzle::win();
		checking = true;
		return true;
	}

}

void PasswordState::resetPassword()
{
	for (unsigned int j = 0; j < password_.size(); j++) {
		userPass_.push_back('_');
	}
}

void PasswordState::reset()
{
	userPass_.clear();
	resetPassword();
	checking = false;
}
