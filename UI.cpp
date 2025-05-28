#include "UI.hpp"
#include "font.hpp"
#include "towers.hpp"
#include "towerDefence.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>

void renderUI(sf::RenderWindow& window) {
    sf::RectangleShape squareUI;
    squareUI.setSize({ 60.f, 60.f });
    squareUI.setFillColor(sf::Color(255, 255, 255, 155));
    squareUI.setOutlineColor(sf::Color(0, 0, 0));
    squareUI.setOutlineThickness(8);

    // Create a Tower object for each type
    Tower turret;
    turret.type = "turret";
    defineTower(turret);

    Tower blaster;
    blaster.type = "blaster";
    defineTower(blaster);

    Tower militant;
    militant.type = "militant";
    defineTower(militant);

    Tower sniper;
    sniper.type = "sniper";
    defineTower(sniper);

    squareUI.setPosition({ 100.f, 610.f });
    window.draw(squareUI);
    turret.draw(turret, window, true, 120.f, 640.f);
    renderText(window, "1", 150.f, 615.f, sf::Color(219, 172, 112), sf::Color(54, 42, 27));
    renderText(window, "$50", 100.f, 640.f, sf::Color(32, 150, 24), sf::Color(9, 38, 7));

    squareUI.setPosition({ 200.f, 610.f });
    window.draw(squareUI);
    blaster.draw(blaster, window, true, 220.f, 640.f);
    renderText(window, "2", 240.f, 615.f, sf::Color(219, 172, 112), sf::Color(54, 42, 27));
    renderText(window, "$100", 190.f, 640.f, sf::Color(32, 150, 24), sf::Color(9, 38, 7));

    squareUI.setPosition({ 300.f, 610.f });
    window.draw(squareUI);
    militant.draw(militant, window, true, 320.f, 640.f);
    renderText(window, "3", 340.f, 615.f, sf::Color(219, 172, 112), sf::Color(54, 42, 27));
    renderText(window, "$350", 290.f, 640.f, sf::Color(32, 150, 24), sf::Color(9, 38, 7));

    squareUI.setPosition({ 400.f, 610.f });
    window.draw(squareUI);
    sniper.draw(sniper, window, true, 420.f, 640.f);
    renderText(window, "4", 440.f, 615.f, sf::Color(219, 172, 112), sf::Color(54, 42, 27));
    renderText(window, "$400", 390.f, 640.f, sf::Color(32, 150, 24), sf::Color(9, 38, 7));

    squareUI.setPosition({ 550.f, 610.f });
    window.draw(squareUI);
    renderText(window, "enter", 535.f, 615.f, sf::Color(219, 172, 112), sf::Color(54, 42, 27));

    squareUI.setPosition({ 750.f, 610.f });
    window.draw(squareUI);
    renderText(window, "<>", 765.f, 615.f, sf::Color(219, 172, 112), sf::Color(54, 42, 27));
    renderText(window, "game speed", 685.f, 640.f, sf::Color(197, 209, 31), sf::Color(46, 48, 8));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {if (!keyRightPressed) {gameSpeed += 0.5f; keyRightPressed = true;}}
    else {keyRightPressed = false;}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {if (!keyLeftPressed) {gameSpeed -= 0.5f; keyLeftPressed = true;}}
    else { keyLeftPressed = false;}
    if (gameSpeed < 0.5f) gameSpeed = 5.f;
    if (gameSpeed > 5.0f) gameSpeed = .5f;

    renderText(window, "lives- " + to_string(lives), 20.f, 20.f, sf::Color(32, 150, 24), sf::Color(9, 38, 7));
    renderText(window, "coins- " + to_string(coins), 20.f, 50.f, sf::Color(32, 150, 24), sf::Color(9, 38, 7));
    renderText(window, "wave- " + to_string(wave - 1), 20.f, 80.f, sf::Color(32, 150, 24), sf::Color(9, 38, 7));
    ostringstream stream;
    stream << fixed << setprecision(1) << gameSpeed;
    renderText(window, "game speed- " + stream.str(), 20.f, 110.f, sf::Color(32, 150, 24), sf::Color(9, 38, 7));

    //renderText(window, "abcdefghijklmnopqrstuvwxyz", 20.f, 120.f, sf::Color(32, 150, 24), sf::Color(9, 38, 7));
}

void renderUpgrade(sf::RenderWindow& window, int upgradeCost) {
    renderText(window, "upgrade- e", 1000.f, 620.f, sf::Color(29, 133, 20), sf::Color(6, 33, 4));
    renderText(window, "cost- " + to_string(upgradeCost), 1000.f, 650.f, sf::Color(29, 133, 20), sf::Color(6, 33, 4));
}