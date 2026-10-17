#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <set>
#include <unordered_map>

#include "EngineView.h"
#include "GameObject.h"

namespace CMPUT350 {

class NotificationManager {
public:
    bool IsRegistered(std::weak_ptr<GameObject> object, const std::string &key);
    void Register(std::weak_ptr<GameObject> object, const std::string &key);
    void Unregister(std::weak_ptr<GameObject> object, const std::string &key);
    void Notify(const std::string &message);

private:
    std::unordered_map<std::string, std::set<std::weak_ptr<GameObject>, std::owner_less<>>> mListeners = {};
    void Clean();

    friend class GameEngine;
};

}  // namespace CMPUT350

#endif  // NOTIFICATIONMANAGER_H
