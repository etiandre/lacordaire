#pragma once


struct Position {
	int x; int y;
};

struct Size {
	int width; int height;
};

class Player
{
public:
	Player();
	~Player();
	void setPosition(int x, int y);
	Position& getPosition();
	Size& getSize();
	sf::Sprite playerSprite;

private:
	int _health;
	int _speed;
	Size _size;
	Position _location;

	sf::Texture playerTexture;
};