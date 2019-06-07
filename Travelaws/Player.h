#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Player : public Actor {
 public:
  Player();
  void updateAnimation();
  void manageInputs();
  void animator(int x, int y);
  sf::Vector2i animatorState();
  bool onGround = false;

 private:
  sf::Vector2i _animation;
  float _acceleration;
  float _jumpAcceleration;
  float _maxMoveSpeed;
};