#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


#include "../player/player.h"
#include "../challenges/challenge.h"
#include "../parallax/parallax.h"
#include "../state/state.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(State &state);
	void UpdateWindowTitle(int score, int level, int fps, int previous_score);
	void SetStage(SDL_Renderer * renderer);

 private:
  SDL_Window * sdl_window;
  SDL_Renderer * sdl_renderer;

	SDL_Texture * sdl_texture_trees;
	SDL_Texture * sdl_texture_dist_trees;
	SDL_Texture * sdl_texture_back_hill_one;
	SDL_Texture * sdl_texture_back_hill_two;
	SDL_Texture * sdl_texture_ground;

	SDL_Texture * sdl_texture_back_clouds_huge;
	SDL_Texture * sdl_texture_back_clouds_one;
	SDL_Texture * sdl_texture_back_clouds_two;
	SDL_Texture * sdl_texture_back_clouds_three;

	SDL_Texture * sdl_texture_game_over;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
