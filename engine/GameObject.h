#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "EngineView.h"

namespace CMPUT350 {

class GameContext;

class GameObject : public std::enable_shared_from_this<GameObject> {
public:
    virtual ~GameObject() = default;
    virtual void Initialize(GameContext *context);
    virtual void Update(GameContext *context);
    virtual void LateUpdate(GameContext *context);
    virtual void RenderUI(GameContext *context);
    virtual bool IsAlive() const;
    virtual void Kill();
    virtual void ReceiveNotification(const std::string& key);

private:
    EngineView *mEngineView;
};

}  // namespace CMPUT350

#endif  // GAMEOBJECT_H
