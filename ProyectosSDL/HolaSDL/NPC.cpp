#include "NPC.h"


NPC::NPC()
{
}

NPC::NPC(SDLApp * game, int x, int y, int w, int h, Texture * texture, string convoName, bool repeat, bool done) : GOConversational(game, x, y, w, h, texture, convoName, repeat, done), convoName_(convoName)
{
	obj = new ColisionableObject(game, x, y, w, h, nullptr);
}


NPC::~NPC()
{
}
