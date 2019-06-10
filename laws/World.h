#pragma once
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include "SFMLOrthogonalLayer.hpp"

/*
Classe décrivant le monde et s'occupant de charger et afficher les niveaux
*/
class World {
 public:
  World();
  void draw(sf::RenderWindow& window);

  // charge le niveau n°i, plante lamentablement s'il n'est pas trouvé
  void loadLevel(int levelID);

  // renvoie une référence vers l'objet map
  tmx::Map& getMap();
  // renvoie la taille de la carte en pixels
  sf::Vector2i getSize();

  // renvoie le layer où les infos de collision sont présentes
  std::unique_ptr<MapLayer>& getCollisionLayer();

  // rectangle décrivant la zone de spawn du joueur
  sf::FloatRect playerSpawn;
  // rectangle décrivant la zone de win du joueur
  sf::FloatRect goal;

 private:
  tmx::Map _map;
  std::vector<std::unique_ptr<MapLayer>> _layers;
  std::vector<tmx::Object> _objects;
  sf::FloatRect _getObjectRect(const char* name);
};