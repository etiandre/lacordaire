#include "TextWriter.h"
#include <iostream>
#include "ColorUtil.h"
#include "DEFINITIONS.h"
#include "FontManager.hpp"

sf::Text TextWriter::createText(const sf::String& string,
                                const sf::Vector2f& centerPos,
                                const sf::Color& color) {
  sf::Text text;

  sf::Font* fontPtr = FontManager::loadFont("font", "assets/font.ttf");
  if (!fontPtr) {
    std::cout << "erreur chargement assets/font.ttf !" << std::endl;
    exit(-1);
  }

  text.setFont(*fontPtr);
  text.setString(string);
  text.setCharacterSize(36);
  text.setFillColor(color);
  const auto bounds = text.getLocalBounds();
  text.setOrigin(bounds.left + bounds.width / 2,
                 bounds.top + bounds.height / 2);
  text.setPosition(centerPos);
  return text;
}

void TextWriter::drawRainbowText(sf::Text& text, sf::RenderWindow& window) {
  auto hsv = ColorUtil::RGBtoHSV(text.getFillColor());
  auto h = std::get<0>(hsv);
  auto s = std::get<1>(hsv);
  auto v = std::get<2>(hsv);
  sf::FloatRect box = text.getGlobalBounds();
  int i = 0;
  while (box.intersects(sf::FloatRect(0, 0, SCREEN_WIDTH / SCALE_FACTOR,
                                      SCREEN_HEIGHT / SCALE_FACTOR))) {
    sf::Text shadow = text;
    shadow.move(5 * i, 5 * i);
    box = shadow.getGlobalBounds();
    h += 10;
    shadow.setFillColor(ColorUtil::HSVtoRGB(h, s, v));
    window.draw(shadow);
    i++;
  }
  window.draw(text);
}

void TextWriter::drawShadowedText(sf::Text& text, sf::RenderWindow& window) {
  auto hsl = ColorUtil::RGBtoHSL(text.getFillColor());
  auto h = std::get<0>(hsl);
  auto s = std::get<1>(hsl);
  auto l = std::get<2>(hsl);
  sf::Text shadow = text;
  shadow.move(5, 5);
  l -= 0.2;
  s -= 0.2;
  shadow.setFillColor(ColorUtil::HSLtoRGB(h, s, l));
  window.draw(shadow);
  window.draw(text);
}