#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

/*
Classe décrivant le joueur (slime)
*/
class Player : public Actor {
 public:
  Player();
  // mouvement
  void manageInputs(sf::Time dt);
  // vrai si le slime touche le sol (managé par CollisionRule)
  bool onGround = false;

 private:
  float _airAcceleration;     // en pixels / s^2
  float _groundAcceleration;  // en pixels / s^2
  float _jumpAcceleration;    // en pixels / s^2
  float _maxMoveSpeed;        // en pixels / s
  float _groundFriction;  // coefficient entre 0 et 1: <0 = décélération, 1 =
                          // pas de friction, >0 = accélération
  float _airFriction;     // idem

  enum AnimationState { Idle = 0, WalkRight = 4, WalkLeft = 1 };
};