#include "game.h"

Game::Game(std::size_t screen_width, std::size_t screen_height,
			 std::size_t grid_width, std::size_t grid_height)
    : player(static_cast<int>(screen_width), static_cast<int>(screen_height), screen_height * 0.5, screen_height * 0.69)
{
	// add all background parallaxes
	backgrounds.push_back(Parallax(screen_width, screen_height, 2.5));
	backgrounds.push_back(Parallax(screen_width, screen_height, 1.6));
	backgrounds.push_back(Parallax(screen_width, screen_height, 0.8));
	backgrounds.push_back(Parallax(screen_width, screen_height, 0.4));
	// backgrounds.push_back(Parallax(screen_width, screen_height, 0.2));

	diamonds.push_back(Diamond(50, screen_height * 0.69 + 30, 2.5));
	fires.push_back(Fire(100, screen_height * 0.69 + 30, 2.5));
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration, int previous_score) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Mix_Music * background_music = Mix_LoadMUS("../assets/background_music.wav");
	Mix_Chunk * diamond_sf = Mix_LoadWAV("../assets/sound_01.wav");
	Mix_PlayMusic(background_music, 0);

	State state = State();

	state.SetBackgrounds(backgrounds);
	state.SetPlayer(player);
	state.SetRunningStatus(true);

	state.GenerateChallenges();

  while (state.GetRunningStatus()) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(state);
    Update(*diamond_sf, state);
    renderer.Render(state);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(state.GetPlayer().consume_score, state.GetLevel(), previous_score, frame_count);
			player.consume_score = state.GetPlayer().consume_score;
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

	Mix_FreeMusic(background_music);
}

void Game::Update(Mix_Chunk &diamond_sf, State &state) {
	if (!player.alive) return;

	// update player
	state.GetPlayer().SetAction(state.GetKeysPressed(), state.GetPreviousKeysPressed());
	state.GetPlayer().Update();

  // update diamonds
	for (size_t i = 0; i < state.GetDiamonds().size(); i++) {
		state.GetDiamonds()[i].SetDirection(state.GetKeysPressed(), state.GetPreviousKeysPressed());
		state.GetDiamonds()[i].Update();
	}

  // update fires
	for (size_t i = 0; i < state.GetFires().size(); i++) {
		state.GetFires()[i].SetDirection(state.GetKeysPressed(), state.GetPreviousKeysPressed());
		state.GetFires()[i].Update();
	}

	// update backgrounds
	for (size_t i = 0; i < state.GetBackgrounds().size(); i++) {
		state.GetBackgrounds()[i].SetDirection(state.GetKeysPressed(), state.GetPreviousKeysPressed());
		state.GetBackgrounds()[i].Update();
	}

	Detect(diamond_sf, state);

	// diamonds.push_back(Diamond(50, state.GetPlayer()->y + 30, 2.5));
}

int Game::GetScore() const { return player.consume_score; }
int Game::GetSize() const { return 1; }

void Game::Detect(Mix_Chunk &diamond_sf, State &state) const {

	for (size_t i = 0; i < state.GetDiamonds().size(); i++)
		{
			bool collision = state.GetPlayer().PlayerCell(state.GetDiamonds()[i].GetX(), state.GetDiamonds()[i].GetY());

			if (collision) {
				Mix_PlayChannel(-1, &diamond_sf, 0);

				state.GetDiamonds().erase(state.GetDiamonds().begin() + i);
				state.GetPlayer().consume_score += 1;
				if (state.GetDiamonds().size() == 0) {
					state.SetLevel(state.GetLevel() + 1);
				}
			}
		}

	for (size_t i = 0; i < state.GetFires().size(); i++)
		{
			bool collision = state.GetPlayer().PlayerCell(state.GetFires()[i].GetX(), state.GetFires()[i].GetY());
			if (collision) {
				state.GetPlayer().Die();
				state.SetKeysPressed(KeysPressed::keyNone);
			}
		}
}
