#pragma once
#include <SFML/Graphics.hpp>
#include "GameData.h"
class Game {
 public:
  Game(int width, int height);
  void run();

 private:
  sf::View _view;
  GameData _gameData;
};