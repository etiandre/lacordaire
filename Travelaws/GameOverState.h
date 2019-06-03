#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Travelaws.h"

class GameOverState : public State
{
public:
	GameOverState(GameDataRef data);

	void init();

	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	GameDataRef _data;

	sf::Sprite _background;
};
