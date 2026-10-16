#ifndef PLAYER_H
#define PLAYER_H

#include <cassert>
#include <forward_list>
#include <memory>

#include "Bullet.h"
#include "CollisionObject.h"

class Player : public CMPUT350::CollisionObject {
    static const int MAX_PLAYER_BULLETS = 2;

public:
    Player(CMPUT350::Point2D loc);

    // GameObject Functions
    void Initialize(CMPUT350::GameContext *context) override;
    void Update(CMPUT350::GameContext *context) override;
    void LateUpdate(CMPUT350::GameContext *context) override;
    bool IsAlive() const override;
    void Kill() override;
    void ReceiveNotification(const std::string& key) override;

    // Graphics Object Functions
    void RenderForeground(CMPUT350::GameContext *context) override;

    // Collision Object Functions
    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject> &obj) override;
    const std::vector<CMPUT350::Shape> &GetShapes() override;

    CMPUT350::Point2D GetLocation() const override;
    float GetRotation() const override;

private:
    CMPUT350::Point2D location;
    std::forward_list<std::weak_ptr<Bullet>> bullets;
    bool isLeftPressed = false;
    bool isRightPressed = false;

    float boundWidth;
    float boundHeight;
    bool alive = true;

    CMPUT350::EngineView *mEngineView;
};

#endif
