#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <iostream>
#include <SDL2/SDL.h>

#include "../player/player.h"
#include "../challenges/challenge.h"
#include "../parallax/parallax.h"
#include "../../utils/keys.h"
#include "../state/state.h"

class Controller {
 public:
  void HandleInput(State &state) const;
};

#endif
