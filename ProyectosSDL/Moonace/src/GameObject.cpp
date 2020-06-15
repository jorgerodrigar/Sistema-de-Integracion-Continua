#include "GameObject.h"


GameObject::GameObject(): objectType(Default)
{
}


GameObject::~GameObject()
{
	app = nullptr;
}
