#ifndef FIRE_H
#define FIRE_H

#include "challenge.h"
#include "keys.h"

class Fire : public Challenge {
 public:
	Fire(int x, int y, float speed) : Challenge(x, y, speed) {
		SetChallengeType(ChallengeType::DETRIMENTAL);
		SetSurface(IMG_Load("../assets/fire.png"));
	};

	// GenerateDiamondsForever() {};

 	private:
};

#endif
