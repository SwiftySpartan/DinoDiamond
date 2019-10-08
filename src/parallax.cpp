#include "parallax.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

Parallax::Parallax(std::size_t w, std::size_t h, float speed) {
	width = static_cast<int>(w);
	height = static_cast<int>(h);
	this->speed = speed;

	// only need 3 tiles (left, center, and right)
	// update the tiles position once one is out of view
	// instead of creating new objects and removing old ones
	// for time and space optimisation.
	tiles.push_back({ static_cast<int>(x) - width, 0, width, height });
	tiles.push_back({ static_cast<int>(x), 0, width, height });
	tiles.push_back({ static_cast<int>(x) + width, 0, width, height });
}

Parallax::~Parallax() {}


// kLeft, kRight, kNone, kLeftQuick, kRightQuick
void Parallax::SetDirection(KeysPressed key_KeysPressed, KeysPressed previous_key_KeysPressed) {
	switch (key_KeysPressed)
	{
	case KeysPressed::keyNone:
		direction = Direction::kNone;
		break;
	case KeysPressed::keyLeft:
		direction = Direction::kLeft;
		break;
	case KeysPressed::keyRight:
		direction = Direction::kRight;
		break;
	case KeysPressed::keySprint:
		if (previous_key_KeysPressed == KeysPressed::keyLeft) {
			direction = Direction::kLeftQuick;
			break;
		}

		if (previous_key_KeysPressed == KeysPressed::keyRight) {
			direction = Direction::kRightQuick;
			break;
		}
		break;
	default:
		break;
	}
}

void Parallax::Update() {
	switch(direction) {
		case Direction::kNone:
			break;
		case Direction::kLeft:
			x += speed;
			break;
		case Direction::kRight:
			x -= speed;
			break;
		case Direction::kLeftQuick:
			// x += (speed * 1.5);
			break;
		case Direction::kRightQuick:
			// x -= (speed * 1.5);
			break;
	}
}

void Parallax::RenderCopy(SDL_Renderer * sdl_renderer, SDL_Texture * texture, bool flip_stitch) {
	// Abstact the tiling process of the background
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

	// once the middle frame is at the end
	// reset to 0 so that it creates a loop effect
	if (x >= width || x <= -(width)) {
		x = 0.0;
	}

	tiles[0].x = static_cast<int>(x) - width;
	tiles[1].x = static_cast<int>(x);
	tiles[2].x = static_cast<int>(x) + width;

	if (flip_stitch) {
		SDL_RenderCopyEx(sdl_renderer, texture, NULL, &tiles[0], 0.0, NULL, flip);
		SDL_RenderCopy(sdl_renderer, texture, NULL, &tiles[1]);
		SDL_RenderCopyEx(sdl_renderer, texture, NULL, &tiles[2], 0.0, NULL, flip);
		return;
	}

	SDL_RenderCopy(sdl_renderer, texture, NULL, &tiles[0]);
	SDL_RenderCopy(sdl_renderer, texture, NULL, &tiles[1]);
	SDL_RenderCopy(sdl_renderer, texture, NULL, &tiles[2]);
}

