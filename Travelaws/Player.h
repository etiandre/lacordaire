#pragma once

struct Position {
	int x; int y;
};

class Player
{
public:
	Player();
	~Player();
	void setPosition(int x, int y);
	Position& getPosition();

private:
	int _health;
	int _speed;
	float _size;
	Position _location;
	
};