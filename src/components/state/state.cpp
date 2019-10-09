#include "state.h"

void State::GenerateChallenges() {
	std::thread t(&State::GenerateDiamonds, this, std::move(diamond_prms));
	std::thread t2(&State::GenerateFires, this, std::move(fire_prms));

	std::vector<Diamond> d = diamond_ftr.get();
	SetDiamonds(d);

	std::vector<Fire> f = fire_ftr.get();
	SetFires(f);

	t.join();
	t2.join();
}

void State::GenerateDiamonds(std::promise<std::vector<Diamond>> && promise) {
		std::vector<Diamond> d = {
			Diamond(800, 650, 2.5),
			Diamond(1400, 650, 2.5),
			Diamond(1700, 650, 2.5),
			Diamond(2100, 650, 2.5),
			Diamond(2700, 650, 2.5),
			Diamond(2900, 650, 2.5) };

    promise.set_value(d);
}

void State::GenerateFires(std::promise<std::vector<Fire>> && promise) {
		std::vector<Fire> f = {
			Fire(800, 650, 2.5),
			Fire(1400, 650, 2.5),
			Fire(1700, 650, 2.5),
			Fire(2100, 650, 2.5),
			Fire(2700, 650, 2.5),
			Fire(2900, 650, 2.5) };
    promise.set_value(f);
}

// Setters
void State::SetKeysPressed(KeysPressed p) {
	this->key_pressed = p;
}

void State::SetPreviousKeysPressed(KeysPressed p) {
	this->previous_key_pressed = p;
}

void State::SetPlayer(Player& p) {
	this->player = p;
}

void State::SetDiamonds(std::vector<Diamond>& d) {
	this->diamonds = d;
}

void State::SetFires(std::vector<Fire>& f) {
	this->fires = f;
}

void State::SetBackgrounds(std::vector<Parallax>& b) {
	this->backgrounds = b;
}

void State::SetRunningStatus(bool const &running) {
	this->running = running;
}

void State::SetLevel(int l) {
	this->level = l;
}

// Getters
KeysPressed & State::GetKeysPressed() {
	return this->key_pressed;
}

KeysPressed & State::GetPreviousKeysPressed() {
	return this->previous_key_pressed;
}

Player & State::GetPlayer() {
	return this->player;
}

std::vector<Diamond> & State::GetDiamonds() {
	return diamonds;
}

std::vector<Fire> & State::GetFires() {
	return fires;
}

std::vector<Parallax> & State::GetBackgrounds() {
	return backgrounds;
}

bool State::GetRunningStatus() {
	return this->running;
}

int State::GetLevel() {
	return this->level;
}
