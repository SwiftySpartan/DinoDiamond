#ifndef STATE_H
#define STATE_H

#include <thread>
#include <future>
#include <chrono>

#include "../challenges/diamonds/diamond.h"
#include "../challenges/fires/fire.h"
#include "../player/player.h"
#include "../parallax/parallax.h"
#include "../../utils/keys.h"

class State {
	public:
		State() {};

		void GenerateChallenges();

		// Setters
		void SetKeysPressed(KeysPressed p);

		void SetPreviousKeysPressed(KeysPressed p);

		void SetPlayer(Player& p);

		void SetDiamonds(std::vector<Diamond>& d);

		void SetFires(std::vector<Fire>& f);

		void SetBackgrounds(std::vector<Parallax>& b);

		void SetRunningStatus(bool const &running);

		void SetLevel(int l);

		// Getters
		KeysPressed & GetKeysPressed();

		KeysPressed & GetPreviousKeysPressed();

		Player & GetPlayer();

		std::vector<Diamond> & GetDiamonds();

		std::vector<Fire> & GetFires();

		std::vector<Parallax> & GetBackgrounds();

		bool GetRunningStatus();

		int GetLevel();

	private:
		void GenerateDiamonds(std::promise<std::vector<Diamond>> && promise);
		void GenerateFires(std::promise<std::vector<Fire>> && promise);

		Player player;
		std::vector<Diamond> diamonds;
		std::vector<Fire> fires;
		std::vector<Parallax> backgrounds;

		int level{1};
		bool running;

		KeysPressed key_pressed;
		KeysPressed previous_key_pressed;

    std::promise<std::vector<Diamond>> diamond_prms;
    std::future<std::vector<Diamond>> diamond_ftr = diamond_prms.get_future();

		std::promise<std::vector<Fire>> fire_prms;
    std::future<std::vector<Fire>> fire_ftr = fire_prms.get_future();
};

#endif
