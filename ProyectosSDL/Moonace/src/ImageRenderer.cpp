#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(Texture * image): image_(image)
{
	if (image != nullptr) {
		frameRect.x = 0;
		frameRect.y = 0;
		frameRect.w = image->getWidth();
		frameRect.h = image->getHeight();
	}
	else {
		frameRect = { 0,0,0,0 };
	}
}

ImageRenderer::ImageRenderer(Texture * image, int numFrCols, int numFrFils, int frAPintar):
	image_(image)
{
	frameRect.w = image->getWidth() / numFrCols;
	frameRect.h = image->getHeight() / numFrFils;

	// teniendo el frame 0 como esquina sup izquierda
	frameRect.x = (frAPintar%numFrFils)*frameRect.w;
	frameRect.y = (frAPintar/numFrFils)*frameRect.h;
}

ImageRenderer::~ImageRenderer() {
}

void ImageRenderer::render(GameObject* o, Uint32 time) {
	SDL_Rect rect{ o->getPosition().getX(), o->getPosition().getY(),
					o->getWidth(), o->getHeight() };
		
	image_->render(o->getGame()->getRenderer(), rect, o->getAngle(),&frameRect);
}
