#pragma once
#include "Rule.h"

class WindRule : public Rule {

public:
	void update(GameData &gameData);

private:
	int _windForce = 2;
};
