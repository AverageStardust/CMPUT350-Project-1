#include "Galaga.h"

#include "Enemy.h"
#include "Keyboard.h"
#include "MathUtil.h"
#include "Player.h"
#include "Stars.h"

void Galaga::Initialize(CMPUT350::GameContext *context) {
    auto view = context->mEngineView;

    view->InstallKeyDownNotification(CMPUT350::Key::Space, "shoot");
    view->InstallKeyDownNotification(CMPUT350::Key::A, "move_left");
    view->InstallKeyUpNotification(CMPUT350::Key::A, "stop_left");
    view->InstallKeyDownNotification(CMPUT350::Key::D, "move_right");
    view->InstallKeyUpNotification(CMPUT350::Key::D, "stop_right");

    auto player = std::make_shared<Player>(CMPUT350::Point2D(int(768 / 2), 900));
    view->AddGameObject(player);

    view->AddGameObject(std::make_shared<Stars>(250, CMPUT350::Rect(0, 0, 768, 1024)));
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 10; x++) {
            auto enemy = std::make_shared<Enemy>(CMPUT350::Point2D(40 + x * 76, 76 + y * 76));
            view->AddGameObject(enemy);
        }
    }
};

void Galaga::Update(CMPUT350::GameContext *context) {

};

void Galaga::LateUpdate(CMPUT350::GameContext *context) {

};

bool Galaga::IsAlive() const { return alive; };
