#pragma once
#include "GameData.h"

class Rule {
 public:
  virtual void update(GameData& gameData){};
  virtual void physicsUpdate(GameData& gameData){};
  virtual const char* getName() = 0;
  bool active = true;
};