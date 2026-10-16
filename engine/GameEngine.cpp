#include "GameEngine.h"

#include <memory>

#include "CollisionObject.h"
#include "DrawContext.h"
#include "NotificationManager.h"
#include "SFML/Graphics/Font.hpp"

/// @brief
namespace CMPUT350 {

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string &name) {
    // load font
    mFont = std::make_shared<sf::Font>(sf::Font());
    if (!mFont->openFromMemory(_font, _font_len)) {
        fprintf(stderr, "WARNING: Font did not load.\n");
    }

    // Setup window
    std::shared_ptr<sf::RenderWindow> windowPointer =
        std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(width, height)), name);
    windowPointer->setFramerateLimit(30);
    mWindow = windowPointer;
}

GameEngine::~GameEngine() {
    // Cleanup resources
    delete mNotificationManager;
    mWindow->close();
}

// EngineView functions -------------------------------------------

void GameEngine::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    // Add the gameObject to our "added" vector to tell the game to activate it
    addedGameObjects.push_back(gameObject);
}

// Key notifications
void GameEngine::InstallKeyDownNotification(int notifKey, const std::string &notification) {
    // Register key with Notification manager for keydown events.
    // NotifKey is the scancode of the key we want to implement.
    mRegisteredKeys.push_back(1 + notifKey);
    mRegisteredNotifications.push_back(notification);
}
void GameEngine::InstallKeyUpNotification(int notifKey, const std::string &notification) {
    // Register key with Notification manager for keyup events.
    // NotifKey is the scancode of the key we want to implement.
    mRegisteredKeys.push_back(-(1 + notifKey));
    mRegisteredNotifications.push_back(notification);
}

void GameEngine::NotifyForInstalledKey(int notifKey) {
    // Tells NotificationManager to notify all GameObjects registered for notifkey
    for (int i = 0; i < mRegisteredKeys.size(); ++i) {
        if (mRegisteredKeys[i] == notifKey) {
            mNotificationManager->Notify(mRegisteredNotifications[i]);
        }
    }
}

// Iterators
EngineView::const_iterator GameEngine::begin() const { return mGameObjects.begin(); }
EngineView::const_iterator GameEngine::end() const { return mGameObjects.end(); }

// ----------------------------------------------------------------

// Engine loop functions ------------------------------------------

void GameEngine::CleanupDeadGameObjects() {
    // Logic copied from Lab 2
    // Apply a filter to remove dead GameObjects
    std::vector<std::shared_ptr<GameObject>> filterResult;
    // Use a vector swap filter to remove dead bullets
    for (std::shared_ptr<GameObject> gObj : mGameObjects) {
        if (gObj->IsAlive()) {
            filterResult.push_back(gObj);
        }
    }
    mGameObjects.swap(filterResult);

    // clean referances to old objects
    // mNotificationManager->Clean();
}

bool GameEngine::ProcessEvents(GameContext *context) {
    // Returns true if the window has been closed
    // Also checks for window resizing and key presses

    while (const std::optional event = mWindow->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            mWindow->close();
            return true;
        } else if (const auto *resize = event->getIf<sf::Event::Resized>()) {
            mWindow->setView(sf::View(
                sf::FloatRect({0.f, 0.f}, {float(resize->size.x), float(resize->size.y)})));
        } else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            NotifyForInstalledKey(1 + int(keyPressed->scancode));
        } else if (const auto *keyPressed = event->getIf<sf::Event::KeyReleased>()) {
            NotifyForInstalledKey(-1 * (1 + int(keyPressed->scancode)));
        }
    }

    return false;
}

void GameEngine::ProcessCollisions() {
    // Check each object against each other object and call CollisionEnter on any objects that
    // intersect

    std::vector<std::shared_ptr<CollisionObject>> colliders;

    for (int i = 0; i < mGameObjects.size(); i++) {
        std::shared_ptr<CollisionObject> collider =
            std::dynamic_pointer_cast<CollisionObject>(mGameObjects[i]);

        if (collider != nullptr) {
            colliders.push_back(collider);
            collider->UpdateBounds();
        }
    }

    for (int i = 0; i < colliders.size(); i++) {
        for (int j = i + 1; j < colliders.size(); j++) {
            bool isColliding = colliders[i]->CheckCollision(*colliders[j]);
            if (isColliding) {
                colliders[i]->CollisionEnter(colliders[j]);
                colliders[j]->CollisionEnter(colliders[i]);
            }
        }
    }
}

void GameEngine::RenderObjects(GameContext *context, bool drawColliders) {
    // Iterate over all GameObjects and render GraphicsObjects to the screen
    // Render objects to the background
    for (std::shared_ptr<GameObject> gObj : mGameObjects) {
        std::shared_ptr<GraphicsObject> graphicObj =
            std::dynamic_pointer_cast<GraphicsObject>(gObj);
        if (graphicObj != nullptr) {
            context->ScreenContext->transform = graphicObj->GetTransform();
            context->CurrObject = gObj->weak_from_this();
            graphicObj->RenderBackground(context);
        }
    }

    // Render objects to the foreground
    for (std::shared_ptr<GameObject> gObj : mGameObjects) {
        std::shared_ptr<GraphicsObject> graphicObj =
            std::dynamic_pointer_cast<GraphicsObject>(gObj);
        if (graphicObj != nullptr) {
            context->ScreenContext->transform = graphicObj->GetTransform();
            context->CurrObject = gObj->weak_from_this();
            graphicObj->RenderForeground(context);
        }
    }

    if (drawColliders) {
        // Render colliders
        for (std::shared_ptr<GameObject> gObj : mGameObjects) {
            std::shared_ptr<CollisionObject> collisionObj =
                std::dynamic_pointer_cast<CollisionObject>(gObj);
            if (collisionObj != nullptr) {
                context->ScreenContext->transform = collisionObj->GetTransform();
                context->ScreenContext->FrameRect(collisionObj->bounds, 1, Colors::green);
            }
        }
    }
}

// ----------------------------------------------------------------

/**
 * @method Run
 * @arguments None
 * @description Gives control to the game engine. Will not return until the game window is closed or
 * all objects have been destroyed.
 */
void GameEngine::Run() {
    GameContext *context = new GameContext(this, new DrawContext(mWindow, mFont),
                                           new DrawContext(mWindow, mFont), mNotificationManager);

    while (true)  // window is open
    {
        // 0. Remove any objects that are now dead
        CleanupDeadGameObjects();

        // 1. Activate and initialize any objects added during the last frame
        for (std::shared_ptr<GameObject> gObj : addedGameObjects) {
            mGameObjects.push_back(gObj);

            context->CurrObject = gObj->weak_from_this();
            gObj->Initialize(context);
        }
        addedGameObjects.clear();

        // 2. Process events
        bool shouldClose = ProcessEvents(context);
        if (shouldClose) {
            break;
        }

        // 3. Update game objects
        for (std::shared_ptr<GameObject> gObj : mGameObjects) {
            context->CurrObject = gObj->weak_from_this();
            gObj->Update(context);

            std::shared_ptr<CollisionObject> collisionObj =
                std::dynamic_pointer_cast<CollisionObject>(gObj);
            if (collisionObj != nullptr) {
                collisionObj->UpdateTransform();
            }
        }

        // 4. Process collision events
        ProcessCollisions();

        // 5. Late updates
        for (std::shared_ptr<GameObject> gObj : mGameObjects) {
            context->CurrObject = gObj->weak_from_this();
            gObj->LateUpdate(context);
        }

        // Clear window
        mWindow->clear(sf::Color::Black);

        // 6. Render background
        // 7. Render foreground
        RenderObjects(context, false);

        // Actually render to window
        mWindow->display();
        context->currentFrame++;
    }

    delete context->ScreenContext;
    delete context;
}

}  // namespace CMPUT350
