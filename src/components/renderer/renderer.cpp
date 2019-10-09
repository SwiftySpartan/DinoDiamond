#include "renderer.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("New Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

	SetStage(sdl_renderer);
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(State &state) {
  // Clear screen
	SDL_RenderClear(sdl_renderer);
  SDL_SetRenderDrawColor(sdl_renderer, 133, 193, 200, 80);

	// Render Stage
	state.GetBackgrounds()[3].RenderCopy(sdl_renderer, sdl_texture_back_clouds_three);
	state.GetBackgrounds()[3].RenderCopy(sdl_renderer, sdl_texture_back_clouds_two);
	state.GetBackgrounds()[3].RenderCopy(sdl_renderer, sdl_texture_back_clouds_one);
	state.GetBackgrounds()[3].RenderCopy(sdl_renderer, sdl_texture_back_clouds_huge);
	state.GetBackgrounds()[2].RenderCopy(sdl_renderer, sdl_texture_back_hill_two, true);
	state.GetBackgrounds()[2].RenderCopy(sdl_renderer, sdl_texture_back_hill_one, true);
	state.GetBackgrounds()[1].RenderCopy(sdl_renderer, sdl_texture_dist_trees);

	// foreground
	state.GetBackgrounds()[0].RenderCopy(sdl_renderer, sdl_texture_trees);
	state.GetBackgrounds()[0].RenderCopy(sdl_renderer, sdl_texture_ground);

	for (size_t i = 0; i < state.GetDiamonds().size(); i++) {
		state.GetDiamonds()[i].Render(sdl_renderer);
	}

	for (size_t i = 0; i < state.GetFires().size(); i++) {
		state.GetFires()[i].Render(sdl_renderer);
	}

	state.GetPlayer().Render(sdl_renderer);

	SDL_Rect r = { 0, 0, 1300, 900 };
	SDL_RenderCopy(sdl_renderer, sdl_texture_game_over, &r, NULL);

  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int level, int previous_score, int fps) {
  std::string title{"Dino Score: " + std::to_string(score) + " | Level: " +  std::to_string(level) + " | Previous score: " + std::to_string(previous_score) + " | FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::SetStage(SDL_Renderer * renderer) {
	sdl_texture_back_hill_two = SDL_CreateTextureFromSurface(renderer, IMG_Load("../assets/06_hill2.png"));
  sdl_texture_back_hill_one = SDL_CreateTextureFromSurface(renderer, IMG_Load("../assets/05_hill1.png"));

  sdl_texture_trees = SDL_CreateTextureFromSurface(renderer, IMG_Load("../assets/02_trees_and_bushes.png"));

  sdl_texture_ground = SDL_CreateTextureFromSurface(renderer, IMG_Load("../assets/01_ground.png"));

	sdl_texture_dist_trees = SDL_CreateTextureFromSurface(renderer, IMG_Load("../assets/03_distant_trees.png"));

	sdl_texture_back_clouds_huge = SDL_CreateTextureFromSurface(renderer, IMG_Load("../assets/07_huge_clouds.png"));

	sdl_texture_back_clouds_one = SDL_CreateTextureFromSurface(renderer, IMG_Load("../assets/08_clouds.png"));
	sdl_texture_back_clouds_two = SDL_CreateTextureFromSurface(renderer, IMG_Load("../assets/09_distant_clouds1.png"));
	sdl_texture_back_clouds_three = SDL_CreateTextureFromSurface(renderer, IMG_Load("../assets/10_distant_clouds.png"));

	sdl_texture_game_over = SDL_CreateTextureFromSurface(renderer, IMG_Load("../assets/game_over.png"));
}
