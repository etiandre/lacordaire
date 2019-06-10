#pragma once
#include "GameData.h"

struct GameData;

/*
Classe abstraite implémentant le concept de règle.
Une classe enfant doit implémenter getName() et getScore(), et devrait
implémenter au moins update() pour être utile
*/

class Rule {
 public:
  // doit mettre à jour les éléments de jeu
  // est appelé après la mise à jour du joueur et du monde
  virtual void update(GameData& gameData, sf::Time dt){};
  // doit renvoyer le nom de la rèlge
  virtual const char* getName() = 0;
  // doit dessiner les éléments de jeu
  virtual void draw(sf::RenderWindow& window){};
  // doit renvoyer la valeur en score de la règle
  virtual int getScore() = 0;
  // indique si la règle est active ou non
  // si elle ne l'est pas, update() et draw() ne devraient jamais être appelés
  bool active = true;
};