#ifndef TOWERSPLACE_HPP
#define TOWERSPLACE_HPP

#include "towers.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

void checkIfPlacing(const sf::Event& event, std::vector<Tower>& towers, sf::RenderWindow& window);
void renderTowers(std::vector<Tower>& towers, sf::RenderWindow& window);

#endif // TOWERSPLACE_HPP