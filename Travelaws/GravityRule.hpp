#pragma once
#include "Rule.h"

class GravityRule : public Rule {
 private:
  //const float gSquared = 96.2361;
  const float gSquared;

 public:
  GravityRule();
  void update(GameData& gameData, sf::Time dt);
  const char* getName();
  int getScore() override;
};