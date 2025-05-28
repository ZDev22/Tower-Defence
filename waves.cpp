#include "waves.hpp"
#include "zombies.hpp"
#include "towerDefence.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

void delay(short delay) {
    short spawnDelay = delay / gameSpeed;
    this_thread::sleep_for(chrono::milliseconds(spawnDelay));
}

void waves(std::vector<Zombie>& zombies) {
    for (wave = 1; wave <= 11; ++wave) {
        while (true) { if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && zombieAmount == 0) { break; } }
        coins += wave * 5;
        switch (wave) {
        case 1: {
            spawnZombies(zombies, "zombie", path, 5, 1000);
            break;
        }
        case 2: {
            spawnZombies(zombies, "zombie", path, 7, 800);
            delay(2000);
            spawnZombies(zombies, "speedZombie", path, 3, 1000);
            break;
        }
        case 3: {
            thread zombie1(spawnZombies, ref(zombies), "zombie", path, 12, 500);
            zombie1.detach();
            delay(1200);
            spawnZombies(zombies, "speedZombie", path, 6, 800);
            delay(1200);
            spawnZombies(zombies, "tankZombie", path, 1, 0);
            break;
        }
        case 4: {
            thread zombie2(spawnZombies, ref(zombies), "speedZombie", path, 12, 500);
            zombie2.detach();
            delay(1000);
            thread zombie3(spawnZombies, ref(zombies), "zombie", path, 15, 400);
            zombie3.detach();
            delay(1000);
            spawnZombies(zombies, "tankZombie", path, 5, 1500);
            break;
        }
        case 5: {
            thread zombie4(spawnZombies, ref(zombies), "tankZombie", path, 10, 1000);
            zombie4.detach();
            spawnZombies(zombies, "mutantZombie", path, 5, 1500);
            spawnZombies(zombies, "mutantSpeedZombie", path, 5, 1500);
            break;
        }
        case 6: {
            thread zombie5(spawnZombies, ref(zombies), "mutantSpeedZombie", path, 10, 1000);
            zombie5.detach();
            delay(500);
            spawnZombies(zombies, "mutantZombie", path, 10, 400);
            spawnZombies(zombies, "mutantSpeedZombie", path, 10, 500);
            delay(1500);
            spawnZombies(zombies, "mutantTankZombie", path, 1, 0);
            break;
        }
        case 7: {
            thread zombie6(spawnZombies, ref(zombies), "mutantTankZombie", path, 5, 4000);
            zombie6.detach();
            spawnZombies(zombies, "mutantSpeedZombie", path, 20, 250);
            spawnZombies(zombies, "mutantZombie", path, 15, 250);
            delay(2000);
            spawnZombies(zombies, "dartZombie", path, 5, 1000);
            break;
        }
        case 8: {
            thread zombie7(spawnZombies, ref(zombies), "dartZombie", path, 20, 1200);
            zombie7.detach();
            delay(1000);
            thread zombie8(spawnZombies, ref(zombies), "mutantTankZombie", path, 10, 2245);
            zombie8.detach();
            spawnZombies(zombies, "minibossZombie", path, 2, 6000);
            spawnZombies(zombies, "steelZombie", path, 5, 2300);
            break;
        }
        case 9: {
            thread zombie9(spawnZombies, ref(zombies), "dartZombie", path, 40, 500);
            zombie9.detach();
            delay(500);
            thread zombie10(spawnZombies, ref(zombies), "minibossZombie", path, 5, 5000);
            zombie10.detach();
            delay(500);
            spawnZombies(zombies, "steelZombie", path, 10, 2500);
            delay(4500);
            spawnZombies(zombies, "tankBossZombie", path, 1, 0);
            break;
        }
        case 10: {
            thread zombie11(spawnZombies, ref(zombies), "dartZombie", path, 70, 200);
            zombie11.detach();
            spawnZombies(zombies, "minibossZombie", path, 10, 1800);
            delay(2000);
            spawnZombies(zombies, "tankBossZombie", path, 3, 5000);
            spawnZombies(zombies, "speedBossZombie", path, 3, 6000);
            break;
        }
        case 11: {
            thread zombie12(spawnZombies, ref(zombies), "dartZombie", path, 170, 190);
            zombie12.detach();
            delay(32000);
            spawnZombies(zombies, "bossZombie", path, 1, 0);
        }
        }
    }
}