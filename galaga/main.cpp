#include "GameEngine.h"
#include "MathUtil.h"
#include "Player.h"
#include "Enemy.h"
#include "Stars.h"

int main()
{
    CMPUT350::GameEngine engine(768, 1024, "Galaga");
    auto player = std::make_shared<Player>(CMPUT350::Point2D(int(768 / 2), 900));
    engine.AddGameObject(player);
    engine.AddGameObject(std::make_shared<Stars>(250, CMPUT350::Rect(0, 0, 768, 1024)));
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            auto enemy = std::make_shared<Enemy>(CMPUT350::Point2D(40 + x * 76, 76 + y * 76));
            engine.AddGameObject(enemy);
        }
    }
    engine.Run();

    return 0;
}
