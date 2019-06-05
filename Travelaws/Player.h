#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Player : public Actor {
 public:
  Player();
  void updateAnimation();
  void animator(int x, int y);
  sf::Vector2i animatorState();
  float moveSpeed;
  bool onGround = false;

 private:
  sf::Vector2i _animation;
};