#pragma once
#include "Rule.h"

class WindRule : public Rule {

public:
	void update(GameData &gameData);
	WindRule();
private:
	int _windForce = 0;
};
