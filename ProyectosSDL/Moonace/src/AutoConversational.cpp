#include "AutoConversational.h"



AutoConversational::AutoConversational()
{
}


AutoConversational::~AutoConversational()
{
}

void AutoConversational::handleInput(Uint32 time, const SDL_Event& event) {
	act();
}