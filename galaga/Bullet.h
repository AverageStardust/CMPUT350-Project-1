#ifndef BULLET_H
#define BULLET_H

#include "CollisionObject.h"
#include "GameContext.h"

class Bullet : public CMPUT350::CollisionObject
{
public:
    Bullet(CMPUT350::Point2D location, CMPUT350::Point2D velocity, bool player);
    bool IsPlayerBullet();

    // GameObject Functions
    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;
    bool IsAlive() const override;
    void Kill() override;

    // Graphics Object Functions
    void RenderBackground(CMPUT350::GameContext* context) override;

    // Collision Object Functions
    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) override;
    const std::vector<CMPUT350::Shape> &GetShapes() override;

    CMPUT350::Point2D GetLocation() const override;

private:
    CMPUT350::Point2D location;
    CMPUT350::Point2D velocity;
    bool isFromPlayer;

    float boundWidth;
    float boundHeight;
    bool alive = true;
};
#endif // BULLET_H
