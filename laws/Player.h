#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

/*
Classe d�crivant le joueur (slime)
*/
class Player : public Actor {
 public:
  Player();
  // mouvement
  void manageInputs(sf::Time dt);
  // vrai si le slime touche le sol (manag� par CollisionRule)
  bool onGround = false;

 private:
  float _airAcceleration;     // en pixels / s^2
  float _groundAcceleration;  // en pixels / s^2
  float _jumpAcceleration;    // en pixels / s^2
  float _maxMoveSpeed;        // en pixels / s
  float _groundFriction;  // coefficient entre 0 et 1: <0 = d�c�l�ration, 1 =
                          // pas de friction, >0 = acc�l�ration
  float _airFriction;     // idem

  enum AnimationState { Idle = 0, WalkRight = 4, WalkLeft = 1 };
};