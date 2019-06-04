#pragma once
#include "Rule.h"

class WindRule : public Rule {
 public:
  void physicsUpdate(GameData &gameData);

 private:
  int _windForce = 0;
};
