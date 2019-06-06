#pragma once
#include "GameData.h"
#include "InputManager.hpp"
#include "State.hpp"
#include "DEFINITIONS.h"

class GameOverState : public State {
public:
	GameOverState(GameData& gameData,StateMachine& stateMachine);
	void update() override;
	void onEnter() override;
	void onExit() override;
private:
	sf::Sprite _gameOverSprite;
	InputManager _inputManager;
};