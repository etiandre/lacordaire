#pragma once
#include "GameData.h"

class Rule {
 public:
  virtual void update(GameData& gameData) = 0;
};