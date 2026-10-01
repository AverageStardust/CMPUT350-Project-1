#include "Enemy.h"
#include "Bullet.h"
#include "DrawContext.h"

Enemy::Enemy(CMPUT350::Point2D loc) : location(loc)
{
}

void Enemy::Initialize(CMPUT350::GameContext* context)
{
    // Manually setting bound size, change if desired
    boundWidth = 50.0f;
    boundHeight = 50.0f;
}

void Enemy::Update(CMPUT350::GameContext* context)
{
}

void Enemy::LateUpdate(CMPUT350::GameContext* context)
{
}


void Enemy::RenderBackground(CMPUT350::GameContext* context)
{
}

void Enemy::RenderForeground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawRect(CMPUT350::Rect(location - CMPUT350::Point2D(boundWidth/2, boundHeight/2), boundWidth, boundHeight),
                                    CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(location + CMPUT350::Point2D(-20, 15),
                                    location + CMPUT350::Point2D(20, 15),
                                    5,
                                    CMPUT350::Colors::red);
    context->ScreenContext->DrawCircle(location + CMPUT350::Point2D(-15, -5),
                                    3,
                                    CMPUT350::Colors::red);
    context->ScreenContext->DrawCircle(location + CMPUT350::Point2D(15, -5),
                                    3,
                                    CMPUT350::Colors::red);
}

void Enemy::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
}

void Enemy::Kill()
{
}

bool Enemy::IsAlive() const
{
    return alive;
}

const CMPUT350::Rect& Enemy::GetBounds()
{
    static CMPUT350::Rect sBounds(location - CMPUT350::Point2D(boundWidth/2, boundHeight/2), boundWidth, boundHeight);
    return sBounds;
}
