#pragma once

#include <tmxlite/Map.hpp>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <string>
#include "Player.h"
#include "GameData.h"
#include "Rule.h"
#include "TextureManager.h"

class Game {
 public:
  Game(int width, int height, std::string title);

 private:
  sf::RenderWindow window;
  sf::View view;
  GameData gameData;
  std::vector<std::unique_ptr<Rule>> rules;
  void loadLevel(int levelID);
  void mainLoop();
  void victory();
  void gameOver();
  void check_state();
};