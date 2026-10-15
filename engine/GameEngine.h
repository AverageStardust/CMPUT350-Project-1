
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

namespace CMPUT350 {
class GameEngine;
}

#include <memory>
#include <vector>

#include "CollisionObject.h"
#include "EngineView.h"
#include "FontData.h"
#include "GameContext.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>

namespace CMPUT350 {

class DrawContext;

class GameEngine : public EngineView {
public:
    GameEngine(unsigned int width, unsigned int height, const std::string &name);
    ~GameEngine();

    GameEngine(const GameEngine &) = delete;             // Prevent copy-construction
    GameEngine(GameEngine &&) = delete;                  // Prevent move-construction
    GameEngine &operator=(const GameEngine &) = delete;  // Prevent assignment
    GameEngine &operator=(GameEngine &&) = delete;       // Prevent move-assignment

    void AddGameObject(std::shared_ptr<GameObject> gameObject) override;
    void InstallKeyDownNotification(int, const std::string &notification) override;
    void InstallKeyUpNotification(int, const std::string &notification) override;
    void CallNotification();

    bool ProcessEvents(GameContext *context);
    void cleanupDeadGameObjects();
    void processCollisions();
    void renderObjects(GameContext *context);

    void Run();

private:
    std::shared_ptr<sf::RenderWindow> mWindow;
    std::shared_ptr<sf::Font> mFont;
    std::vector<std::shared_ptr<GameObject>> mGameObjects;
    std::vector<std::shared_ptr<GameObject>> addedGameObjects;  // Newly added objects that will be activated on the next frame

    // Notification manager (the vectors are mapped to one another)
    std::shared_ptr<sf::NotificationManager> mNotificationManager;
    std::vector<int> registeredKeys; // Positive ints are for keydown events, negative ints are for keyup events
    std::vector<std::string> registeredNotifications;
};

}  // namespace CMPUT350

#endif  // GAMEENGINE_H
