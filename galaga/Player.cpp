#include "Player.h"

#include "DrawContext.h"
#include "Keyboard.h"
#include "MathUtil.h"

Player::Player(CMPUT350::Point2D location) : location(location) {}

void Player::Initialize(CMPUT350::GameContext *context) {
    boundWidth = 40.0f;
    boundHeight = 40.0f;

    mEngineView = context->mEngineView;

    // Sign up for key press notifications
    std::weak_ptr<GameObject> mSelf = weak_from_this();
    context->mNotificationManager->Register(mSelf, "shoot"      );
    context->mNotificationManager->Register(mSelf, "shoot_stop" );
    context->mNotificationManager->Register(mSelf, "move_left"  );
    context->mNotificationManager->Register(mSelf, "stop_left"  );
    context->mNotificationManager->Register(mSelf, "move_right" );
    context->mNotificationManager->Register(mSelf, "stop_right" );
}

void Player::Update(CMPUT350::GameContext *context) {
    if (isLeftPressed && !isRightPressed) {
        location.x -= 5;
    } else if (isRightPressed && !isLeftPressed) {
        location.x += 5;
    }
}

void Player::LateUpdate(CMPUT350::GameContext *context) {}

/*void Player::HandleKeyEvent(CMPUT350::GameContext *context, int key, bool isPressed) {
    switch (key) {
        case CMPUT350::Key::A:
            isLeftPressed = isPressed;
            break;
        case CMPUT350::Key::D:
            isRightPressed = isPressed;
            break;
        case CMPUT350::Key::Space:
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
}*/
void Player::ReceiveNotification(const std::string& key) {
    // Handle key presses
    if (key == "move_left")       { isLeftPressed  = true; }
    else if (key == "stop_left")  { isLeftPressed  = false; }

    else if (key == "move_right") { isRightPressed = true; }
    else if (key == "stop_right") { isRightPressed = false; }

    else if (key == "shoot")      {
        bullets.remove_if([](std::weak_ptr<Bullet> bullet) { return bullet.expired(); });
        int size = distance(bullets.begin(), bullets.end());  // yuck

        if (size < 2) {
            std::shared_ptr<Bullet> bullet =
                std::make_shared<Bullet>(location, CMPUT350::Point2D(0, -20), true);
            mEngineView->AddGameObject(bullet);
            bullets.push_front(bullet);
        }
    }
    else if (key == "shoot_stop") {}
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

CMPUT350::Point2D Player::GetLocation() const { return location; };

float Player::GetRotation() const { return 0; };

const std::vector<CMPUT350::Shape> &Player::GetShapes() {
    static std::vector<CMPUT350::Shape> shapes;

    shapes.clear();
    shapes.push_back(CMPUT350::Rect(-boundWidth / 2, -boundHeight / 2, boundWidth, boundHeight));

    return shapes;
}
