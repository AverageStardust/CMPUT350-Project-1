# CMPUT 350 HW 1

## Team

- Wren Durbano
- Liam Latham

## Controls

Move: A, D
Shoot: Space
Play: 1
Insert Coin: 5
Toggle colliders: 8
Record replay: 9
Run replay: 0

## Implementation
### MathUtils

Three extra structs have been added to MathUtils for the sake of transformations and collisions.

- First, Matrix2, which is a 2x2 matrix used to represent rotation and scaling. This is mostly a support struct for the following.

- Next, Transform2D, which is an aggmented matrix (2x2 matrix + 1x2 vector). It is used to represent all transformations in the game, including translation. A Transform2D can be inverted, combined into one, and applied to Point2D, Line, Circle, Rect, and Quad.

- Last, Quad, which is a quadrilateral with 4 points. Quad is used to represent a rotated rect durring collisions.

Any of the 4 basic shapes, Line, Circle, Rect, and Quad, can run `Intersects()` with eachother. This method will return true if they intersect. It will also write a collision point. For most shapes this collision point is the center of the overlapping area, or some aproximation of that. For intersections with lines, the line is treated as directed, and the collision point returned is the first intersecting point along said line. (Like in the Project 1b discription)

### DrawContext/GraphicsObject

The funtionality of Transform2D far exceeds the requirements for drawing. Thus the following API in the Project discription has been replaced. This was deamed acceptable because it's internal to the engine.

```cpp
private:
    void SetContextOffset(Point2D p);
    void SetContextRotation(float rotation);
    Point2D Transform(Point2D p);
    Point2D ReverseTransform(Point2D p);
    Rect Transform(Rect r); // Rotates rectangle and computes new bounding box after rotation
```

In it's place there is the following API. The implementation of DrawContext has been updated to handle scaling.

```cpp
private:
    Transform2D transform;
```

This transform value is updated before drawing. It's value is derived from the results of `GraphicsObject::GetLocation()` and `GraphicsObject::GetRotation()`. The transform is calculated once per frame for each object.

## Galaga class

The galaga class is implemented as a state machine. It has 4 states, **Wait**, **Spawn**, **Play**, and **Over**.

During **Wait** coins are accepted. Pressing start transitions to the Spawn state. This transition spawns the player.

During **Spawn** enemies are slowly added wave by wave (row by row). Two counters and a cooldown variable are uses to track how many have been spawned, and how long until the next enemy should be spawned. Once all enemies have been spawned the game transitions to the **Play** state. Mostly of the behaviour of the **Play** state is also shared by the **Spawn** stace, since the game can still be played while enemies spawn.

During the **Play** state the player my move and shoot enemeis. Once all enemies have been killed the game transitions back to the Spawn state, and incremeants the level. Dying at any time will decrement the number of lives. Once lives reaches zero, the game transitions to the **Over** state.

During the **Over** state the player can see their score, it transitions back to the **Wait** state after 3 seconds.


## Contributions

Wren
- Galiga class / game loop
- Implement MathUtil
- Implement Transfrom2D
- Implement DrawContext
- Implement Player
- Design Player sprite
- Font rendering
- Implement Bezier
- Update CollisionObject
- Update GraphicsObject
- Update GameObject
- Implement 1b collision logic in GameEngine

Liam
- Implement most of GameEngine
- Implement Enemy
- Design Enemy sprite
- Implement Bullet
- Implement Bezier path following
- Implement EngineView
- Implement NotificationManager
- Update Player
- Update Bullet
- Update Enemy

## Extra Credit
### Game Replays

Replays can be used in game by pressing `9` to record a replay to disk. Later the game can be restarted and the user may press `0` to start replaying that replay.

Replays use fstreams to write and read replay data to a disk. When replays are written timing is stored in frames since the recording start, *not* since when the game started. Reading from a replay will block all manual input to the game until it's over. Reading a replay will restart the framecount of the engine to 0. Replay files are closed when requested in the API, or when GameEngine is deconstructed.

The following API has been added to EngineView to allow for replays.
```cpp
void WriteReplay(std::string path);
void ReadReplay(std::string path);
void FinishWritingReplay();
void FinishReadingReplay();
```

Replays are formatted as a series of lines, each containing a frame number, a scancode, and a up/down boolean. The following is an example replay of the player inserting a coin, pressing start, moving left, and shooting once.
```
0 34 1
2 34 0
32 30 1
35 30 0
70 26 1
152 40 1
156 40 0
162 26 0
```

## Credits
Lerp angle function from user151496 at https://stackoverflow.com/a/14498790

## AI Usage
We did not use AI.
