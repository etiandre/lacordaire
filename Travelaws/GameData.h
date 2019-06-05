#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "World.h"

struct GameData {
  Player player;
  World world;
  sf::RenderWindow window;
};
