#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Travelaws.h"


class MainMenuState : public State
{
public:
	MainMenuState(GameDataRef data);

	void init();

	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	GameDataRef _data;

	sf::Sprite _background;
	sf::Sprite _title;
	sf::Sprite _playButton;
};
