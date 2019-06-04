#include "pch.h"
#include "GravityRule.hpp"

void GravityRule::update(GameData& gameData) {
	gameData.player.velocity.y += gravity;
}

GravityRule::GravityRule()
{
}
