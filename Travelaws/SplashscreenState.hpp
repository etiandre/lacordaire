#pragma once
#include "GameData.h"
#include "InputManager.hpp"
#include "State.hpp"
#include "DEFINITIONS.h"

class SplashscreenState : public State {
public:
	SplashscreenState(GameData& gameData, StateMachine& stateMachine);
	void processEvent(sf::Event& event) override;
	void update() override;
	void onEnter() override;
private:
	sf::Sprite _splashscreenSprite;
	InputManager _inputManager;
};