#pragma once
#include <SFML/Graphics.hpp>

class Actor {
 public:
  Actor(const char* name);
  void teleportTo(float x, float y);
  void teleportTo(sf::Vector2f position);
  sf::Vector2f getPosition();
  virtual void update();

  sf::Vector2f velocity;

  sf::Sprite sprite;
  sf::FloatRect hitbox;
  void draw(sf::RenderWindow& window);

  bool collidesWith(sf::FloatRect rect);

 protected:
  float _inertia;
  const char* _name;
};