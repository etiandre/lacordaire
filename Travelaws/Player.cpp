#include "pch.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Player.h"

Player::Player()
{
	_location.x = 0 , _location.y = 0;
	_health = 100, _speed = 5, _size.height=1, _size.width=1;
	if (!playerTexture.loadFromFile("assets/textures/slime.png")) {
		std::cout << "erreur chargement slime.png" << std::endl;
	}
	playerTexture.setSmooth(true);  // lisse la texture
	playerSprite.setTexture(playerTexture);
}

Player::~Player()
{
}

void Player::setPosition(int x, int y)
{
	_location.x = x;
	_location.y = y;

}

Position& Player::getPosition()
{
	return _location;
}

Size& Player::getSize()
{
	return _size;
}


