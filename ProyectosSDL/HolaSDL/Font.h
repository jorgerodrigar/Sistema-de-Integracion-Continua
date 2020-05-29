#ifndef FONT_H_
#define FONT_H_

#include "checkML.h"
#include <SDL_ttf.h>
#include <string>

class Font {
public:
	Font();
	Font(std::string fileName, int size);
	virtual ~Font();

	bool load(std::string fileName, int size);
	void close();
	SDL_Surface* renderText(std::string text, SDL_Color color) const;
private:
	TTF_Font *font_;
};

#endif /* FONT_H_ */
