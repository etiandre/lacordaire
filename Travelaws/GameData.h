#pragma once
#include <tmxlite/Map.hpp>
#include "Player.h"

struct GameData {
  Player player;
  tmx::Map map;
};
