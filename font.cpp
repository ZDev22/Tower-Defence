#include "font.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

void addThickLine(sf::VertexArray& array, sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color) {
    sf::Vector2f direction = end - start;
    sf::Vector2f perpendicular(-direction.y, direction.x);

    float length = std::sqrt(perpendicular.x * perpendicular.x + perpendicular.y * perpendicular.y);
    perpendicular /= length;
    perpendicular *= thickness / 2;

    array.append(sf::Vertex(start + perpendicular, color));
    array.append(sf::Vertex(start - perpendicular, color));
    array.append(sf::Vertex(end - perpendicular, color));
    array.append(sf::Vertex(end + perpendicular, color));
}

void addOutline(sf::VertexArray& array, sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color outlineColor) {
    sf::Vector2f direction = end - start;
    sf::Vector2f perpendicular(-direction.y, direction.x);

    float length = std::sqrt(perpendicular.x * perpendicular.x + perpendicular.y * perpendicular.y);
    perpendicular /= length;
    perpendicular *= (thickness + 2.0f) / 2; // Slightly larger for outline

    array.append(sf::Vertex(start + perpendicular, outlineColor));
    array.append(sf::Vertex(start - perpendicular, outlineColor));
    array.append(sf::Vertex(end - perpendicular, outlineColor));
    array.append(sf::Vertex(end + perpendicular, outlineColor));
}

void renderText(sf::RenderWindow& window, const std::string& text, float x, float y, sf::Color fillColor, sf::Color outlineColor) {
    sf::VertexArray textObject(sf::Quads);  // Using Quads for thicker lines
    std::vector<sf::Vector2<short>> textPoints;

    for (size_t b = 0; b < text.size(); ++b) {
        textPoints.clear();

        if (text[b] == 'a') {
            textPoints = { {0, 0}, {0, 20}, {15, 20}, {10, 20}, {10, 0}, {0, 0} };
        }
        else if (text[b] == 'b') {
            textPoints = { {0, 0}, {0, 20}, {10, 20}, {10, 10}, {0, 10} };
        }
        else if (text[b] == 'c') {
            textPoints = { {10, 0}, {0, 0}, {0, 20}, {10, 20} };
        }
        else if (text[b] == 'd') {
            textPoints = { {10, 0}, {10, 20}, {0, 20}, {0, 10}, {10, 10} };
        }
        else if (text[b] == 'e') {
            textPoints = { {0, 10}, { 0, 0 }, {10, 0}, {10, 10}, {0, 10}, {0, 20}, {10, 20} };
        }
        else if (text[b] == 'f') {
            textPoints = { {10, 0}, {0, 0}, {0, 20}, {0, 10}, {-5, 10}, {5, 10} };
        }
        else if (text[b] == 'g') {
            textPoints = { {10, 10}, {0, 10}, {0, 0}, {10, 0}, {10, 20}, {0, 20} };
        }
        else if (text[b] == 'h') {
            textPoints = { {0, 0}, {0, 20}, {0, 10}, {10, 10}, {10, 20} };
        }
        else if (text[b] == 'i') {
            textPoints = { {5, 0}, {5, 20} };
        }
        else if (text[b] == 'j') {
            textPoints = { {5, 5}, {5, 20}, {0, 20} };
        }
        else if (text[b] == 'k') {
            textPoints = { {0, 0}, {0, 20}, {0, 10}, {10, 0}, {0, 10}, {10, 20} };
        }
        else if (text[b] == 'l') {
            textPoints = { {0, 0}, {0, 20}, {10, 20} };
        }
        else if (text[b] == 'm') {
            textPoints = { {0, 20}, {0, 0}, {10, 0}, {10, 20}, {10, 0}, {20, 0}, {20, 20} };
        }
        else if (text[b] == 'n') {
            textPoints = { {0, 20}, {0, 0}, {10, 0}, {10, 20} };
        }
        else if (text[b] == 'o') {
            textPoints = { {0, 0}, {10, 0}, {10, 20}, {0, 20}, {0, 0} };
        }
        else if (text[b] == 'p') {
            textPoints = { {0, 0}, {0, 20}, {0, 10}, {10, 10}, {10, 0}, {0, 0} };
        }
        else if (text[b] == 'q') {
            textPoints = { {10, 20}, {10, 0}, {0, 0}, {0, 10}, {10, 10} };
        }
        else if (text[b] == 'r') {
            textPoints = { {0, 20}, {0, 0}, {10, 0} };
        }
        else if (text[b] == 's') {
            textPoints = { {10, 0}, {0, 0}, {0, 10}, {10, 10}, {10, 20}, {0, 20} };
        }
        else if (text[b] == 't') {
            textPoints = { {10, 20}, {0, 20}, {0, 0}, {0, 10}, {-5, 10}, {5, 10} };
        }
        else if (text[b] == 'u') {
            textPoints = { {0, 0}, {0, 20}, {10, 20}, {10, 0} };
        }
        else if (text[b] == 'v') {
            textPoints = { {0, 0}, {5, 20}, {10, 0} };
        }
        else if (text[b] == 'w') {
            textPoints = { {0, 0}, {5, 20}, {10, 0}, {15, 20}, {20, 0} };
        }
        else if (text[b] == 'x') {
            textPoints = { {0, 0}, {10, 20}, {5, 10}, {0, 20}, {10, 0} };
        }
        else if (text[b] == 'y') {
            textPoints = { {0, 0}, {5, 8}, {10, 0}, {0, 20} };
        }
        else if (text[b] == 'z') {
            textPoints = { {0, 0}, {10, 0}, {0, 20}, {10, 20} };
        }
        else if (text[b] == '1') {
            textPoints = { {0, 5}, {5, 0}, {5, 20} };
        }
        else if (text[b] == '2') {
            textPoints = { {0, 0}, {10, 0}, {10, 10}, {0, 10}, {0, 20}, {10, 20} };
        }
        else if (text[b] == '3') {
            textPoints = { {0, 0}, {10, 0}, {10, 10}, {0, 10}, {10, 10}, {10, 20}, {0, 20} };
        }
        else if (text[b] == '4') {
            textPoints = { {0, 0}, {0, 10}, {15, 10}, {10, 10}, {10, 0}, {10, 20} };
        }
        else if (text[b] == '5') {
            textPoints = { {10, 0}, {0, 0}, {0, 10}, {10, 10}, {10, 20}, {0, 20} };
        }
        else if (text[b] == '6') {
            textPoints = { {10, 0}, {0, 0}, {0, 20}, {10, 20}, {10, 10}, {0, 10} };
        }
        else if (text[b] == '7') {
            textPoints = { {0, 0}, {10, 0}, {0, 20} };
        }
        else if (text[b] == '8') {
            textPoints = { {5, 10}, {0, 8}, {0, 0}, {10, 0}, {10, 8}, {0, 12}, {0, 20}, {10, 20}, {10, 12}, {5, 10} };
        }
        else if (text[b] == '9') {
            textPoints = { {0, 20}, {10, 20}, {10, 0}, {0, 0}, {0, 10}, {10, 10} };
        }
        else if (text[b] == '0') {
            textPoints = { {0, 0}, {10, 0}, {10, 20}, {0, 20}, {0, 0} };
        }
        else if (text[b] == '$') {
            textPoints = { {7, 0}, {-7, 0}, {-7, 10}, {7, 10}, {7, 20}, {-7, 20}, {0, 20}, {0, 25}, { 0,-5 } };
        }
        else if (text[b] == '-') {
            textPoints = { {0, 10}, {10, 10} };
        }
        else if (text[b] == ' ') {
            textPoints = { {32000, 32000} };
        }
        else if (text[b] == '<') {
            textPoints = { {10, 0}, {0, 10}, {10, 20} };
        }
        else if (text[b] == '>') {
            textPoints = { {0, 0}, {10, 10}, {0, 20} };
        }
        else if (text[b] == '.') {
            textPoints = { {0, 20}, {0, 15} };
        }
        else { std::cout << text[b] << std::endl;  return; }

        textObject.clear();
        for (size_t i = 0; i < textPoints.size() - 1; ++i) {
            addOutline(textObject,
                { x + textPoints[i].x + b * 20, y + textPoints[i].y },
                { x + textPoints[i + 1].x + b * 20, y + textPoints[i + 1].y },
                3.0f,  // Outline thickness
                sf::Color(outlineColor));

            addThickLine(textObject,
                { x + textPoints[i].x + b * 20, y + textPoints[i].y },
                { x + textPoints[i + 1].x + b * 20, y + textPoints[i + 1].y },
                3.0f,
                sf::Color(fillColor));
        }

        window.draw(textObject);
    }
}