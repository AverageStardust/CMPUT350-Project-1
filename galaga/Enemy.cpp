#include "Enemy.h"

#include "DrawContext.h"

Enemy::Enemy(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D> &path) : homeLocation(loc), entryPath(CMPUT350::Path(path, loc)) {}

void Enemy::Initialize(CMPUT350::GameContext *context) {
    // Manually setting bound size, change if desired
    boundWidth = 50.0f;
    boundHeight = 50.0f;
    speed = 10.0f;

    curPosition = 0.0f;
}

void Enemy::Update(CMPUT350::GameContext *context) {
    if (state == "enter") {
        location = entryPath.GetLocation(curPosition);
        curPosition = entryPath.Increment(speed, curPosition);
        //mRotation = atan(entryPath.GetSlope(curPosition));

        if ( curPosition >= 1) {
            state = "idle";
            location = entryPath.GetLocation(1.0f);
        }
    }
    else if (state == "idle") {
        
    }
    else if (state == "attack") {
        
    }
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

float Enemy::GetRotation() const {
    return mRotation;
};

const std::vector<CMPUT350::Shape> &Enemy::GetShapes() {
    static std::vector<CMPUT350::Shape> shapes;

    shapes.clear();
    shapes.push_back(CMPUT350::Rect(-boundWidth / 2, -boundHeight / 2, boundWidth, boundHeight));

    return shapes;
}


bool Enemy::Attack(CMPUT350::GameContext *context, const CMPUT350::Point2D &target) {
    if (state != "idle") {
        return false;
    }

    std::vector<CMPUT350::Point2D> AttackCurve { {384.8, 310.4}, {160.5, 118.4}, {266.9, 25.6}, {399.6, 27.2},
    {532.2, 28.8}, {607.5, 449.6}, {604.2, 566.4},
    {591.1, 664}, {327.5, 595.2}, {target.x - 180, 732.8}/*{224.3, 732.8}*/,
    {108.1, 860.8}, {227.6, 974.4}, target/*{371.7, 974.4}*/,
    {515.8, 974.4}, {655, 899.2}, {target.x + 180, 734.4}/*{543.7, 734.4}*/,
    {412.7, 566.4}, {250.5, 681.6}, {170.3, 582.4},
    {73.7, 480}, {178.5, 352}, {383.2, 312} }

    state = "attack";
    return true;
}
