#pragma once
#include "GameData.h"

struct GameData;

class Rule {
 public:
  virtual void update(GameData& gameData, sf::Time dt){};
  virtual const char* getName() = 0;
  virtual void draw(sf::RenderWindow& window) {};
  bool active = true;
};