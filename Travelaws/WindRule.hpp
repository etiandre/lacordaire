#pragma once
#include "Rule.h"

class WindRule : public Rule {
 public:
  void update(GameData& gameData, sf::Time dt);
  const char* getName();
  int getScore() override;

 private:
  const float _windForce = -60;
};
