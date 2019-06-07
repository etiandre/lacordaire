#include "Player.h"
#include <algorithm>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "TextureManager.h"

Player::Player()
    : Actor("Player"),
      _maxMoveSpeed(180),
      _groundAcceleration(18),
      _airAcceleration(6),
      _jumpAcceleration(100),
      _groundFriction(0.5),
      _airFriction(1) {
  hitbox = sf::FloatRect(10, 22, 12, 10);
  sf::Texture* texturePointer =
      TextureManager::loadTexture("player", "assets/textures/slime.png");
  if (texturePointer == NULL) {
    std::cout << "erreur chargement texture slime !" << std::endl;
    exit(1);
  }
  sprite.setTexture(*texturePointer);
  sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
  _animation.x = 0, _animation.y = 0;
}

sf::Vector2i Player::animatorState() { return _animation; }

void Player::animator(int x, int y) {
  _animation.x = x;
  _animation.y = y;
}

void Player::updateAnimation() {
  if (_animation.x >= 5) {
    _animation.x -= 5;
  }
  sprite.setTextureRect(
      sf::IntRect(_animation.x * 32, _animation.y * 32, 32, 32));
}

void Player::manageInputs(sf::Time dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    if (onGround)
      velocity.x -= _groundAcceleration;
    else
      velocity.x -= _airAcceleration;
    if (velocity.x < -_maxMoveSpeed) velocity.x = -_maxMoveSpeed;

    animator(animatorState().x, 0);
    animator(animatorState().x + 1, animatorState().y);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    if (onGround)
      velocity.x += _groundAcceleration;
    else
      velocity.x += _airAcceleration;
    if (velocity.x > _maxMoveSpeed) velocity.x = _maxMoveSpeed;

    animator(animatorState().x, 1);
    animator(animatorState().x + 1, animatorState().y);
  } else {
    if (onGround)
      velocity.x *= _groundFriction;
    else
      velocity.x *= _airFriction;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) {
    velocity.y = -_jumpAcceleration;
  }
}