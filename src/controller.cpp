#include <iostream>
#include <SDL2/SDL.h>

#include "controller.h"
#include "parallax.h"
#include "state.h"

void Controller::HandleInput(State &state) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      state.SetRunningStatus(false);
    } else if (e.type == SDL_KEYDOWN) {
			if (state.GetPlayer() == nullptr) {
				return;
			}

			if (!state.GetPlayer()->alive) {
				return;
			}

			state.SetPreviousKeysPressed(state.GetKeysPressed());

      switch (e.key.keysym.sym) {
				case SDLK_s:
					state.SetKeysPressed(KeysPressed::keySprint);
					break;

        case SDLK_UP:
					state.SetKeysPressed(KeysPressed::keyJump);
          break;

        case SDLK_DOWN:
					state.SetKeysPressed(KeysPressed::keyNone);
          break;

				case SDLK_SPACE:
					state.SetKeysPressed(KeysPressed::keyJump);
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
