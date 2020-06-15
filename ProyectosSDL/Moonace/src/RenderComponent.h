#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

#include "checkML.h"
#include "GameObject.h"
#include "Texture.h"

/*
 *
 */
class RenderComponent {
public:
	RenderComponent();
	virtual ~RenderComponent();
	virtual void render(GameObject* o, Uint32 time) = 0;
	virtual Texture* getTexture() const = 0;
	virtual void setTexture(Texture* newText) = 0;
};

#endif /* RENDERCOMPONENT_H_ */
