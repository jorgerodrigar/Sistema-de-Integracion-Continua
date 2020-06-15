#ifndef SDL_INCLUDES_H_
#define SDL_INCLUDES_H_

/*
whenever we need to include an SDL library we use this file. This way we can make the
program portable as paths might be different depending on the environment we use.
*/

// The following 'if' includes the SDL paths depending on the operating system,
// you might need to fix depending on how you've installed the SDL libraries


#if defined(_WIN32) || defined(_WIN64) // Windows
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_image/SDL_image.h>
#else
#error "SDL includes where not resolved correctly"
#endif

// the RECT macro is used to automatically cast the argument to integer (since in GameObject the
// dimension, position, etc., are double
#define RECT(x,y,w,h) {static_cast<int>(x),static_cast<int>(y),static_cast<int>(w),static_cast<int>(h)}

// the COLOREXP macro is used to expand an SDL_Color variable into its components, so instead of writing
//
//    SDL_SetRenderDrawColor(game_->getRenderer(), color.r, color.g, color.b, color.a);
//
// we can simply write
//
// SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color));
#define COLOREXP(color) color.r, color.g, color.b, color.a

// Write colors in an easy way in hex, e.g., 0xaaff12ff. Instead of writing
//
//   { 0x44, 0x11, 0x22, 0x33 }
//
// simply write {COLOR(0x44112233)}
//
#define COLOR(num) (num >> 24) & 0xff, (num >> 16) & 0xff, (num >> 8) & 0xff, num & 0xff

#endif /* SDL_INCLUDES_H_ */