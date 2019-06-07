#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Player : public Actor {
 public:
  Player();
  void manageInputs(sf::Time dt);
  bool onGround = false;

 private:
  float _airAcceleration;
  float _groundAcceleration;
  float _jumpAcceleration;
  float _maxMoveSpeed;
  float _groundFriction;
  float _airFriction;
};