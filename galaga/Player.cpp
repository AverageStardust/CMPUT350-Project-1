#include "Player.h"

#include "DrawContext.h"
#include "Keyboard.h"
#include "MathUtil.h"

Player::Player(CMPUT350::Point2D location) : location(location) {}

void Player::Initialize(CMPUT350::GameContext *context) {
    boundWidth = 40.0f;
    boundHeight = 40.0f;

    // Sign up for key press notifications
    context->mNotificationManager->Register(context->CurrObject, "shoot");
    context->mNotificationManager->Register(context->CurrObject, "move_left");
    context->mNotificationManager->Register(context->CurrObject, "stop_left");
    context->mNotificationManager->Register(context->CurrObject, "move_right");
    context->mNotificationManager->Register(context->CurrObject, "stop_right");
}

void Player::Update(CMPUT350::GameContext *context) {
    if (isLeftPressed && !isRightPressed) {
        location.x -= 5;
    } else if (isRightPressed && !isLeftPressed) {
        location.x += 5;
    }

    if (isShootPressed) {
        bullets.remove_if([](std::weak_ptr<Bullet> bullet) { return bullet.expired(); });
        int size = distance(bullets.begin(), bullets.end());  // yuck

        if (size < 2) {
            std::shared_ptr<Bullet> bullet =
                std::make_shared<Bullet>(location, CMPUT350::Point2D(0, -20), true);
            context->mEngineView->AddGameObject(bullet);
            bullets.push_front(bullet);
        }
        isShootPressed = false;
    }
}

void Player::LateUpdate(CMPUT350::GameContext *context) {}

void Player::ReceiveNotification(const std::string &notification) {
    // Handle key presses
    if (notification == "move_left") {
        isLeftPressed = true;
    } else if (notification == "stop_left") {
        isLeftPressed = false;
    } else if (notification == "move_right") {
        isRightPressed = true;
    } else if (notification == "stop_right") {
        isRightPressed = false;
    } else if (notification == "shoot") {
        isShootPressed = true;
    }
}

void Player::RenderForeground(CMPUT350::GameContext *context) {
    context->ScreenContext->DrawLine(CMPUT350::Point2D(20, 5), CMPUT350::Point2D(20, -10), 5,
                                     CMPUT350::Colors::red);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(-20, 5), CMPUT350::Point2D(-20, -10), 5,
                                     CMPUT350::Colors::red);

    context->ScreenContext->DrawRect(CMPUT350::Rect(CMPUT350::Point2D(-7, -20), 14, 40),
                                     CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(0, -10), CMPUT350::Point2D(-30, 15), 12,
                                     CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(0, -10), CMPUT350::Point2D(30, 15), 12,
                                     CMPUT350::Colors::white);

    context->ScreenContext->DrawRect(CMPUT350::Rect(CMPUT350::Point2D(-5, -15), 10, 10),
                                     CMPUT350::Colors::cyan);
}

void Player::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject> &obj) {}

void Player::Kill() {
    alive = false;

    for (auto bullet : bullets) {
        auto lock = bullet.lock();

        if (lock != nullptr) lock->Kill();
    }
}

bool Player::IsAlive() const { return alive; }

CMPUT350::Point2D Player::GetLocation() const { return location; };

float Player::GetRotation() const { return 0; };

const std::vector<CMPUT350::Shape> &Player::GetShapes() {
    static std::vector<CMPUT350::Shape> shapes;

    shapes.clear();
    shapes.push_back(CMPUT350::Rect(-boundWidth / 2, -boundHeight / 2, boundWidth, boundHeight));

    return shapes;
}
