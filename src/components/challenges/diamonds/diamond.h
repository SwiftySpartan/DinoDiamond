#ifndef DIAMOND_H
#define DIAMOND_H

#include "../challenge.h"
#include "../../../utils/keys.h"

class Diamond : public Challenge {
 public:
	Diamond(int x, int y, float speed) : Challenge(x, y, speed) {
		SetChallengeType(ChallengeType::BENEFICIAL);
		SetSurface(IMG_Load("../assets/diamond.png"));
	};

	// GenerateDiamondsForever() {};

 	private:
};

#endif
