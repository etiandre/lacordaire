#pragma once
#include "Player.h"

class InputManager {
 public:
  void manageInputs(Player &player);

 private:
  float _acceleration = 2;
  float _maxMoveSpeed = 4;
};
