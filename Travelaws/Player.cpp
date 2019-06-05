#include "Player.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "TextureManager.h"


Player::Player() : Actor("Player") {
  moveSpeed = 5;
  box = sf::FloatRect(10, 22, 12, 10);
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