#include "Actor.h"
#include "DEBUG.h"
#include "DEFINITIONS.h"
#include "TextureManager.h"
#include <iostream>

Actor::Actor(const char* name)
    : _name(name), _inertia(0.9f), velocity(), _anim() {}

void Actor::teleportTo(float x, float y) {
  velocity.x = 0;
  velocity.y = 0;
  sprite.setPosition(x, y);
}

void Actor::teleportTo(sf::Vector2f position) {
  teleportTo(position.x, position.y);
}

sf::Vector2f Actor::getPosition() { return sprite.getPosition(); }

void Actor::update(sf::Time dt) {
  float x = sprite.getPosition().x + velocity.x * dt.asSeconds();
  float y = sprite.getPosition().y + velocity.y * dt.asSeconds();
  std::cout << x << " " << y << std::endl;  
	// velocity.x *= _inertia;
               sprite.setPosition(x, y);
}

void Actor::draw(sf::RenderWindow& window) {
  window.draw(sprite);
  sprite.setTextureRect(_anim.textureRect);
#ifdef DEBUG
  sf::Vertex line[2];
  line[0].position = sprite.getPosition();
  line[0].color = sf::Color::Red;
  line[1].position = sprite.getPosition() + velocity;
  line[1].color = sf::Color::Red;
  window.draw(line, 2, sf::LineStrip);
#endif  // DEBUG
}

bool Actor::collidesWith(sf::FloatRect rect) {
  auto box = hitbox;
  box.left += sprite.getPosition().x;
  box.top += sprite.getPosition().y;
  return box.intersects(rect);
}
