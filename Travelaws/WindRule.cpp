#include "pch.h"
#include "WindRule.hpp"

void WindRule::update(GameData &gameData) {
	gameData.player.velocity.x += _windForce;
}

WindRule::WindRule()
{
}
