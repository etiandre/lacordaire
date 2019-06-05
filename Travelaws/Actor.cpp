#include "Actor.h"
#include "TextureManager.h"
#include "DEFINITIONS.h"
Actor::Actor(const char* name) : _name(name) {
  _inertia = 0.8;
  velocity = sf::Vector2f(0, 0);
}

void Actor::setPosition(int x, int y) {
  velocity.x = 0;
  velocity.y = 0;
  sprite.setPosition(x, y);
}

sf::Vector2i Actor::getPosition() { return (sf::Vector2i)sprite.getPosition(); }

void Actor::update() {
  int x = sprite.getPosition().x + velocity.x;
  int y = sprite.getPosition().y + velocity.y;
  velocity.x *= _inertia;
  sprite.setPosition(x, y);
}

void Actor::draw(sf::RenderWindow& window) { window.draw(sprite); }