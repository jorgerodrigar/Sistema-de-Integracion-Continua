#pragma once
#include "ClickeableGO.h"
#include "Conversacion.h"
class GOConversational :
	public ClickeableGO, public Observer
{
public:
	GOConversational();
	~GOConversational();
	GOConversational(SDLApp* game, int x, int y, int w, int h, Texture* texture, string convoName, bool repeat = true, bool done = false) : ClickeableGO(game, x, y, w, h, texture), convoName_(convoName), repeat_(repeat), done_(done) {
		convo = new Conversacion(app);
		convo->loadConversation(convoName);
	};
	virtual void saveToJson(json& j) {
		json aux; Entity::saveToJson(aux);
		aux["convoName"] = convoName_; aux["repeat"] = repeat_; aux["done"] = done_; j["GOConversational"].push_back(aux);
	};

	virtual void receive(Mensaje* msg);
protected:
	virtual void act();
	virtual void secondAct() {};
	bool inconversation = false;
	string convoName_;
	Conversacion* convo = nullptr;
	bool repeat_;
	bool firstTime_ = true;
	bool done_ = false;
};

