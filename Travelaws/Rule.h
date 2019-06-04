#pragma once
#include "GameData.h"

class Rule {
 public:
  virtual void update(GameData& gameData){};
  virtual void physicsUpdate(GameData& gameData){};
  virtual const char* getName() = 0;
  virtual void draw(sf::RenderWindow& window) {};
  bool active = true;
};