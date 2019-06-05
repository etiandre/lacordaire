#include "Actor.h"
#include "DEFINITIONS.h"
#include "TextureManager.h"

Actor::Actor(const char* name) : _name(name), _inertia(0.9f), velocity() {}

void Actor::teleportTo(float x, float y) {
  velocity.x = 0;
  velocity.y = 0;
  sprite.setPosition(x, y);
}

sf::Vector2f Actor::getPosition() { return sprite.getPosition(); }

void Actor::update() {
  float x = sprite.getPosition().x + velocity.x;
  float y = sprite.getPosition().y + velocity.y;
  velocity.x *= _inertia;
  sprite.setPosition(x, y);
}

void Actor::draw(sf::RenderWindow& window) { window.draw(sprite); }