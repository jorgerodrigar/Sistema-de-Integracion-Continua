#ifndef IMAGERENDERER_H_
#define IMAGERENDERER_H_

#include "checkML.h"
#include "RenderComponent.h"
#include "Texture.h"
#include "SDLApp.h"

/*
 *
 */
class ImageRenderer: public RenderComponent {
public:
	ImageRenderer() {};
	ImageRenderer(Texture* image);
	ImageRenderer(Texture* image, SDL_Rect rect) : image_(image), frameRect(rect){}
	ImageRenderer(Texture* image, int numFrCols, int numFrFils, int frAPintar);
	virtual ~ImageRenderer();
	virtual void render(GameObject* o, Uint32 time);
	virtual Texture* getTexture() const { return image_; };
	virtual void setTexture(Texture* newText) { this->image_ = newText; };
private:
	Texture* image_;
	SDL_Rect frameRect;
};

#endif /* IMAGERENDERER_H_ */
