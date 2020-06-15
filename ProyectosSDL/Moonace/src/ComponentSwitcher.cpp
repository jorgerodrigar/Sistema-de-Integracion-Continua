#include "ComponentSwitcher.h"

ComponentSwitcher::ComponentSwitcher(SDLApp* game, Entity* o) :
		GameObject(game), o_(o), modes_(), currMode_(-1) {
}

ComponentSwitcher::~ComponentSwitcher() {
	o_ = nullptr;
}

void ComponentSwitcher::handleInput(Uint32 time, const SDL_Event& event) {
	if ((!mouse && event.type == SDL_KEYDOWN && currMode_ != 0)) {
		switchToNextMode();
		cout << currMode_;
		keyComp = true;//keyboard activado
	}
	else if(!keyBoard && event.type == SDL_MOUSEBUTTONDOWN && currMode_ != 1 && event.button.button == SDL_BUTTON_RIGHT){
		switchToNextMode();
		keyComp = false;//keyboard desactivado
	}
}



void ComponentSwitcher::addMode(ModeInfo mode) {
	modes_.push_back(mode);
}

void ComponentSwitcher::switchToNextMode() {
	setMode( (currMode_ + 1) % modes_.size() );
}

void ComponentSwitcher::setMode(int i) {
	ModeInfo m;

	if ( currMode_ != -1 ) {
		m = modes_[currMode_];
		if ( m.ic != nullptr ) {
			o_->delInputComponent(m.ic);
		}
		if ( m.pc != nullptr ) {
			o_->delPhysicsComponent(m.pc);
		}
		if ( m.rc != nullptr ) {
			o_->delRenderComponent(m.rc);
		}
	}

	currMode_ = i;
	m =  modes_[currMode_];
	if ( m.ic != nullptr ) {
		o_->addInputComponent(m.ic);
	}
	if ( m.pc != nullptr ) {
		o_->addPhysicsComponent(m.pc);
	}
	if ( m.rc != nullptr ) {
		o_->addRenderComponent(m.rc);
	}

}

//para independizar los dos tipos de movimiento
void ComponentSwitcher::receive(Mensaje* msg) {
	if (msg->id_ == Moving)keyBoard = true;
	else if (msg->id_ == StopRight || msg->id_ == StopLeft)keyBoard = false;
	else if (msg->id_ == MouseMoving)mouse = true;
	else if (msg->id_ == MouseStop)mouse = false;
	else if (msg->id_ == CambioEscena)cambioEscena = true;

}
