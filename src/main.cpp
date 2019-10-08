#include <iostream>
#include <fstream>
#include <string>

#include "controller.h"
#include "game.h"
#include "renderer.h"


int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1300};
  constexpr std::size_t kScreenHeight{900};
  constexpr std::size_t kGridWidth{1300};
  constexpr std::size_t kGridHeight{900};

	std::ifstream infile("previous_score.txt");
	std::string line;
	int previous_score = 0;
	while (std::getline(infile, line))
	{
			previous_score = std::stoi(line);
	}

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame, previous_score);

	std::ofstream myfile;
  myfile.open ("previous_score.txt");
  myfile << game.GetScore();
	std::cout << "Successfully saved score: " << game.GetScore() << std::endl;
  myfile.close();

  return 0;
}
