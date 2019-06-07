#pragma once
#include "Rule.h"

class WindRule : public Rule {
 public:
  void update(GameData& gameData);
  const char* getName();
  int getScore() override;

 private:
  int _windForce = 0;
};
