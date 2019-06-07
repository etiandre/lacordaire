#pragma once
#include "Rule.h"

class GravityRule : public Rule {
 private:
  const float gSquared = 96.2361;

 public:
  void update(GameData& gameData, sf::Time dt);
  const char* getName();
};