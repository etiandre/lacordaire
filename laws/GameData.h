#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Rule.h"
#include "World.h"

class Rule;

/*
La struct GameData contient toutes les infos du jeu.
Un objet GameData est cr�� par Game, et un seul doit exister.
L'�tat des objets contenus doit �tre valide � tout moment.
*/
struct GameData {
  Player player;
  World world;
  sf::RenderWindow window;
  sf::Time time;
  int currentLevel;
  std::vector<std::unique_ptr<Rule>> rules;
};
