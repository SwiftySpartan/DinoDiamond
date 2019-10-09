#include "state.h"

void State::ForeverGenerateChallenges() {
	std::thread t(&State::GenerateDiamonds, this, std::move(prms));
	// threads.push_back(&t);

	std::vector<Diamond> d = ftr.get();
	for (size_t i = 0; i < d.size(); i++) {
		diamonds->push_back(d[i]);
	}

	t.join();
}

void State::GenerateDiamonds(std::promise<std::vector<Diamond>> && promise) {
		std::vector<Diamond> d;
		d.push_back(Diamond(20, 20, 2.5));
    promise.set_value(d);
}

// Setters
void State::SetKeysPressed(KeysPressed p) {
	this->key_KeysPressed = p;
}

void State::SetPreviousKeysPressed(KeysPressed p) {
	this->previous_key_KeysPressed = p;
}

void State::SetPlayer(Player * p) {
	this->player = p;
}

void State::SetDiamonds(std::vector<Diamond> * d) {
	this->diamonds = d;
}

void State::SetFires(std::vector<Fire> * f) {
	this->fires = f;
}

void State::SetBackgrounds(std::vector<Parallax> * b) {
	this->backgrounds = b;
}

void State::SetRunningStatus(bool const &running) {
	this->running = running;
}

void State::SetLevel(int l) {
	this->level = l;
}

// Getters
KeysPressed State::GetKeysPressed() {
	return this->key_KeysPressed;
}

KeysPressed State::GetPreviousKeysPressed() {
	return this->previous_key_KeysPressed;
}

Player * State::GetPlayer() {
	return this->player;
}

std::vector<Diamond> & State::GetDiamonds() {
	return *diamonds;
}

std::vector<Fire> & State::GetFires() {
	return *fires;
}

std::vector<Parallax> & State::GetBackgrounds() {
	return *backgrounds;
}

bool State::GetRunningStatus() {
	return this->running;
}

int State::GetLevel() {
	return this->level;
}
