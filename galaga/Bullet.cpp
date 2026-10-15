#include "Bullet.h"

#include "DrawContext.h"
#include "Enemy.h"
#include "GraphicsObject.h"
#include "MathUtil.h"
#include "Player.h"

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D velocity, bool player)
    : location(location), velocity(velocity), isFromPlayer(player) {}

bool Bullet::IsPlayerBullet() { return isFromPlayer; }

void Bullet::Initialize(CMPUT350::GameContext *context) {
    // Manually setting bound size, change if desired
    boundWidth = 4.0f;
    boundHeight = 4.0f;
}

void Bullet::Update(CMPUT350::GameContext *context) {
    location += velocity;

    if (location.y < 0 || location.y > 1024) {
        Kill();
    }
}

void Bullet::LateUpdate(CMPUT350::GameContext *context) {}

void Bullet::RenderBackground(CMPUT350::GameContext *context) {
    context->ScreenContext->DrawLine(location, location - velocity, 4, CMPUT350::Colors::red);
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject> &obj) {
    if ((typeid(obj) == typeid(Enemy) && IsPlayerBullet()) ||
        typeid(obj) == typeid(Player) && !IsPlayerBullet()) {
        obj->Kill();
        Kill();
    }
}

void Bullet::Kill() { alive = false; }

bool Bullet::IsAlive() const { return alive; }

CMPUT350::Point2D Bullet::GetLocation() const { return location; };

const std::vector<CMPUT350::Shape> &Bullet::GetShapes() {
    static std::vector<CMPUT350::Shape> shapes;

    shapes.clear();
    shapes.push_back(CMPUT350::Line({}, velocity * -1));

    return shapes;
}
