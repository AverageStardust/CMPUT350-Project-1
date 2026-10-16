#include "Enemy.h"

#include "DrawContext.h"

Enemy::Enemy(CMPUT350::Point2D loc) : location(loc) {}

void Enemy::Initialize(CMPUT350::GameContext *context) {
    // Manually setting bound size, change if desired
    boundWidth = 50.0f;
    boundHeight = 50.0f;
}

void Enemy::Update(CMPUT350::GameContext *context) {}

void Enemy::LateUpdate(CMPUT350::GameContext *context) {}

void Enemy::RenderBackground(CMPUT350::GameContext *context) {}

void Enemy::RenderForeground(CMPUT350::GameContext *context) {
    context->ScreenContext->DrawRect(
        CMPUT350::Rect(CMPUT350::Point2D(-boundWidth / 2, -boundHeight / 2), boundWidth,
                       boundHeight),
        CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(-20, 15), CMPUT350::Point2D(20, 15), 5,
                                     CMPUT350::Colors::red);
    context->ScreenContext->DrawCircle(CMPUT350::Point2D(-15, -5), 3, CMPUT350::Colors::red);
    context->ScreenContext->DrawCircle(CMPUT350::Point2D(15, -5), 3, CMPUT350::Colors::red);
}

void Enemy::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject> &obj) {}

void Enemy::Kill() { alive = false; }

bool Enemy::IsAlive() const { return alive; }

CMPUT350::Point2D Enemy::GetLocation() const { return location; };

float Enemy::GetRotation() const {
    return 0;
};

const std::vector<CMPUT350::Shape> &Enemy::GetShapes() {
    static std::vector<CMPUT350::Shape> shapes;

    shapes.clear();
    shapes.push_back(CMPUT350::Rect(-boundWidth / 2, -boundHeight / 2, boundWidth, boundHeight));

    return shapes;
}
