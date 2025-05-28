#ifndef FONT_HPP
#define FONT_HPP

#include <SFML/Graphics.hpp>
#include <string>

void addThickLine(sf::VertexArray& array, sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color);
void renderText(sf::RenderWindow& window, const std::string& text, float x, float y, sf::Color fillColor, sf::Color outlineColor);

#endif