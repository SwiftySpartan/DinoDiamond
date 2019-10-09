#ifndef STATE_H
#define STATE_H

#include <thread>
#include <future>
#include <chrono>

#include "diamond.h"
#include "fire.h"
#include "player.h"
#include "parallax.h"
#include "keys.h"

class State {
	public:
		State() {};
		~State() {
			for (size_t i = 0; i < threads.size(); i++) {
				threads[i]->join();
			}
		};

		void ForeverGenerateChallenges();

		// Setters
		void SetKeysPressed(KeysPressed p);

		void SetPreviousKeysPressed(KeysPressed p);

		void SetPlayer(Player * p);

		void SetDiamonds(std::vector<Diamond> * d);

		void SetFires(std::vector<Fire> * f);

		void SetBackgrounds(std::vector<Parallax> * b);

		void SetRunningStatus(bool const &running);

		void SetLevel(int l);

		// Getters
		KeysPressed GetKeysPressed();

		KeysPressed GetPreviousKeysPressed();

		Player * GetPlayer();

		std::vector<Diamond> & GetDiamonds();

		std::vector<Fire> & GetFires();

		std::vector<Parallax> & GetBackgrounds();

		bool GetRunningStatus();

		int GetLevel();

	private:
		void GenerateDiamonds(std::promise<std::vector<Diamond>> && promise);

		Player * player;
		std::vector<Diamond> * diamonds;
		std::vector<Fire> * fires;
		std::vector<Parallax> * backgrounds = nullptr;
		int level{1};
		bool running;
		KeysPressed key_KeysPressed;
		KeysPressed previous_key_KeysPressed;
		std::vector<std::thread *> threads;

    std::promise<std::vector<Diamond>> prms;
    std::future<std::vector<Diamond>> ftr = prms.get_future();
};

#endif
