#pragma once
#include <SFML/Graphics.hpp>

class Actor {
 public:
  Actor(const char* name);
  void setPosition(int x, int y);
  sf::Vector2i getPosition();
  virtual void update();

  sf::Vector2f velocity;

  sf::Sprite sprite;
  void draw(sf::RenderWindow& window);

 protected:
  float _inertia;
  const char* _name;
};