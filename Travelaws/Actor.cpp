#include "Actor.h"
#include "DEFINITIONS.h"
#include "TextureManager.h"

Actor::Actor(const char* name) : _name(name), _inertia(0.9f), velocity(), _anim() {
}

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
  float x = sprite.getPosition().x + velocity.x;
  float y = sprite.getPosition().y + velocity.y;
  velocity.x *= _inertia;
  sprite.setPosition(x, y);
  _anim.update(0, dt);
}

void Actor::draw(sf::RenderWindow& window) { window.draw(sprite); }

bool Actor::collidesWith(sf::FloatRect rect) {
  auto box = hitbox;
  box.left += sprite.getPosition().x;
  box.top += sprite.getPosition().y;
  return box.intersects(rect);
}

