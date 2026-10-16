#include "DrawContext.h"

#include "MathUtil.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

namespace CMPUT350 {

DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font)
    : mWindow(window), mFont(font) {}

void DrawContext::DrawCenteredText(const std::string &str, int pixelSize, Point2D p, RGBColor c) {
    sf::Text text(*mFont, str, pixelSize);

    text.setFillColor(c.AsSfmlColor());
    text.setPosition(p.AsSfmlVector());
    text.setLineAlignment(sf::Text::LineAlignment::Center);

    mWindow->draw(text);
}

void DrawContext::DrawText(const std::string &str, int pixelSize, Point2D p, RGBColor c) {
    sf::Text text(*mFont, str, pixelSize);

    text.setFillColor(c.AsSfmlColor());
    text.setPosition(p.AsSfmlVector());

    mWindow->draw(text);
}

void DrawContext::DrawCircle(Point2D p, float radius, RGBColor c) {
    sf::CircleShape circle(radius);

    circle.setPosition((p - radius).AsSfmlVector());
    circle.setFillColor(c.AsSfmlColor());

    mWindow->draw(circle);
}

void DrawContext::DrawRect(Rect r, RGBColor c) {
    sf::RectangleShape rect(r.Size().AsSfmlVector());

    rect.setPosition(r.topLeft.AsSfmlVector());
    rect.setFillColor(c.AsSfmlColor());

    mWindow->draw(rect);
}

void DrawContext::FrameRect(Rect r, float width, RGBColor c) {
    sf::RectangleShape rect(r.Size().AsSfmlVector());

    rect.setPosition(r.topLeft.AsSfmlVector());
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(c.AsSfmlColor());
    rect.setOutlineThickness(1);

    mWindow->draw(rect);
}

/**
 * @brief Draws a line between two points with a specified width and color.
 *
 * @param from The starting point of the line (Point2D).
 * @param to The ending point of the line (Point2D).
 * @param width The width of the line in pixels.
 * @param c The color of the line, specified as an RGBColor object.
 *
 * This function calculates the distance and angle between the two points
 * and uses a polygone shape to represent the line. The line is drawn
 * relative to the world offset and rendered onto the associated window.
 */
void DrawContext::DrawLine(Point2D from, Point2D to, float width, RGBColor c) {
    if(to == from) return;

    sf::RectangleShape rect({from.Distance(to), width});

    Point2D tangent = (to - from).Normalized();
    Point2D normal = tangent.Perpendicular();

    rect.setPosition((from - normal * width / 2).AsSfmlVector());
    rect.setRotation(tangent.AsSfmlVector().angle());
    rect.setFillColor(c.AsSfmlColor());

    mWindow->draw(rect);
}

int DrawContext::GetWindowWidth() { return mWindow->getSize().x; }

int DrawContext::GetWindowHeight() { return mWindow->getSize().y; }

}  // namespace CMPUT350
