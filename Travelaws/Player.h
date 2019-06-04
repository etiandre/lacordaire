#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Actors.hpp"

class Player : public Actors {
 public:
  Player();
  void setPosition(int x, int y);
  void move(int x, int y);
  sf::Vector2i getPosition();

  sf::Sprite playerSprite;
  void updatePosition();
  enum Direction{Left,Right};
  void updateAnimation();
  void animator(int x, int y);
  sf::Vector2i animatorState();
  sf::Vector2f velocity;

 private:
  int _health;
  sf::Vector2i _moveSpeed;//à terme à bouger dans InputManager
  float _inertia;
  sf::Vector2i _animation;
};