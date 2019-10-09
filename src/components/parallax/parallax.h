#ifndef Parallax_H
#define Parallax_H

#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../utils/keys.h"

class Parallax {
 public:
 	Parallax(std::size_t w, std::size_t h, float speed);
  ~Parallax();

	void RenderCopy(SDL_Renderer * sdl_renderer, SDL_Texture * texture, bool flip_stitch = false);

	void SetDirection(KeysPressed key_KeysPressed, KeysPressed previous_key_KeysPressed);

	void Update();

	enum class Direction { kLeft, kRight, kNone, kLeftQuick, kRightQuick};
	Direction direction = Direction::kNone;

 private:
	float speed{1.0f};
	float x{0.0f};
	float y{0.0f};

	std::vector<SDL_Rect> tiles;

	int width;
	int height;


	void shiftLeft();
	void shiftRight();
};

#endif
