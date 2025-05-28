#include "healthBar.hpp"
#include "SFML/Graphics.hpp"
#include "zombies.hpp"

void drawHealthBar(Zombie& zombie, sf::RenderWindow& window) {
    float healthRatio = static_cast<float>(zombie.health) / zombie.maxHealth;
    float healthBarWidth = max(1.f, healthRatio * 45);

    vector<sf::Vector2f> healthBarPoints = {
        {0, 0},
        {0, -8},
        {healthBarWidth, -8},
        {healthBarWidth, 0}
    };

    sf::ConvexShape healthBar;
    healthBar.setPointCount(healthBarPoints.size());

    for (size_t a = 0; a < healthBarPoints.size(); ++a) {
        healthBar.setPoint(a, healthBarPoints[a]);
    }

    healthBar.setFillColor(sf::Color::Red);
    healthBar.setOutlineColor(sf::Color::Black);
    healthBar.setOutlineThickness(2.f);

    healthBar.setPosition(zombie.getPosition().x, zombie.getPosition().y - (zombie.size / 2) + 5.f);

    window.draw(healthBar);
}