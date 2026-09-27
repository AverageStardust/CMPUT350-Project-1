#include "GameEngine.h"

/// @brief
namespace CMPUT350 {
#include "FontData.h"


GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& name) {
    // Sample font loading code
    if (!mFont->openFromMemory(&_font, _font_len))
    {
    	fprintf(stderr, "WARNING: Font did not load.\n");
    }
    // Setup window
    std::shared_ptr<sf::RenderWindow> windowPointer = std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(width, height)), name);
    windowPointer->setFramerateLimit(30);
    mWindow = windowPointer;
}

GameEngine::~GameEngine() {
    // Cleanup resources
    mWindow->close();
}

void GameEngine::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    // Add the gameObject to our "added" vector to tell the game to activate it
    addedGameObjects.push_back(gameObject);
    mObjectSize += 1;
}



void GameEngine::cleanupDeadGameObjects() {
    // Logic copied from Lab 2
    // Apply a filter to remove dead GameObjects
    std::vector<std::shared_ptr<GameObject>> filterResult;
    // Use a vector swap filter to remove dead bullets
    for (std::shared_ptr<GameObject> gObj: mGameObjects) {
        if (gObj->IsAlive()) {
            filterResult.push_back(gObj);
        }
        else {
            mObjectSize -= 1;
        }
    }
    mGameObjects.swap(filterResult);
}


bool GameEngine::ProcessEvents(GameContext *context) {
    // Returns true if the window has been closed

    context->inputs.clear();
    context->inputs = std::vector<bool> {false, false, false};

	while (const std::optional event = mWindow->pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
            mWindow->close();
            return true;
		}
		else if (const auto* resize = event->getIf<sf::Event::Resized>()) {
            mWindow->setView(sf::View(sf::FloatRect({0.f, 0.f}, {static_cast<float>(resize->size.x), static_cast<float>(resize->size.y)})));
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
            context->inputs.push_back(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));     // move left
            context->inputs.push_back(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D));     // move right
            context->inputs.push_back(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)); // shoot

		}
	}
    return false;
}


void GameEngine::processCollisions() {
    // Checks if any gameObjects are colliding                                              TODO: more efficient collision detection?
    for (int i = 0; i < mObjectSize; i++) {
        for (int k = i + 1; k < mObjectSize; k++) {
            std::shared_ptr<CollisionObject> gObj1 = std::dynamic_pointer_cast<CollisionObject>(mGameObjects[i]);
            std::shared_ptr<CollisionObject> gObj2 = std::dynamic_pointer_cast<CollisionObject>(mGameObjects[k]);

            if (gObj1 && gObj2) {
                Rect g1Rect = gObj1->GetBounds();
                Rect g2Rect = gObj2->GetBounds();

                if (!(g1Rect.topLeft.x > g2Rect.bottomRight.x ||
                    g1Rect.topLeft.y < g2Rect.bottomRight.y ||
                    g1Rect.bottomRight.x < g2Rect.topLeft.x ||
                    g1Rect.bottomRight.y > g2Rect.topLeft.y)) {
                    gObj1->CollisionEnter(gObj2);
                    gObj2->CollisionEnter(gObj1);
                }
            }
        }
    }
}


void GameEngine::renderObjects(GameContext *context) {
    // Renders objects to the background.
    for (std::shared_ptr<GameObject> gObj: mGameObjects) {
        std::shared_ptr<GraphicsObject> gObj1 = std::dynamic_pointer_cast<GraphicsObject>(gObj);
        if (gObj1) {
            if (gObj1->isBackground) {
                gObj1->RenderBackground(context);
            }
            else {
                gObj1->RenderForeground(context);
            }
        }
    }
}


/**
 * @method Run
 * @arguments None
 * @description Gives control to the game engine. Will not return until the game window is closed or
 * all objects have been destroyed.
 */
void GameEngine::Run() {
    GameContext *context;
    mObjectSize = 0;

    while (true)  // window is open
    {
        // 0. Remove any objects that are now dead
        cleanupDeadGameObjects();

        // 1. Activate and initialize any objects added during the last frame
        for (std::shared_ptr<GameObject> gObj: addedGameObjects) { mGameObjects.push_back(gObj); }
        addedGameObjects.clear();

        // 2. Process events
        bool shouldClose = ProcessEvents(context);
        if (shouldClose) { break; }

        // 3. Update game objects
        for (std::shared_ptr<GameObject> gObj: mGameObjects) { gObj->Update(context); }

        // 4. Process collision events
        processCollisions();

        // 5. Late updates
        for (std::shared_ptr<GameObject> gObj: mGameObjects) { gObj->LateUpdate(context); }

        // Clear window
        mWindow->clear(sf::Color::Black);

        // 6. Render background
        // 7. Render foreground
        renderObjects(context);

        // Actually render to window
        mWindow->display();
    }
}

}  // namespace CMPUT350



