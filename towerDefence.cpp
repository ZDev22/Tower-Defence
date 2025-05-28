#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
#include <mutex>
#include "zombies.hpp"
#include "waves.hpp"
#include "path.hpp"
#include "towers.hpp"
#include "towersPlace.hpp"
#include "healthBar.hpp"
#include "towerDefence.hpp"
#include "UI.hpp"
#include "screens.hpp"

using namespace std;

short wave;
int coins = 100;
short lives = 100;
int zombieID = 0;
int zombieAmount = 0;
bool deleted = false;
float gameSpeed = 1.0f;
float deltaTime;
bool windowFocused;
bool keyRightPressed = false;
bool keyLeftPressed = false;

vector<sf::Vector2f> path = { {0.f, 580.f}, {500.f, 580.f}, {500.f, 200.f}, {800.f, 200.f}, {800.f, 500.f}, {1500.f, 500.f} };
vector<Zombie> zombies;
vector<float> distances;
vector<float> health;
vector<float> defense;
vector<Tower> towers;

std::mutex zombiesMutex;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 680), "Tower Defence");
    window.setVerticalSyncEnabled(true);

    thread wavesThread(waves, ref(zombies));
    wavesThread.detach();

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        windowFocused = true;  // Track focus state

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::LostFocus)
                windowFocused = false;

            if (event.type == sf::Event::GainedFocus)
                windowFocused = true;

            if (windowFocused) {
                checkIfPlacing(event, towers, window);
            }
        }

        deltaTime = clock.restart().asSeconds() * gameSpeed;

        window.clear(sf::Color(21, 87, 4));
        window.draw(drawPath(path, 0, 0, 0, sf::Color(112, 70, 8), sf::Color(43, 27, 4)));

        simulateTowers(towers, zombies, gameSpeed, window, deltaTime);

        lock_guard<mutex> lock(zombiesMutex);
        for (auto& zombie : zombies) {
            if (!zombie.isDead()) {
                zombie.move(deltaTime);

                if (!zombie.isDead()) {
                    zombie.draw(window);
                    if (zombie.health != zombie.maxHealth) { drawHealthBar(zombie, window); }
                }
            }
        }
        renderUI(window);
        renderScreen(window);
        window.display();
    }
    return 0;
}