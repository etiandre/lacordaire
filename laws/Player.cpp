#include <thread>

#include <algorithm>
#include <iostream>
#include "Animation.hpp"
#include "Player.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SoundManager.h"
#include "TextureManager.h"

Player::Player()
    : Actor("Player"),
      _maxMoveSpeed(180),
      _groundAcceleration(18),
      _airAcceleration(6),
      _jumpAcceleration(380),
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
  _anim.setAnimationTexture(texturePointer, sf::Vector2i(10, 10),
                            sf::seconds(0.1f));
}

void Player::manageInputs(sf::Time dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    if (onGround)
      velocity.x -= _groundAcceleration;
    else
      velocity.x -= _airAcceleration;
    if (velocity.x < -_maxMoveSpeed) velocity.x = -_maxMoveSpeed;
    _anim.playAnimation(WalkLeft, dt);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    if (onGround)
      velocity.x += _groundAcceleration;
    else
      velocity.x += _airAcceleration;
    if (velocity.x > _maxMoveSpeed) velocity.x = _maxMoveSpeed;
    _anim.playAnimation(WalkRight, dt);
  } else {
    if (onGround)
      velocity.x *= _groundFriction;
    else
      velocity.x *= _airFriction;
    _anim.playAnimation(Idle, dt);
  }

  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) &&
      onGround) {
    velocity.y = -_jumpAcceleration;
    std::thread thread_object(playSound(), "assets/sounds/jump.wav");
    thread_object.detach();
  }
}