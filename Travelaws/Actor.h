#pragma once
#include <SFML/Graphics.hpp>

class Actor {
 public:
  Actor(const char* name);
  void teleportTo(float x, float y);
  sf::Vector2f getPosition();
  virtual void update();

  sf::Vector2f velocity;

  sf::Sprite sprite;
  sf::FloatRect box;
  void draw(sf::RenderWindow& window);

 protected:
  float _inertia;
  const char* _name;
};