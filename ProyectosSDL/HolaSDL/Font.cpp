#include "Font.h"

Font::Font() :
		font_(nullptr) {
}

Font::Font(std::string fileName, int size) {
		load(fileName, size);
}

Font::~Font() {
	close();
}

bool Font::load(std::string fileName, int size) {
	font_ = TTF_OpenFont(fileName.c_str(), size);
	return font_ != nullptr;
}

void Font::close() {
	if (font_) {
		TTF_CloseFont(font_);
		font_ = nullptr;
	}
}

SDL_Surface* Font::renderText(std::string text, SDL_Color color) const {
	if ( font_ ) {
		return TTF_RenderUTF8_Solid(font_, text.c_str(), color);
	} else {
		return nullptr;
	}
}
