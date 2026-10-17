#include "Bullet.h"

#include "DrawContext.h"
#include "Enemy.h"
#include "GraphicsObject.h"
#include "MathUtil.h"
#include "Player.h"

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D velocity, bool isFromPlayer)
    : location(location), velocity(velocity), isFromPlayer(isFromPlayer) {}

void Bullet::Initialize(CMPUT350::GameContext *context) {
    // Manually setting bound size, change if desired
    boundWidth = 4.0f;
    boundHeight = 4.0f;

    explosionTime = 4;

    if (isFromPlayer) {
        bulletColor = CMPUT350::Colors::orange;
    } else {
        bulletColor = CMPUT350::Colors::red;
    }
}

void Bullet::Update(CMPUT350::GameContext *context) {
    if (isExploding) {
        explosionTime -= 1;
        if (explosionTime <= 0) {
            Kill();
        }
    } else {
        location += velocity;
    }

    if (location.y < 0 || location.y > 1024 || location.x < 0 || location.x > 768) {
        Kill();
    }
}

void Bullet::RenderBackground(CMPUT350::GameContext *context) {
    if (isExploding) {
        context->ScreenContext->DrawCircle(explosionPosition, 15, bulletColor);
    } else {
        context->ScreenContext->DrawLine({}, velocity * -1, 4, bulletColor);
    }
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject> &obj,
                            const CMPUT350::Point2D &collisionPoint) {
    bool enemyHit = (typeid(*obj) == typeid(Enemy)) && isFromPlayer;
    bool playerHit = (typeid(*obj) == typeid(Player)) && !isFromPlayer;
    if (enemyHit || playerHit) {
        obj->Kill();

        if (!isExploding || collisionPoint.y > explosionPosition.y) {
            explosionPosition = collisionPoint;
        }
        isExploding = true;
    }
}

void Bullet::Kill() { alive = false; }

bool Bullet::IsAlive() const { return alive; }

CMPUT350::Point2D Bullet::GetLocation() const { return location; };

float Bullet::GetRotation() const { return atan2(velocity.x, -velocity.y); }

const std::vector<CMPUT350::Shape> &Bullet::GetShapes() {
    static std::vector<CMPUT350::Shape> shapes;

    shapes.clear();
    shapes.push_back(CMPUT350::Line({}, velocity * -1));

    return shapes;
}
