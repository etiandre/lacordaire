#pragma once
#include <tmxlite/Map.hpp>
#include <SFML/Graphics.hpp>
#include "SFMLOrthogonalLayer.hpp"

class World {
 public:
  World();
  World(int levelID);
  void draw(sf::RenderWindow &window);

	tmx::Map& getMap();
  sf::Vector2i getSize();

  std::unique_ptr<MapLayer>& getCollisionLayer();

  sf::Vector2f playerSpawn;
  sf::Vector2f goal;

  

 private:
  tmx::Map _map;
  std::vector<std::unique_ptr<MapLayer>> _layers;
  std::vector<tmx::Object> _objects;
  sf::Vector2f _getObject(const char* name);
};