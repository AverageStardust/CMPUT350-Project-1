#ifndef PLAYER_H
#define PLAYER_H

#include <forward_list>
#include "Bullet.h"
#include "CollisionObject.h"
#include "MathUtil.h"

class Player : public CMPUT350::CollisionObject
{
    static const int MAX_PLAYER_BULLETS = 2;
public:
    Player(CMPUT350::Point2D loc);

    // GameObject Functions
    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;
    void HandleKeyEvent(CMPUT350::GameContext* context, int key, bool isPressed) override;
    bool IsAlive() const override;
    void Kill() override;

    // Graphics Object Functions
    void RenderForeground(CMPUT350::GameContext* context) override;


    // Collision Object Functions
    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) override;
    const CMPUT350::Rect& GetBounds() override;

private:
    CMPUT350::Point2D location;
    std::forward_list<std::weak_ptr<Bullet>> bullets;
    bool isLeftPressed = false;
    bool isRightPressed = false;

    float boundWidth;
    float boundHeight;
    bool alive = true;
};

#endif
