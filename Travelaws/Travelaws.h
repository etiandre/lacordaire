#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

struct GameData {};

typedef std::shared_ptr<GameData> GameDataRef;

class Game {
 public:
  Game(int width, int height, std::string title);

 private:
  sf::RenderWindow window;
  sf::View view;

  tmx::Map map;

  GameDataRef _data = std::make_shared<GameData>();
  void loadLevel(int levelID);

  void mainLoop();
};