#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Rule.h"
#include "World.h"

class Rule;

/*
La struct GameData contient toutes les infos du jeu.
Un objet GameData est créé par Game, et un seul doit exister.
L'état des objets contenus doit être valide à tout moment.
*/
struct GameData {
  Player player;
  World world;
  sf::RenderWindow window;
  sf::Time time;
  int currentLevel;
  std::vector<std::unique_ptr<Rule>> rules;
};
