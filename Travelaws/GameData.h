#pragma once
#include <tmxlite/Map.hpp>
#include "Player.h"
#include "StateMachine.hpp"
#include "SFMLOrthogonalLayer.hpp"

struct GameData {
  Player player;
  tmx::Map map;
  State gameState;
};
