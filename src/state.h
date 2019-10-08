#ifndef STATE_H
#define STATE_H

#include "diamond.h"
#include "player.h"
#include "parallax.h"
#include "keys.h"

class State {
	public:
		State() {};
		~State() {};

		// Setters
		void SetKeysPressed(KeysPressed p) {
			this->key_KeysPressed = p;
		}

		void SetPreviousKeysPressed(KeysPressed p) {
			this->previous_key_KeysPressed = p;
		}

		void SetPlayer(Player * p) {
			this->player = p;
		}

		void SetDiamonds(std::vector<Diamond> * d) {
			this->diamonds = d;
		}

		void SetBackgrounds(std::vector<Parallax> * b) {
			this->backgrounds = b;
		}

		void SetRunningStatus(bool const &running) {
			this->running = running;
		}

		void SetLevel(int l) {
			this->level = l;
		}

		// Getters
		KeysPressed GetKeysPressed() {
			return this->key_KeysPressed;
		}

		KeysPressed GetPreviousKeysPressed() {
			return this->previous_key_KeysPressed;
		}

		Player * GetPlayer() {
			return this->player;
		}

		std::vector<Diamond> & GetDiamonds() {
			return *diamonds;
		}

		std::vector<Parallax> & GetBackgrounds() {
			return *backgrounds;
		}

		bool GetRunningStatus() {
			return this->running;
		}

		int GetLevel() {
			return this->level;
		}

	private:
		Player * player;
		std::vector<Diamond> * diamonds;
		std::vector<Parallax> * backgrounds = nullptr;
		int level{1};
		bool running;
		KeysPressed key_KeysPressed;
		KeysPressed previous_key_KeysPressed;
};

#endif
