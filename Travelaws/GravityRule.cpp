#include "pch.h"
#include "GravityRule.hpp"

void GravityRule::update(GameData& gameData) {
	gameData.player.accelerate(0, gravity);
}
