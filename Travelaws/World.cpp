#include "World.h"
#include "DEFINITIONS.h"


World::World() {}

void World::draw(sf::RenderWindow& window) {
  for (auto& layer : _layers) {
    window.draw(*layer.get());
  }
}

void World::loadLevel(int levelID) {
  if (!_map.load("assets/levels/level" + std::to_string(levelID) + ".tmx")) {
    std::cout << "cannot load level !" << std::endl;
    exit(1);
  }

  int i = 0;
  for (const auto& layer : _map.getLayers()) {
    if (layer.get()->getType() == tmx::Layer::Type::Object) {
      _objects = layer.get()->getLayerAs<tmx::ObjectGroup>().getObjects();
    } else if (layer.get()->getType() == tmx::Layer::Type::Tile) {
      _layers.push_back(std::make_unique<MapLayer>(_map, i));
    } else {
      std::cout << "Unexpected layer type :(" << std::endl;
      exit(1);
    }
    i++;
  }

  playerSpawn = _getObjectRect("playerSpawn");
  goal = _getObjectRect("goal");
}

tmx::Map& World::getMap() { return _map; }

sf::Vector2i World::getSize() {
  return sf::Vector2i(_map.getTileSize().x * _map.getTileCount().x,
                      _map.getTileSize().y * _map.getTileCount().y);
}

std::unique_ptr<MapLayer>& World::getCollisionLayer() {
  return _layers.back();  // on part du principe que le dernier layer est celui
                          // des plateformes
}

sf::FloatRect World::_getObjectRect(const char* name) {
  for (const auto& object : _objects) {
    if (object.getName() == name) {
      auto& rect = object.getAABB();
      return sf::FloatRect(rect.left, rect.top, rect.width, rect.height);
    }
  }
  std::cout << "WARNING : did not find " << name << std::endl;
  return sf::FloatRect();
}