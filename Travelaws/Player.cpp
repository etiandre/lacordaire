#include "Player.h"
#include <algorithm>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include "Animation.hpp"

Player::Player()
	: Actor("Player"),
	_maxMoveSpeed(180),
	_groundAcceleration(18),
	_airAcceleration(6),
	_jumpAcceleration(350),
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
	_anim.addAnimation(texturePointer, sf::Vector2i(10, 10), sf::seconds(0.1f));
}

void Player::manageInputs(sf::Time dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (onGround)
			velocity.x -= _groundAcceleration;
		else
			velocity.x -= _airAcceleration;
		if (velocity.x < -_maxMoveSpeed) velocity.x = -_maxMoveSpeed;
		_anim.update(2, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (onGround)
			velocity.x += _groundAcceleration;
		else
			velocity.x += _airAcceleration;
		if (velocity.x > _maxMoveSpeed) velocity.x = _maxMoveSpeed;
		_anim.update(4, dt);
	}
	else {
		if (onGround)
			velocity.x *= _groundFriction;
		else
			velocity.x *= _airFriction;
		_anim.update(0, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) {
		velocity.y = -_jumpAcceleration;
		_anim.update(3, dt);
	}
}