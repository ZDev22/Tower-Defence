#include "screens.hpp"
#include "towerDefence.hpp"
#include "font.hpp"
#include <vector>

void renderScreen(sf::RenderWindow& window) {
	if (lives <= 0) {
		sf::RectangleShape overlay;
		overlay.setSize(sf::Vector2f(10000.f, 10000.f));
		overlay.setFillColor(sf::Color(0, 0, 0, 200));
		window.draw(overlay);
		renderText(window, "you lose", 650, 480, sf::Color(189, 23, 34), sf::Color(69, 5, 9));
	}
	else if (zombieAmount == 0 && wave == 12) {
		sf::RectangleShape overlay;
		overlay.setSize(sf::Vector2f(10000.f, 10000.f));
		overlay.setFillColor(sf::Color(0, 0, 0, 200));
		window.draw(overlay);
		renderText(window, "you win", 650, 480, sf::Color(25, 212, 53), sf::Color(11, 66, 19));
	}
}