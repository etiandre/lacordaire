#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Player : public Actor {
 public:
  Player();
  void manageInputs(sf::Time dt);
  bool onGround = false;

 private:
  float _airAcceleration;     // en pixels / s^2
  float _groundAcceleration;  // en pixels / s^2
  float _jumpAcceleration;    // en pixels / s^2
  float _maxMoveSpeed;        // en pixels / s
  float _groundFriction;  // coefficient entre 0 et 1: 0 = arrêt immédiat, 1 =
                          // pas de friction
  float _airFriction;     // idem

  enum AnimationState { Idle = 0, WalkRight = 4, WalkLeft = 1 };
};