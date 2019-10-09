#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <cmath>
#include <memory>
#include <map>
#include <vector>
#include <iostream>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../utils/keys.h"

enum class ChallengeType { BENEFICIAL, DETRIMENTAL };

class Challenge {
 public:
  Challenge(int x, int y, float speed)
      : x(x),
        y(y),
				speed(speed) {};

	~Challenge() {
		if (texture != nullptr) {
			SDL_DestroyTexture(texture);
		}
	};

	void SetDirection(KeysPressed key_KeysPressed, KeysPressed previous_key_KeysPressed);

  void Update();

	void Render(SDL_Renderer * sdl_renderer);

  bool Collides(int x, int y);

	template <typename T> void some_method(T t);

	enum class Direction { kNone, kLeft, kRight, kLeftQuick, kRightQuick };
  Direction direction = Direction::kNone;

	// Getter & Setters
	SDL_Texture * GetTexture(SDL_Renderer * renderer);

	SDL_Texture & GetSurface() {
		return *texture;
	}

	int GetWidth() {
		return width;
	};

	int GetHeight() {
		return height;
	};

	float GetX() {
		return this->x;
	}

	float GetY() {
		return this->y;
	}


	ChallengeType GetChallengeType() {
		return this->challengeType;
	}

	void SetSpeed(float speed);

	void SetX(float x) {
		this->x = x;
	}

	void SetY(float y) {
		this->y = y;
	}

	void SetLevel(int level) {
		this->level = 0;;
	}

	void SetIsAlive(bool isAlive) {
		this->alive = isAlive;
	}

	void SetChallengeType(ChallengeType type) {
		this->challengeType = type;
	}

	void SetSurface(SDL_Surface * s) {
		this->surface = s;
	}

 private:
  void Update(SDL_Point &current_cell, SDL_Point &prev_cell);

	size_t RandomGenerator(int min, int max);

	int width{50};
	int height{50};

	SDL_Texture * texture;
	SDL_Surface * surface;

	ChallengeType challengeType;

	std::vector<Challenge *> challenges;

  float speed{0.0f};
	bool alive{true};
	int level{0};

  float x;
  float y;

	int detrimental_size{0};

  std::vector<SDL_Point> body;
};

#endif
