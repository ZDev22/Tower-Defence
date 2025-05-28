#include "towersPlace.hpp"
#include "towers.hpp"
#include "towerDefence.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

bool isPositionOccupied(const std::vector<Tower>& towers, float x, float y, const std::vector<sf::Vector2f>& shape) {
    for (const auto& tower : towers) {
        sf::FloatRect existingTowerBounds(
            tower.x - tower.shape[6].x,
            tower.y - ((tower.shape[6].y * 2) + 5) / 2,
            tower.shape[6].x * 2,
            (tower.shape[6].y * 2) + 5
        );

        sf::FloatRect newTowerBounds(
            x - shape[6].x,
            y - ((shape[6].y * 2) + 5) / 2,
            shape[6].x * 2,
            (shape[6].y * 2) + 5
        );

        if (existingTowerBounds.intersects(newTowerBounds)) {
            return true;
        }
    }
    return false;
}

void checkIfPlacing(const sf::Event& event, std::vector<Tower>& towers, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        Tower newTower;
        short spent;
        switch (event.key.code) {
        case sf::Keyboard::Num1: newTower.type = "turret"; spent = 50; break;
        case sf::Keyboard::Num2: newTower.type = "blaster"; spent = 100; break;
        case sf::Keyboard::Num3: newTower.type = "militant"; spent = 350; break;
        case sf::Keyboard::Num4: newTower.type = "sniper"; spent = 400; break;
        default: return;
        }

        if (coins >= spent) {
            // Correct mouse positioning for full-screen mode
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            newTower.x = mousePos.x;
            newTower.y = mousePos.y;

            defineTower(newTower);

            // Check if the position is occupied
            if (!isPositionOccupied(towers, newTower.x, newTower.y, newTower.shape)) {
                towers.push_back(newTower);
                coins -= spent;
            }
        }
    }
}

void renderTowers(std::vector<Tower>& towers, sf::RenderWindow& window) {
    for (auto& tower : towers) {
        tower.draw(tower, window, false, 0.f, 0.f);
    }
}