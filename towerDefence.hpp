#ifndef TOWERDEFENCE_HPP
#define TOWERDEFENCE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <mutex>

extern std::vector<sf::Vector2f> path;
extern int zombieAmount;
extern std::vector<float> distances;
extern std::vector<float> health;
extern int zombieID;
extern std::mutex zombiesMutex;

extern float gameSpeed;
extern short wave;
extern short lives;
extern int coins;
extern bool keyRightPressed;
extern bool keyLeftPressed;

#endif