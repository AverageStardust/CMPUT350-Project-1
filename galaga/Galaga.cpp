#include "Galaga.h"

#include <cassert>

#include "DrawContext.h"
#include "Enemy.h"
#include "GameContext.h"
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
    view->InstallKeyDownNotification(CMPUT350::Key::Num1, "start");
    view->InstallKeyUpNotification(CMPUT350::Key::Num5, "coin");

    context->mNotificationManager->Register(context->CurrObject, "start");
    context->mNotificationManager->Register(context->CurrObject, "coin");
    context->mNotificationManager->Register(context->CurrObject, "enemy_died");

    view->AddGameObject(std::make_shared<Stars>(250, CMPUT350::Rect(0, 0, 768, 1024)));
}

void Galaga::Update(CMPUT350::GameContext *context) {
    switch (state) {
        case GalagaState::wait:
            if (startingNextFrame) {
                StartGame(context);
            }
            break;

        case GalagaState::spawn:
            spawnCooldown--;
            if (spawnCooldown <= 0) {
                auto enemy = std::make_shared<Enemy>(
                    CMPUT350::Point2D(80 + 87 * waveEnemiesSpawned, 80 + wavesSpawned * 87));
                context->mEngineView->AddGameObject(enemy);

                waveEnemiesSpawned++;
                spawnCooldown = 8;

                if (waveEnemiesSpawned == 8) {
                    waveEnemiesSpawned = 0;
                    wavesSpawned++;
                    spawnCooldown = 60;
                }

                if (wavesSpawned == 5) {
                    FinishSpawning();
                }
            }

            // fallthrough
        case GalagaState::play:
            if (enemiesLeft == 0) NextLevel();
            break;

        case GalagaState::over:
            gameOverCooldown--;
            if (gameOverCooldown <= 0) RestartGame();
            break;
    }
}

void Galaga::LateUpdate(CMPUT350::GameContext *context) {}

void Galaga::RenderUI(CMPUT350::GameContext *context) {
    switch (state) {
        case GalagaState::wait:
            if (cointsInserted > 0) {
                context->ScreenContext->DrawCenteredText(
                    "Press Start", 32, (windowSize / 2) - CMPUT350::Point2D(0, 32),
                    CMPUT350::Colors::cyan);
            } else {
                context->ScreenContext->DrawCenteredText("Insert Coins", 32,
                                                         windowSize / 2 - CMPUT350::Point2D(0, 32),
                                                         CMPUT350::Colors::cyan);
            }
            context->ScreenContext->DrawCenteredText("Coins: " + std::to_string(cointsInserted), 32,
                                                     windowSize / 2 + CMPUT350::Point2D(0, 32),
                                                     CMPUT350::Colors::cyan);
            break;

        case GalagaState::spawn:
        case GalagaState::play:
            context->ScreenContext->DrawText("Level: " + std::to_string(level), 20, {16, 16},
                                             CMPUT350::Colors::cyan);
            context->ScreenContext->DrawText("Lives: " + std::to_string(lives), 20,
                                             {windowSize.x / 3 + 16, 16}, CMPUT350::Colors::cyan);
            context->ScreenContext->DrawText("Score: " + std::to_string(score), 20,
                                             {windowSize.x / 3 * 2 + 16, 16},
                                             CMPUT350::Colors::cyan);
            break;

        case GalagaState::over:
            context->ScreenContext->DrawCenteredText(
                "Game Over", 32, windowSize / 2 - CMPUT350::Point2D(0, 32), CMPUT350::Colors::cyan);
            context->ScreenContext->DrawCenteredText("Final Score: " + std::to_string(score), 32,
                                                     windowSize / 2 + CMPUT350::Point2D(0, 32),
                                                     CMPUT350::Colors::cyan);

            gameOverCooldown--;
            if (gameOverCooldown == 0) RestartGame();
            break;
    }
}

void Galaga::ReceiveNotification(const std::string &key) {
    if (key == "coin") {
        cointsInserted++;
    } else if (key == "start" && state == GalagaState::wait && cointsInserted > 0) {
        cointsInserted--;
        startingNextFrame = true;
    } else if (key == "enemy_died") {
        enemiesLeft--;
        score += 5;
    }
}

bool Galaga::IsAlive() const { return alive; };

void Galaga::StartGame(CMPUT350::GameContext *context) {
    state = GalagaState::spawn;
    spawnCooldown = 30;
    waveEnemiesSpawned = 0;
    wavesSpawned = 0;
    enemiesLeft = 40;

    level = 1;
    score = 0;
    lives = 3;

    auto player = std::make_shared<Player>(CMPUT350::Point2D(int(768 / 2), 900));
    context->mEngineView->AddGameObject(player);
}

void Galaga::FinishSpawning() { state = GalagaState::play; }

void Galaga::NextLevel() {
    state = GalagaState::spawn;
    spawnCooldown = 60;
    waveEnemiesSpawned = 0;
    wavesSpawned = 0;
    enemiesLeft = 40;

    level++;
}

void Galaga::FinishGame(CMPUT350::GameContext *context) {
    state = GalagaState::over;
    gameOverCooldown = 120;
}

void Galaga::RestartGame() {
    state = GalagaState::wait;
    startingNextFrame = false;
}
