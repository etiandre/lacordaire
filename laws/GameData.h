#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "World.h"
#include "Rule.h"

class Rule;

struct GameData {
  Player player;
  World world;
  sf::RenderWindow window;
  sf::Time time;
  int currentLevel;
  std::vector<std::unique_ptr<Rule>> rules;
};
