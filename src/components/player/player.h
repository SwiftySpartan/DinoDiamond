#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <iostream>

#include "../../utils/keys.h"

class Player {
 public:
  Player(int screen_width = 1300, int screen_height = 900, float x = 650, float y = 680)
      : screen_width(screen_width),
        screen_height(screen_height),
        x(x),
        y(y) {
		surface = IMG_Load("../assets/dino-gen.png");
	}

	~Player() {};

  void Update();

	void SetAction(KeysPressed key_KeysPressed, KeysPressed previous_key_KeysPressed);

	void Render(SDL_Renderer * sdl_renderer);

  bool PlayerCell(int x, int y);

	SDL_Texture * SetPlayer(SDL_Renderer * renderer);

	void Jump();

	void Die();

	enum class Action { kUp, kNone, kLeft, kRight, kSprintLeft, kSprintRight, kJumpLeft, kJumpRight };
  Action action = Action::kNone;

  float speed{0.0f};
  bool alive{true};
  float x;
  float y;

	int anim_speed{60};
	int anim_frames{9};
	int anim_row{0};
	bool animate{false};

	int consume_score{0};

	int count_to_reset_animation{0};
	bool reset_animation{false};
	Action previous_action{Action::kNone};

  std::vector<SDL_Point> body;

 private:
  void Update(SDL_Point &current_cell, SDL_Point &prev_cell);

	void SetIdle();
	void SetWalking();
	void SetRunning();
	void SetJumping();
	void SetDied();

	SDL_Rect srcrect;

	bool is_falling;
	bool is_jumping;

	bool prevent_user_control{false};

	int jump_height{10};

  int screen_width;
  int screen_height;

	SDL_Surface * surface;
};

#endif
