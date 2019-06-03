#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

struct GameData
{
	
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
public:
	Game(int width, int height, std::string title);

private:
	// Updates run at 60 per second.
	const float updt = 1.0f / 60.0f;
	sf::Clock _clock;

	GameDataRef _data = std::make_shared<GameData>();

	void run();
};