#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Player : public Actor {
 public:
  Player();
  float moveSpeed;
  bool onGround = false;

};