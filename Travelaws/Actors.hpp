#pragma once
#include "SFML/Graphics.hpp"

struct Position {
	int x;
	int y;
};

struct Size {
	int width;
	int height;
};


class Actors
{
public:
	Actors();
	virtual sf::Vector2i getPosition();
	virtual void setPosition(int x, int y);
	virtual void updatePosition();

	sf::Sprite actorSprite;
	sf::Vector2f velocity;
};


