#include "zombies.hpp"
#include "towerDefence.hpp"
#include <cmath>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

extern int zombieID;  // Declare as extern
extern int zombieAmount;
extern std::vector<float> health;  // Ensure the type matches the declaration in towerDefence.hpp
extern std::vector<float> distances;
extern std::mutex zombiesMutex;  // Declare as extern

Zombie::Zombie(const std::string& id, const std::vector<sf::Vector2f>& path, int personalID)
    : path(path), currentTargetIndex(0), personalID(personalID), dead(false), distance(0.f) {

    if (id == "zombie") {
        size = 40.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(9, 156, 22));
        shape.setOutlineColor(sf::Color(0, 38, 3));
        shape.setOutlineThickness(2);

        health = 2.f;
        defence = 0;
        speed = 1.f;
        coinDrop = 1;
        damage = 1;
    }
    else if (id == "speedZombie") {
        size = 24.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(41, 190, 217));
        shape.setOutlineColor(sf::Color(1, 35, 41));
        shape.setOutlineThickness(1.2f);

        health = 1.f;
        defence = 0;
        speed = 1.5f;
        coinDrop = 2;
        damage = 1;
    }
    else if (id == "tankZombie") {
        size = 60.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(87, 87, 87));
        shape.setOutlineColor(sf::Color(20, 20, 20));
        shape.setOutlineThickness(3);

        health = 15.f;
        defence = 1;
        speed = 0.6f;
        coinDrop = 12;
        damage = 5;
    }
    else if (id == "mutantZombie") {
        size = 45.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(7, 82, 14));
        shape.setOutlineColor(sf::Color(2, 20, 4));
        shape.setOutlineThickness(3.2f);

        health = 7.5f;
        defence = 1;
        speed = 1.f;
        coinDrop = 7;
        damage = 5;
    }
    else if (id == "mutantSpeedZombie") {
        size = 33.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(21, 96, 110));
        shape.setOutlineColor(sf::Color(5, 29, 33));
        shape.setOutlineThickness(2.f);

        health = 5.5f;
        defence = 1;
        speed = 2.f;
        coinDrop = 8;
        damage = 5;
    }
    else if (id == "dartZombie") {
        size = 15.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(210, 217, 26));
        shape.setOutlineColor(sf::Color(67, 69, 11));
        shape.setOutlineThickness(1.f);

        health = 12.5f;
        defence = 1;
        speed = 3.f;
        coinDrop = 9;
        damage = 7;
    }
    else if (id == "mutantTankZombie") {
        size = 80.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(38, 38, 38));
        shape.setOutlineColor(sf::Color(0, 0, 0));
        shape.setOutlineThickness(4.1f);

        health = 100.f;
        defence = 2;
        speed = 0.4f;
        coinDrop = 25;
        damage = 12;
    }
    else if (id == "minibossZombie") {
        size = 85.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(22, 125, 9));
        shape.setOutlineColor(sf::Color(8, 46, 4));
        shape.setOutlineThickness(4.5f);

        health = 140.f;
        defence = 1.3f;
        speed = 0.8f;
        coinDrop = 50;
        damage = 20;
    }
    else if (id == "steelZombie") {
        size = 50.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(186, 186, 186));
        shape.setOutlineColor(sf::Color(84, 83, 83));
        shape.setOutlineThickness(4.f);

        health = 75.5f;
        defence = 1.6f;
        speed = 1.f;
        coinDrop = 40;
        damage = 18;
    }
    else if (id == "tankBossZombie") {
        size = 100.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(0, 0, 0));
        shape.setOutlineColor(sf::Color(54, 0, 0));
        shape.setOutlineThickness(6.f);

        health = 500.f;
        defence = 2.5f;
        speed = 0.5f;
        coinDrop = 60;
        damage = 35;
    }
    else if (id == "speedBossZombie") {
        size = 100.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(20, 50, 168));
        shape.setOutlineColor(sf::Color(6, 17, 59));
        shape.setOutlineThickness(6.f);

        health = 300.f;
        defence = 1.2f;
        speed = 1.5f;
        coinDrop = 67;
        damage = 37;
    }
    else if (id == "bossZombie") {
        size = 200.f;
        shape.setRadius(size / 2);
        shape.setFillColor(sf::Color(28, 156, 49));
        shape.setOutlineColor(sf::Color(10, 54, 17));
        shape.setOutlineThickness(12.f);

        health = 2450.5f;
        defence = 1.8f;
        speed = 0.65f;
        coinDrop = 300;
        damage = 100;
    }
    zombieType = id;
    maxHealth = health;
    shape.setPosition(path[0].x - size / 2, path[0].y - size / 2);
    speed *= 50.f;
}

sf::Vector2f Zombie::getPosition() const {
    return shape.getPosition();
}

void Zombie::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Zombie::move(float deltaTime) {

    sf::Vector2f currentPosition = shape.getPosition() + sf::Vector2f(size / 2, size / 2);
    sf::Vector2f targetPosition = path[currentTargetIndex];
    sf::Vector2f direction = targetPosition - currentPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
    }
    shape.move(direction * speed * deltaTime * gameSpeed);

    if (shape.getPosition().x > 1280) {kill();}
    else {
        if (length < speed * deltaTime * gameSpeed) {currentTargetIndex++;}
        distance += speed * deltaTime * gameSpeed;
    }
}

std::string Zombie::getId() const {
    return zombieType;
}

int Zombie::getPersonalID() const {
    return personalID;
}

float Zombie::getSpeed() const {
    return speed;
}

bool Zombie::isDead() const {
    return dead;
}

void Zombie::kill() {
    zombieAmount--;
    dead = true;
    if (shape.getPosition().x > 1280) { lives -= damage; }
    else {coins += coinDrop;}
}

float Zombie::getDistance() const {
    return distance;
}

vector<sf::Vector2f> Zombie::getZombiePosition() {
    return { getPosition() };
}

Zombie spawnZombie(const std::string& id, const std::vector<sf::Vector2f>& path) {
    zombieID++;
    zombieAmount++;
    Zombie newZombie(id, path, zombieID);
    health.push_back(static_cast<float>(newZombie.health));  // Ensure the type matches
    return newZombie;
}

void spawnZombies(std::vector<Zombie>& zombies, const std::string& id, const std::vector<sf::Vector2f>& path, size_t count, int sleep) {
    for (size_t i = 0; i < count; ++i) {
        {
            std::lock_guard<std::mutex> lock(zombiesMutex);
            zombies.push_back(spawnZombie(id, path));
            if (zombieID >= distances.size()) {
                distances.push_back(0);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleep / gameSpeed)));
    }
}