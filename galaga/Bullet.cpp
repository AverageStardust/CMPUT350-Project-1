#include "Bullet.h"

#include "DrawContext.h"
#include "Enemy.h"
#include "GraphicsObject.h"
#include "MathUtil.h"
#include "Player.h"

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player)
    : location(location), heading(heading), isFromPlayer(player) {}

bool Bullet::IsPlayerBullet() { return isFromPlayer; }

void Bullet::Initialize(CMPUT350::GameContext *context) {
    // Manually setting bound size, change if desired
    boundWidth = 2.0f;
    boundHeight = 2.0f;
}

void Bullet::Update(CMPUT350::GameContext *context) {
    location += heading;

    if (location.y < 0 || location.y > 1024) {
        Kill();
    }
}

void Bullet::LateUpdate(CMPUT350::GameContext *context) {}

void Bullet::RenderBackground(CMPUT350::GameContext *context) {
    context->ScreenContext->DrawCircle(location, 10, CMPUT350::Colors::red);
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject> &obj) {
    if ((typeid(*obj) == typeid(Enemy) && IsPlayerBullet()) ||
        typeid(*obj) == typeid(Player) && !IsPlayerBullet()) {
        obj->Kill();
        Kill();
    }
}

void Bullet::Kill() { alive = false; }

bool Bullet::IsAlive() const { return alive; }

const CMPUT350::Rect &Bullet::GetBounds() {
    CMPUT350::Point2D oldLocation = location - heading;
    CMPUT350::Rect currentBounds(location.x - boundWidth / 2, location.y - boundHeight / 2,
                                 boundWidth, boundHeight);
    CMPUT350::Rect oldBounds(oldLocation.x - boundWidth / 2, oldLocation.y - boundHeight / 2,
                             boundWidth, boundHeight);

    static CMPUT350::Rect pathBounds;
    pathBounds = currentBounds | oldBounds;

    return pathBounds;
}
