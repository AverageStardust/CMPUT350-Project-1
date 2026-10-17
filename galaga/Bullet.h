#ifndef BULLET_H
#define BULLET_H

#include "CollisionObject.h"
#include "GameContext.h"
#include "DrawContext.h"

class Bullet : public CMPUT350::CollisionObject
{
public:
    Bullet(CMPUT350::Point2D location, CMPUT350::Point2D velocity, bool fromPlayer);

    // GameObject Functions
    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    bool IsAlive() const override;
    void Kill() override;

    // Graphics Object Functions
    void RenderBackground(CMPUT350::GameContext* context) override;

    // Collision Object Functions
    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj, const CMPUT350::Point2D &collisionPoint) override;

    const std::vector<CMPUT350::Shape> &GetShapes() override;
    CMPUT350::Point2D GetLocation() const override;
    float GetRotation() const override;

private:
    CMPUT350::Point2D location;
    CMPUT350::Point2D velocity;
    const bool isFromPlayer;

    float boundWidth;
    float boundHeight;
    bool alive = true;

    bool isExploding = false;
    int explosionTime; // counts down to 0 once activated and then is destroyed
    CMPUT350::Point2D explosionPosition;

    CMPUT350::RGBColor bulletColor = CMPUT350::RGBColor(0, 0, 0);
};
#endif // BULLET_H
