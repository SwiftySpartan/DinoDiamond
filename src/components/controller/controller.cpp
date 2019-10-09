#include "controller.h"

void Controller::HandleInput(State &state) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      state.SetRunningStatus(false);
    } else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_r) {
				std::cout << "restart game" << std::endl;
			}

			if (!state.GetPlayer().alive) {
				return;
			}

			state.SetPreviousKeysPressed(state.GetKeysPressed());

      switch (e.key.keysym.sym) {
				case SDLK_s:
					state.SetKeysPressed(KeysPressed::keySprint);
					break;

        case SDLK_UP:
					state.SetKeysPressed(KeysPressed::keyJump);
					state.GetPlayer().SetIsJumping(false);
          break;

        case SDLK_DOWN:
					state.SetKeysPressed(KeysPressed::keyNone);
          break;

				case SDLK_SPACE:
					state.SetKeysPressed(KeysPressed::keyJump);
					state.GetPlayer().SetIsJumping(false);
          break;

        case SDLK_LEFT:
					state.SetKeysPressed(KeysPressed::keyLeft);
          break;

        case SDLK_RIGHT:
					state.SetKeysPressed(KeysPressed::keyRight);
          break;
      }
    }
  }
}
