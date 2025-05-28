#include "path.hpp"
#include "towerDefence.hpp"

void addThickPathLine(sf::VertexArray& array, sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color) {
    sf::Vector2f direction = end - start;
    sf::Vector2f perpendicular(-direction.y, direction.x);

    float length = std::sqrt(perpendicular.x * perpendicular.x + perpendicular.y * perpendicular.y);
    perpendicular /= length;
    perpendicular *= thickness;  // Increased thickness for better visibility

    array.append(sf::Vertex(start + perpendicular, color));
    array.append(sf::Vertex(start - perpendicular, color));
    array.append(sf::Vertex(end - perpendicular, color));
    array.append(sf::Vertex(end + perpendicular, color));
}

void addPathOutline(sf::VertexArray& array, sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color outlineColor) {
    sf::Vector2f direction = end - start;
    sf::Vector2f perpendicular(-direction.y, direction.x);

    float length = std::sqrt(perpendicular.x * perpendicular.x + perpendicular.y * perpendicular.y);
    perpendicular /= length;
    perpendicular *= thickness * 1.5f;  // Increased outline size for better contrast

    array.append(sf::Vertex(start + perpendicular, outlineColor));
    array.append(sf::Vertex(start - perpendicular, outlineColor));
    array.append(sf::Vertex(end - perpendicular, outlineColor));
    array.append(sf::Vertex(end + perpendicular, outlineColor));
}

sf::VertexArray drawPath(const std::vector<sf::Vector2f>& path, float x, float y, float b, sf::Color fillColor, sf::Color outlineColor) {
    sf::VertexArray lines(sf::LinesStrip, path.size());
    sf::VertexArray thickLines(sf::Quads);    // For thick lines
    sf::VertexArray outlines(sf::Quads);      // For outlines

    for (size_t i = 0; i < path.size(); ++i) {
        lines[i].position = path[i];
        lines[i].color = sf::Color::White;
    }

    for (size_t i = 0; i < path.size() - 1; ++i) {
        sf::Vector2f start = { x + path[i].x + b * 20, y + path[i].y };
        sf::Vector2f end = { x + path[i + 1].x + b * 20, y + path[i + 1].y };

        addPathOutline(outlines, start, end, 8.0f, outlineColor);  // Thicker outline
        addThickPathLine(thickLines, start, end, 6.0f, fillColor); // Thicker main path
    }

    // Combine all layers for rendering
    sf::VertexArray finalPath(sf::Quads, outlines.getVertexCount() + thickLines.getVertexCount());
    for (size_t i = 0; i < outlines.getVertexCount(); ++i)
        finalPath.append(outlines[i]);
    for (size_t i = 0; i < thickLines.getVertexCount(); ++i)
        finalPath.append(thickLines[i]);

    return finalPath;
}