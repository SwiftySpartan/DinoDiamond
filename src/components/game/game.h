#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "../controller/controller.h"
#include "../challenges/diamonds/diamond.h"
#include "../challenges/fires/fire.h"
#include "../player/player.h"
#include "../renderer/renderer.h"
#include "../state/state.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height,
			 std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration, int previous_score);
  int GetScore() const;
  int GetSize() const;

	void Detect(Mix_Chunk &diamond_sf, State &state) const;

 private:
	Player player;

  int score{0};

	std::vector<Parallax> backgrounds;
	std::vector<Diamond> diamonds;
	std::vector<Fire> fires;

  void Update(Mix_Chunk &diamond_sf, State &state);
};

#endif
