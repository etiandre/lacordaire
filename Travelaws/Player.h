#pragma once
#include <SFML/Graphics.hpp>
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

 private:
  int _health;
  sf::Vector2i _moveSpeed;
  float _inertia;
  sf::Vector2f _velocity;

  sf::Texture playerTexture;
};