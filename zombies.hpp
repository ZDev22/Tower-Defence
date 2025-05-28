#ifndef ZOMBIES_HPP
#define ZOMBIES_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;

extern int zombieID;  // Declare zombieID as an extern variable

class Zombie {
private:
    sf::CircleShape shape;
    std::vector<sf::Vector2f> path;
    size_t currentTargetIndex;
    float speed;
    int personalID;
    bool dead;
    float distance;

public:
    float size;
    float health;
    float maxHealth;
    float defence;
    short coinDrop;
    short damage;
    string zombieType;  // Change to zombieType to avoid confusion with zombieID

    Zombie(const std::string& id, const std::vector<sf::Vector2f>& path, int personalID);

    sf::Vector2f getPosition() const;
    void draw(sf::RenderWindow& window);
    void move(float deltaTime);
    std::string getId() const;
    int getPersonalID() const;
    float getSpeed() const;
    bool isDead() const;
    void kill();
    float getDistance() const;
    vector<sf::Vector2f> getZombiePosition();
};

Zombie spawnZombie(const string& id, const vector<sf::Vector2f>& path);
void spawnZombies(vector<Zombie>& zombies, const string& id, const vector<sf::Vector2f>& path, size_t count, int sleep);

#endif  // ZOMBIES_HPP