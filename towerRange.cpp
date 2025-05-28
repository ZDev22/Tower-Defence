#include "towerRange.hpp"

void displayRange(sf::RenderWindow& window, float radius, short x, short y) {
	sf::CircleShape range;
	range.setRadius(radius);
	range.setPosition(x, y);
	range.setFillColor(sf::Color(255, 255, 255, 100));
	range.setOutlineColor(sf::Color(0, 0, 0, 200));
	range.setOutlineThickness(radius / 20);
	window.draw(range);
}