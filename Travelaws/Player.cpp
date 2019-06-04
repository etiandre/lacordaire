#include "pch.h"
//
#include <iostream>
#include "Player.h"
#include "SFML/Graphics.hpp"

Player::Player() {
  _health = 100, _moveSpeed.x = 5, _moveSpeed.y = 5, _inertia = 0.8;
  velocity = sf::Vector2f(0, 0);
  if (!playerTexture.loadFromFile("assets/textures/slime.png")) {
    std::cout << "erreur chargement slime.png" << std::endl;
    exit(1);
  }
  playerSprite.setTexture(playerTexture);
  playerSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
  _animation.x = 0, _animation.y = 0;

}

void Player::setPosition(int x, int y) {
  velocity.x = 0;
  velocity.y = 0;
  playerSprite.setPosition(x, y);
}

void Player::move(int x, int y) {
  velocity.x = x*_moveSpeed.x;
  velocity.y = y*_moveSpeed.y;
}

void Player::updatePosition() {

  int x = playerSprite.getPosition().x + velocity.x;
  int y = playerSprite.getPosition().y + velocity.y;
  velocity *= _inertia;
	playerSprite.setPosition(x, y);
}

sf::Vector2i Player::getPosition() {
  return (sf::Vector2i)playerSprite.getPosition();
}

void Player::accelerate(int x, int y) {
	velocity.x += x;
	velocity.y += y;
}


sf::Vector2i Player::animatorState() {
	return _animation;
}

void Player::animator(int x, int y) {
	_animation.x = x;
	_animation.y = y;
}

void Player::updateAnimation() {
	if (_animation.x >= 5) {
		_animation.x -= 5;
	}

	playerSprite.setTextureRect(sf::IntRect(_animation.x * BLOCK_SIZE, _animation.y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
}