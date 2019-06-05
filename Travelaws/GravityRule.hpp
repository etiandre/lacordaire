#pragma once
#include "Rule.h"

class GravityRule : public Rule {
 private:
  float gravity = 1;

 public:
  void update(GameData& gameData);
  const char* getName();
};