#pragma once
#include "Rule.h"

class GravityRule : public Rule {
 private:
  const float gravity = 0.2;

 public:
  void update(GameData& gameData);
  const char* getName();
};