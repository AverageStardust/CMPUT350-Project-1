#include "Galaga.h"

#include "Enemy.h"
#include "Keyboard.h"
#include "MathUtil.h"
#include "Player.h"
#include "Stars.h"

#include <vector>
#include <iostream>

void Galaga::Initialize(CMPUT350::GameContext *context) {
    auto view = context->mEngineView;

    // Install key events
    view->InstallKeyDownNotification(CMPUT350::Key::Space, "shoot");
    view->InstallKeyDownNotification(CMPUT350::Key::A, "move_left");
    view->InstallKeyUpNotification(CMPUT350::Key::A, "stop_left");
    view->InstallKeyDownNotification(CMPUT350::Key::D, "move_right");
    view->InstallKeyUpNotification(CMPUT350::Key::D, "stop_right");


    view->AddGameObject(std::make_shared<Stars>(250, CMPUT350::Rect(0, 0, 768, 1024)));

    auto player = std::make_shared<Player>(CMPUT350::Point2D(int(768 / 2), 900));
    view->AddGameObject(player);


    // Define enemy curve
    std::vector<CMPUT350::Point2D> enemyEntry = { {562, 0}, {612, 125}, {146, 291}, {82, 402},
                    {18, 512}, {87, 582}, {156, 602}, {224, 621}, {326, 538}, {357, 475} };


    // Initialize enemies
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 10; x++) {
            auto enemy = std::make_shared<Enemy>(CMPUT350::Point2D(40 + x * 76, 76 + y * 76), enemyEntry);
            view->AddGameObject(enemy);
            std::cout << "Added Enemy\n";
        }
    }
};

void Galaga::Update(CMPUT350::GameContext *context) {

};

void Galaga::LateUpdate(CMPUT350::GameContext *context) {

};

bool Galaga::IsAlive() const { return alive; };
