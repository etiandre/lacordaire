#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "Player.h"

struct GameData {
  Player player;
};

//typedef std::shared_ptr<GameData> GameDataRef;

class Game {
 public:
  Game(int width, int height, std::string title);

 private:
  sf::RenderWindow window;
  sf::View view;
  GameData gameData;
  tmx::Map map;

  void loadLevel(int levelID);
  void mainLoop();
};