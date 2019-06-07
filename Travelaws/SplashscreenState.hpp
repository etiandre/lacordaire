#pragma once
#include "GameData.h"
#include "State.hpp"
#include "DEFINITIONS.h"

class SplashscreenState : public State {
public:
	SplashscreenState(GameData& gameData, StateMachine& stateMachine);
	void processEvent(sf::Event& event) override;
	void update(sf::Time dt) override;
	void onEnter() override;
private:
	sf::Sprite _splashscreenSprite;
	sf::Text _titleText;
};