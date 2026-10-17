#include "Enemy.h"

#include <cmath>

#include "Bullet.h"
#include "DrawContext.h"

Enemy::Enemy(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D> &path)
    : homeLocation(loc), entryPath(CMPUT350::Path(path, loc)) {}

void Enemy::Initialize(CMPUT350::GameContext *context) {
    // Manually setting bound size, change if desired
    boundWidth = 50.0f;
    boundHeight = 50.0f;
    speed = 10.0f;

    curPosition = 0.0f;
}

// code from user151496 at https://stackoverflow.com/a/14498790
float lerpAngle(float start, float end, float amount) {
    float shortestAngle =
        std::fmod(((std::fmod(end - start, M_PI * 2)) + (M_PI * 3)), (M_PI * 2)) - M_PI;
    return start + shortestAngle * amount;
}

void Enemy::Update(CMPUT350::GameContext *context) {
    if (state == "enter") {
        location = entryPath.GetLocation(curPosition);
        curPosition = entryPath.Increment(speed, curPosition);
        mRotation = entryPath.GetSlope(curPosition).Angle() + M_PI_2;

        if (curPosition >= 1) {
            state = "idle";
            location = entryPath.GetLocation(1.0f);
        }
    } else if (state == "idle") {
        float targetRotation = std::sin(context->currentFrame * 0.05);
        mRotation = lerpAngle(mRotation, targetRotation, 0.03);
    } else if (state == "attack") {
        if (context->currentFrame % 30 == 0) {
            std::shared_ptr<Bullet> bullet =
                std::make_shared<Bullet>(location, CMPUT350::Point2D(0, 20), false);
            context->mEngineView->AddGameObject(bullet);
            state = "idle";
        }
    }
}

bool Enemy::Attack(CMPUT350::GameContext *context, const CMPUT350::Point2D &target) {
    if (state != "idle") return false;

    attackTarget = target;

    return true;
}

void Enemy::LateUpdate(CMPUT350::GameContext *context) {
    if (!alive) {
        context->mNotificationManager->Notify("enemy_died");
    }
}

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

float Enemy::GetRotation() const { return mRotation; };

const std::vector<CMPUT350::Shape> &Enemy::GetShapes() {
    static std::vector<CMPUT350::Shape> shapes;

    shapes.clear();
    shapes.push_back(CMPUT350::Rect(-boundWidth / 2, -boundHeight / 2, boundWidth, boundHeight));

    return shapes;
}
