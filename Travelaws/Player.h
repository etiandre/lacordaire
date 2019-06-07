#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Player : public Actor {
 public:
  Player();
  void updateAnimation();
  void manageInputs(sf::Time dt);
  void animator(int x, int y);
  sf::Vector2i animatorState();
  bool onGround = false;

 private:
  sf::Vector2i _animation;
  float _airAcceleration;
  float _groundAcceleration;
  float _jumpAcceleration;
  float _maxMoveSpeed;
  float _groundFriction;
  float _airFriction;
};