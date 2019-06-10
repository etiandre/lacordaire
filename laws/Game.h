#pragma once
#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "StateMachine.hpp"

/*
Base game class
*/
class Game {
 public:
  /* Constructor with width and height of window in pixels*/
  Game(int width, int height);
  void run();

 private:
  sf::View _view;
  GameData _gameData;
  StateMachine _stateMachine;
};