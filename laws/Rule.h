#pragma once
#include "GameData.h"

struct GameData;

/*
Classe abstraite impl�mentant le concept de r�gle.
Une classe enfant doit impl�menter getName() et getScore(), et devrait
impl�menter au moins update() pour �tre utile
*/

class Rule {
 public:
  // doit mettre � jour les �l�ments de jeu
  // est appel� apr�s la mise � jour du joueur et du monde
  virtual void update(GameData& gameData, sf::Time dt){};
  // doit renvoyer le nom de la r�lge
  virtual const char* getName() = 0;
  // doit dessiner les �l�ments de jeu
  virtual void draw(sf::RenderWindow& window){};
  // doit renvoyer la valeur en score de la r�gle
  virtual int getScore() = 0;
  // indique si la r�gle est active ou non
  // si elle ne l'est pas, update() et draw() ne devraient jamais �tre appel�s
  bool active = true;
};