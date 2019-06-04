#pragma once
#include "Rule.h"

class GravityRule : public Rule {
 private:
  float gravity = 3;

 public:
  void physicsUpdate(GameData& gameData);
  const char* getName();
};