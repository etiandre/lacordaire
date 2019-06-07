#include "Player.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include "Animation.hpp"

Player::Player() : Actor("Player"), moveSpeed(2) {
  hitbox = sf::FloatRect(10, 22, 12, 10);
  sf::Texture* texturePointer =
      TextureManager::loadTexture("player", "assets/textures/slime.png");
  if (texturePointer == NULL) {
    std::cout << "erreur chargement texture slime !" << std::endl;
    exit(1);
  }
  sprite.setTexture(*texturePointer);
  sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
  _anim.addAnimation(texturePointer, sf::Vector2i(10, 3), sf::seconds(0.25));
}
