#pragma once
#include "Rule.h"

class WindRule : public Rule {
 public:
  void physicsUpdate(GameData& gameData);
  const char* getName();

 private:
  int _windForce = 0;
};
