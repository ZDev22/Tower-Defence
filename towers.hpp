#ifndef TOWERS_HPP
#define TOWERS_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "zombies.hpp"

struct Tower {
    std::string type;
    int x;
    int y;
    float range;
    float damage;
    float cooldown;
    short shots;
    float shotCooldown;
    float currentFrame = 0;
    short currentShot = 0;
    int upgradeCost;

	vector<sf::Vector2f> shape;

    sf::Color color;
    sf::Color outlineColor;

    float outlineSize;
    float rotation = 90.f;

    float zombieRotationX;
    float zombieRotationY;
    float angle;

    short orgin;

    void shoot(std::vector<Zombie>& zombies);
    void draw(Tower& tower, sf::RenderWindow& window, bool useCords, float xCord, float yCord);
};

void defineTower(Tower& tower);
void simulateTowers(std::vector<Tower>& towers, std::vector<Zombie>& zombies, float gameSpeed, sf::RenderWindow& window, float deltaTime);

#endif