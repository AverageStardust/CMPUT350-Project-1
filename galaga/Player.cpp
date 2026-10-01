#include "Player.h"

#include <cassert>
#include <memory>

#include "Bullet.h"
#include "DrawContext.h"
#include "MathUtil.h"

Player::Player(CMPUT350::Point2D location) : location(location) {}

void Player::Initialize(CMPUT350::GameContext *context) {
    boundWidth = 40.0f;
    boundHeight = 40.0f;
}

void Player::Update(CMPUT350::GameContext *context) {
    if (isLeftPressed && !isRightPressed) {
        location.x -= 5;
    } else if (isRightPressed && !isLeftPressed) {
        location.x += 5;
    }
}

void Player::LateUpdate(CMPUT350::GameContext *context) {}

void Player::HandleKeyEvent(CMPUT350::GameContext *context, int key, bool isPressed) {
    switch (key) {
        case 0:  // A
            isLeftPressed = isPressed;
            break;
        case 3:  // D
            isRightPressed = isPressed;
            break;
        case 40:  // Space
            if (isPressed) {
                bullets.remove_if([](std::weak_ptr<Bullet> bullet) { return bullet.expired(); });
                int size = distance(bullets.begin(), bullets.end());  // yuck

                if (size < 2) {
                    std::shared_ptr<Bullet> bullet =
                        std::make_shared<Bullet>(location, CMPUT350::Point2D(0, -20), true);
                    context->mEngineView->AddGameObject(bullet);
                    bullets.push_front(bullet);
                }
            }

            break;
    }
}

void Player::RenderForeground(CMPUT350::GameContext *context) {
    context->ScreenContext->DrawLine(location + CMPUT350::Point2D(20, 5),
                                     location + CMPUT350::Point2D(20, -10), 5,
                                     CMPUT350::Colors::red);
    context->ScreenContext->DrawLine(location + CMPUT350::Point2D(-20, 5),
                                     location + CMPUT350::Point2D(-20, -10), 5,
                                     CMPUT350::Colors::red);

    context->ScreenContext->DrawRect(CMPUT350::Rect(location + CMPUT350::Point2D(-7, -20), 14, 40),
                                     CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(location + CMPUT350::Point2D(0, -10),
                                     location + CMPUT350::Point2D(-30, 15), 12,
                                     CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(location + CMPUT350::Point2D(0, -10),
                                     location + CMPUT350::Point2D(30, 15), 12,
                                     CMPUT350::Colors::white);

    context->ScreenContext->DrawRect(CMPUT350::Rect(location + CMPUT350::Point2D(-5, -15), 10, 10),
                                     CMPUT350::Colors::cyan);
}

void Player::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject> &obj) {}

void Player::Kill() {
    alive = false;
}

bool Player::IsAlive() const {
    return alive;
}

const CMPUT350::Rect &Player::GetBounds() {
    static CMPUT350::Rect sBounds(location.y - boundHeight/2, location.x - boundWidth/2, boundWidth, boundHeight);
    return sBounds;
}
