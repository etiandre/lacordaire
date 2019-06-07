#pragma once
#include "SFML/Graphics.hpp"

class TextWriter {
 public:
  TextWriter(){};
  static sf::Text createText(const sf::String& string,
                             const sf::Vector2f& centerPos = sf::Vector2f(0, 0),
                             const sf::Color& color = sf::Color(255, 255, 255), int fontSize = 36);
  static void drawRainbowText(sf::Text& text, sf::RenderWindow& window);
  static void drawShadowedText(sf::Text& text, sf::RenderWindow& window);
};