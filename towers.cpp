#include "towers.hpp"
#include "towersPlace.hpp"
#include "towerDefence.hpp"
#include "zombies.hpp"
#include "towerRange.hpp"
#include "UI.hpp"
#include <cmath>
#include <iostream>

using namespace std;

void defineTower(Tower& tower) {
    if (tower.type == "turret") {
        tower.range = 200.f;
        tower.damage = 1.f;
        tower.cooldown = 1.f;
        tower.shots = 1;
        tower.shotCooldown = 0.f;
        tower.color = sf::Color(66, 64, 64);
        tower.outlineColor = sf::Color(18, 17, 17);
        tower.outlineSize = 4.5f;
        tower.shape = { {0.f, 0.f}, {12.f, 0.f}, {12.f, -24.f}, {20.f, -24.f}, {20.f, 0.f}, {32.f, 0.f}, {32.f, 32.f}, {0.f, 32.f} };
        tower.orgin = 20;
        tower.upgradeCost = 5;
    }
    else if (tower.type == "blaster") {
        tower.range = 165.f;
        tower.damage = 2.f;
        tower.cooldown = 1.4f;
        tower.shots = 2;
        tower.shotCooldown = 0.25f;
        tower.color = sf::Color(51, 49, 49);
        tower.outlineColor = sf::Color(0, 0, 0);
        tower.outlineSize = 7.f;
        tower.shape = { {0.f, 0.f}, {10.625f, 0.f}, {10.625f, -21.25f}, {15.9375f, -21.25f}, {15.9375f, 0.f}, {26.5625f, 0.f}, {26.5625f, -21.25f}, {31.875f, -21.25f}, {31.875f, 0.f}, {42.5f, 0.f}, {42.5f, 42.5f}, {0.f, 42.5f} };
        tower.orgin = 25;
        tower.upgradeCost = 10;
    }
    else if (tower.type == "militant") {
        tower.range = 270.f;
        tower.damage = 1.5f;
        tower.cooldown = .42f;
        tower.shots = 1;
        tower.shotCooldown = 0.f;
        tower.color = sf::Color(214, 144, 51);
        tower.outlineColor = sf::Color(48, 32, 11);
        tower.outlineSize = 4.5f;
        tower.shape = { {0.f, 0.f}, {10.f, 0.f}, { 10.f, -30.f }, {20.f, -30.f}, {20.f, 0.f}, { 30.f, 0.f }, {30.f, 30.f}, {0.f, 30.f} };
        tower.orgin = 15;
        tower.upgradeCost = 35;
    }
    else if (tower.type == "sniper") {
        tower.range = 550.f;
        tower.damage = 20.f;
        tower.cooldown = 4.f;
        tower.shots = 5;
        tower.shotCooldown = 3.2f;
        tower.color = sf::Color(186, 48, 48);
        tower.outlineColor = sf::Color(46, 11, 11);
        tower.outlineSize = 3.f;
        tower.shape = { {0.f, 0.f}, {7.5f, 0.f}, { 7.5f, -40.f }, {12.5f, -40.f}, {12.5f, 0.f}, { 20.f, 0.f }, {20.f, 20.f}, {0.f, 20.f} };
        tower.orgin = 10;
        tower.upgradeCost = 40;
    }
}

void Tower::shoot(vector<Zombie>& zombies) {
    while ((currentShot == 0 && currentFrame >= cooldown) || (currentShot > 0 && currentShot < shots && currentFrame >= shotCooldown)) {

        Zombie* targetZombie = nullptr;
        Zombie* currentZombie = nullptr;
        float distanceFromRange;
        float currentDistance = 0;
        float targetDistance = 0;

        for (auto& zombie : zombies) {
            if (!zombie.isDead()) {
                distanceFromRange = abs(sqrt(pow(zombie.getPosition().x - x, 2) +
                    pow(zombie.getPosition().y - y, 2)));
                if (distanceFromRange <= range) {
                    targetZombie = &zombie;
                    targetDistance = targetZombie->getDistance();
                    if (targetDistance > currentDistance) {
                        currentDistance = targetDistance;
                        currentZombie = targetZombie;
                    }
                }
            }
        }

        // Attack the identified target
        if (currentZombie != nullptr) {
            currentZombie->health -= max(1.f, damage - currentZombie->defence);
            if (currentZombie->health <= 0) { currentZombie->kill(); coins += currentZombie->coinDrop; }

            zombieRotationX = currentZombie->getPosition().x - x;
            zombieRotationY = currentZombie->getPosition().y - y;
            angle = (atan2(zombieRotationY, zombieRotationX) * 180 / 3.14159265) + 70.f;
            rotation = angle;
        }

        currentShot++;

        if (currentShot > 1) {
            if (currentFrame >= shotCooldown) {
                currentFrame -= shotCooldown;
            }
            if (currentShot == shots) { currentShot = 0; }
        }
        else {
            if (shots == 1) { currentShot = 0; }
            currentFrame -= cooldown;
        }
    }
}

bool canUpgrade = true; // Flag to track key press state

void simulateTowers(vector<Tower>& towers, vector<Zombie>& zombies, float gameSpeed, sf::RenderWindow& window, float deltaTime) {
    sf::Event event;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);

    for (auto& tower : towers) {
        tower.currentFrame += gameSpeed * deltaTime;
        tower.shoot(zombies);
        tower.draw(tower, window, false, 0.f, 0.f);

        // Bounding box fix
        float width = (tower.shape[6].x * 2) - 25;
        float height = (tower.shape[6].y * 2) + 25;

        sf::FloatRect towerBounds(
            tower.x - tower.shape[6].x,
            tower.y - ((tower.shape[6].y * 2) + 5) / 2,
            tower.shape[6].x * 2,
            (tower.shape[6].y * 2) + 5
        );

        if (towerBounds.contains(worldMousePosition)) {
            displayRange(window, tower.range, tower.x - tower.range, tower.y - tower.range);
            renderUpgrade(window, tower.upgradeCost);

            // Detect key hit instead of continuous press
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                if (canUpgrade) {
                    if (coins >= tower.upgradeCost) {
                        coins -= tower.upgradeCost;
                        tower.upgradeCost = std::ceil(tower.upgradeCost * 1.13f);
                        tower.damage *= 1.1f;
                        tower.range *= 1.075f;
                        tower.cooldown /= .988f;
                        tower.shotCooldown /= .988f;
                    }
                    canUpgrade = false;
                }
            }
            else {
                canUpgrade = true;
            }
        }
    }
}


void Tower::draw(Tower& tower, sf::RenderWindow& window, bool useCords, float xCord, float yCord) {
    sf::ConvexShape towerShape;
    towerShape.setPointCount(tower.shape.size());
    if (useCords) { towerShape.setPosition(xCord, yCord); }
    else { towerShape.setPosition(x, y); }
    towerShape.setRotation(tower.rotation);
    towerShape.setOrigin(tower.orgin, tower.orgin);
    towerShape.setFillColor(tower.color);
    towerShape.setOutlineColor(tower.outlineColor);
    towerShape.setOutlineThickness(tower.outlineSize);
    for (size_t i = 0; i < tower.shape.size(); ++i) {
        towerShape.setPoint(i, tower.shape[i]);
    }
    window.draw(towerShape);
}