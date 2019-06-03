#pragma once
#include "Travelaws.h"

class Rule {
 public:
  virtual void update(GameData &gameData) = 0;
  double scoreMultiplicator;
};