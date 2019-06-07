#pragma once
#include <SFML/Graphics/Color.hpp>
#include <tuple>

class ColorUtil {
 public:
  static std::tuple<float, float, float> RGBtoHSL(const sf::Color& color);
  static std::tuple<float, float, float> RGBtoHSV(const sf::Color& color);
  static sf::Color HSLtoRGB(float H, float S, float L);
  static sf::Color HSVtoRGB(float H, float S, float V);
};