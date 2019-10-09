#include "player.h"

void Player::SetAction(KeysPressed key_KeysPressed, KeysPressed previous_key_KeysPressed) {
	// store old action for resetting animations in other life cycles
	previous_action = action;
	switch (key_KeysPressed)
	{
	case KeysPressed::keyNone:
		action = Action::kNone;
		break;
	case KeysPressed::keyUp:
		if (previous_key_KeysPressed == KeysPressed::keyLeft) {
			action = Action::kJumpLeft;
			break;
		}

		if (previous_key_KeysPressed == KeysPressed::keyRight) {
			action = Action::kJumpRight;
			break;
		}
		break;
	case KeysPressed::keyLeft:
		action = Action::kLeft;
		break;
	case KeysPressed::keyRight:
		action = Action::kRight;
		break;
	case KeysPressed::keySprint:
		if (previous_key_KeysPressed == KeysPressed::keyLeft) {
			action = Action::kSprintLeft;
			break;
		}

		if (previous_key_KeysPressed == KeysPressed::keyRight) {
			action = Action::kSprintRight;
			break;
		}
		break;
	case KeysPressed::keyJump:
		if (previous_key_KeysPressed == KeysPressed::keyLeft) {
			action = Action::kJumpLeft;
			break;
		}

		if (previous_key_KeysPressed == KeysPressed::keyRight) {
			action = Action::kJumpRight;
			break;
		}
		break;
	default:
		break;
	}
}

void Player::Update() {
	if (!alive) {
		return;
	}

  switch (action) {
    case Action::kUp:
			SetIdle();
      break;

    case Action::kNone:
			SetIdle();
      break;

    case Action::kLeft:
			SetWalking();
      x += speed;
      break;

    case Action::kRight:
			SetWalking();
      x -= speed;
      break;

		case Action::kSprintLeft:
      x += speed;
			SetRunning();
      break;

		case Action::kSprintRight:
      x -= speed;
			SetRunning();
      break;

		case Action::kJumpLeft:
      x += speed;
			SetJumping();
      break;

		case Action::kJumpRight:
      x -= speed;
			SetJumping();
      break;
  }
}

SDL_Texture * Player::SetPlayer(SDL_Renderer * renderer) {
	return SDL_CreateTextureFromSurface(renderer, surface);
}

bool Player::PlayerCell(int px, int py) {
	if (px <= static_cast<int>(x) + 50 && px >= static_cast<int>(x) - 50 && py <= static_cast<int>(y) + 50) {
		return true;
  }

  return false;
}


void Player::Render(SDL_Renderer * sdl_renderer) {
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

	SDL_Texture * texture = SetPlayer(sdl_renderer);
	SDL_Rect dstrect = { static_cast<int>(x), static_cast<int>(y), 90, 90 };

	if (action == Player::Action::kLeft || action ==  Player::Action::kSprintLeft || action ==  Player::Action::kJumpLeft) {
		SDL_RenderCopyEx(sdl_renderer, texture, &srcrect, &dstrect, 0.0, NULL, flip);
		SDL_DestroyTexture(texture);
		return;
	}

	SDL_RenderCopy(sdl_renderer, texture, &srcrect, &dstrect);
	SDL_DestroyTexture(texture);
}

void Player::SetIdle() {
	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 100;
	int sprite = seconds % 9;

	srcrect = { sprite * 257, 0, 180, 180 };
}

void Player::SetWalking() {
	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 100;
	int sprite = seconds % 10;

	srcrect = { sprite * 257, 422, 180, 180 };
}

void Player::SetRunning() {
	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 100;
	int sprite = seconds % 8;

	srcrect = { sprite * 257, 189, 180, 180 };
}

void Player::SetJumping() {
	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 240;
	int sprite = seconds % 12;

	srcrect = { sprite * 257, 632, 180, 180 };

	Jump();
}

void Player::SetDied() {
	Uint32 ticks = SDL_GetTicks();
	Uint32 seconds = ticks / 240;
	int sprite = seconds % 9;

	srcrect = { 800, 885, 250, 250 };
}

void Player::Jump() {
	if (!is_jumping && jump_count == 0) {
		is_jumping = true;
		jump_count = 100;
	} else if (is_jumping && jump_count == 0) {
		SetWalking();
		return;
	}

	if (jump_count <= 50) {
		y += 5;
		jump_count--;
	} else if (50 < jump_count && jump_count <= 100){
		y -= 5;
		jump_count--;
	}
}

void Player::Die() {
	SetDied();
	alive = false;
}
