#ifndef GALAGA_H
#define GALAGA_H

#include <memory>
#include "EngineView.h"
#include "GameObject.h"
#include "MathUtil.h"
#include "Player.h"

enum class GalagaState { wait, spawn, play, over };

class Galaga : public CMPUT350::GameObject {
public:
    Galaga(int width, int height) : windowSize{float(width), float(height)} {}

    void Initialize(CMPUT350::GameContext *context) override;
    void Update(CMPUT350::GameContext *context) override;
    void LateUpdate(CMPUT350::GameContext *context) override;
    void RenderUI(CMPUT350::GameContext *context) override;
    void ReceiveNotification(const std::string &key) override;
    bool IsAlive() const override;
    void Kill() override {};

private:
    CMPUT350::EngineView* view;
    CMPUT350::Point2D windowSize;
    std::weak_ptr<CMPUT350::GameObject> mPlayer;
    bool alive = true;

    GalagaState state = GalagaState::wait;

    // wait data
    int cointsInserted = 0;
    bool startingNextFrame = false;

    // spawn data
    int spawnCooldown = 0;
    int waveEnemiesSpawned = 0;
    int wavesSpawned = 0;

    // spawn&play data
    int playerRespawnCooldown = -1;
    int attackCooldown = 0;
    int skipOverNEnemiesInAttack = 0;
    int enemiesLeft = 0;
    int level = 0;
    int lives = 0;

    // spawn&play&over data
    int score = 0;

    // over data
    int gameOverCooldown = 0;

    // transitions
    void StartGame(CMPUT350::GameContext *context);
    void FinishSpawning();
    void NextLevel();
    void FinishGame(CMPUT350::GameContext *context);
    void RestartGame();
    void Attack(CMPUT350::GameContext *context, int attackers);
};
#endif  // GALAGA_H
