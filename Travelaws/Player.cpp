#include "pch.h"
//
#include <iostream>
#include "Player.h"
#include "SFML/Graphics.hpp"

Player::Player() {
  _health = 100, _moveSpeed = 5, _inertia = 0.8;
  _velocity = sf::Vector2f(0, 0);
  if (!playerTexture.loadFromFile("assets/textures/slime.png")) {
    std::cout << "erreur chargement slime.png" << std::endl;
    exit(1);
  }
  playerSprite.setTexture(playerTexture);
  playerSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

void Player::setPosition(int x, int y) {
  _velocity.x = 0;
  _velocity.y = 0;
  playerSprite.setPosition(x, y);
}

void Player::move(int x, int y) {
  _velocity.x = x*_moveSpeed;
  _velocity.y = y*_moveSpeed;
}

void Player::updatePosition() {
  int x = playerSprite.getPosition().x + _velocity.x;
  int y = playerSprite.getPosition().y + _velocity.y;
  _velocity *= _inertia;
	playerSprite.setPosition(x, y);
}

sf::Vector2i Player::getPosition() {
  return (sf::Vector2i)playerSprite.getPosition();
}
