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
  float _airAcceleration; // en pixels / s^2
  float _groundAcceleration; // en pixels / s^2
  float _jumpAcceleration; // en pixels / s^2
  float _maxMoveSpeed; // en pixels / s
  float _groundFriction; // coefficient entre 0 et 1: 0 = arrêt immédiat, 1 = pas de friction
  float _airFriction; // idem
};