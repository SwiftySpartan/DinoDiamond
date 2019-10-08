#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "challenge.h"
#include "parallax.h"
#include "keys.h"
#include "state.h"

class Controller {
 public:
  void HandleInput(State &state) const;
};

#endif
