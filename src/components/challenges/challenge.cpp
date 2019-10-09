#include "challenge.h"

void Challenge::SetDirection(KeysPressed key_KeysPressed, KeysPressed previous_key_KeysPressed) {
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

void Challenge::Update() {
  switch (direction) {
    case Direction::kNone:
      break;

    case Direction::kLeft:
      SetSpeed(speed);
      break;

    case Direction::kRight:
      SetSpeed(speed);
      break;

		case Direction::kLeftQuick:
			SetSpeed(speed * 1.5);
      break;

		case Direction::kRightQuick:
      SetSpeed(speed * 1.5);
      break;
  }
}

SDL_Texture * Challenge::GetTexture(SDL_Renderer * renderer) {
	return SDL_CreateTextureFromSurface(renderer, surface);
}

bool Challenge::Collides(int px, int py) {
  if (px == static_cast<int>(x) && py == static_cast<int>(y)) {
    return true;
  }
  return false;
}

void Challenge::SetSpeed(float s) {
		switch (direction) {
    case Direction::kNone:
      break;

    case Direction::kLeft:
			x += s;
      break;

    case Direction::kRight:
			x -= s;
      break;

		case Direction::kLeftQuick:
			x += s;
      break;

		case Direction::kRightQuick:
			x -= s;
      break;
  }
}

void Challenge::Render(SDL_Renderer * sdl_renderer) {
	texture = GetTexture(sdl_renderer);

	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 100;
	int sprite = seconds % 8;

	SDL_Rect srcrect = { 0, 0, 200, 200 };

	if (challengeType == ChallengeType::DETRIMENTAL) {
		srcrect = { sprite * 64, 53, 60, 60 };
	}

	SDL_Rect dstrect = { static_cast<int>(x), static_cast<int>(y), width, height };

	SDL_RenderCopy(sdl_renderer, texture, &srcrect, &dstrect);

	SDL_DestroyTexture(texture);
}

size_t Challenge::RandomGenerator(int min, int max) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}
