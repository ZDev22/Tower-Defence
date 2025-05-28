#ifndef PATH_HPP
#define PATH_HPP

#include <SFML/Graphics.hpp>
#include <vector>

void addThickPathLine(sf::VertexArray& array, sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color);
void addPathOutline(sf::VertexArray& array, sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color outlineColor);
sf::VertexArray drawPath(const std::vector<sf::Vector2f>& path, float x, float y, float b, sf::Color fillColor, sf::Color outlineColor);

#endif // PATH_HPP