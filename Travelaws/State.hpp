#pragma once
#include "GameData.h"

class State {
public:
	State(GameData& gameData);
	virtual void update() = 0;
	virtual void onEnter();
	virtual void onExit();
protected:
	GameData& _gameData;
};