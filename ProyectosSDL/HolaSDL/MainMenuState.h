#pragma once
#include "GameState.h"
#include "Boton.h"
#include "PlayState.h"
#include "ImageRenderer.h"
#include "MouseEventAnimComponent.h"

class MainMenuState :
	public GameState
{
public:
	MainMenuState();
	MainMenuState(SDLApp* game);
	~MainMenuState();
	vector<Boton*> botones;
private:
	AnimationRenderer* btext;
	AnimationRenderer* bLoadtext;
	AnimationRenderer* bExittext;
	AnimationRenderer* bControles;
	RenderComponent* fondotext;
	MouseEventAnimComponent ov{ SDL_MOUSEMOTION, "Feedback", "Stop" };
	Texture* logotext;
	RenderComponent* logotext2;
	RenderComponent* logotextSDL;
	Entity* fondo;
	Entity* logo;
	Entity* logo2;
	Entity* logoSDL;
	function<void()> nGame_;
	function<void()> lGame_;
	function<void()> eGame_;
	function<void()> controlesFunc_;
	function<void()> creditosFun_;
};

