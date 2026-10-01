#include "Bullet.h"
#include "DrawContext.h"
#include "GraphicsObject.h"

#include "Player.h"
#include "Enemy.h"

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player) :
location(location), heading(heading), isFromPlayer(player)
{
}

bool Bullet::IsPlayerBullet()
{
    return isFromPlayer;
}

void Bullet::Initialize(CMPUT350::GameContext* context)
{
    // Manually setting bound size, change if desired
    boundWidth = 2.0f;
    boundHeight = 2.0f;
}

void Bullet::Update(CMPUT350::GameContext* context)
{
    CMPUT350::Point2D diff = heading - location;
    location = heading;
    heading = location + diff;

    if (location.y < 0 || location.y > 1024) {
        Kill();
    }
}

void Bullet::LateUpdate(CMPUT350::GameContext* context)
{
}


void Bullet::RenderBackground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawCircle(location, 10, CMPUT350::Colors::red);
    CMPUT350::Rect yBounds(location.y - boundWidth/2, location.x - boundHeight/2, boundWidth, boundHeight + (location - heading).y);
    context->ScreenContext->DrawRect(yBounds, CMPUT350::Colors::white);
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    if ((typeid(*obj) == typeid(Enemy) && IsPlayerBullet()) ||
            typeid(*obj) == typeid(Player) && !IsPlayerBullet()) {
        obj->Kill();
        Kill();
    }
}

void Bullet::Kill()
{
    alive = false;
}

bool Bullet::IsAlive() const
{
    return alive;
}

const CMPUT350::Rect& Bullet::GetBounds()
{
    CMPUT350::Point2D diff = heading - location;
    if (location.y > heading.y) {
        static CMPUT350::Rect downBounds(location.y - boundWidth/2, heading.x - boundHeight/2, boundWidth, boundHeight - diff.y);
        return downBounds;
    }
    else {
        static CMPUT350::Rect upBounds(location.y - boundWidth/2, location.x - boundHeight/2, boundWidth, boundHeight + diff.y);
        return upBounds;
    }
}
