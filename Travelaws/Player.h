#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"

struct Position {
  int x;
  int y;
};

struct Size {
  int width;
  int height;
};

class Player {
 public:
  Player();
  void setPosition(int x, int y);
  void move(int x, int y);
  sf::Vector2i getPosition();
  void accelerate(int x, int y);
  sf::Sprite playerSprite;
  void updatePosition();
  sf::Texture playerTexture;
  enum Direction{Left,Right};
  void updateAnimation();
  void animator(int x, int y);
  sf::Vector2i animatorState();

 private:
  int _health;
  sf::Vector2i _moveSpeed;
  float _inertia;
  sf::Vector2f _velocity;
  sf::Vector2i _animation;




  sf::Texture playerTexture;
};