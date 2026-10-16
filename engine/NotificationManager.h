#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <unordered_map>
#include <cassert>
#include "EngineView.h"
#include "GameObject.h"

namespace CMPUT350 {

class NotificationManager {
public:
    void Register(std::weak_ptr<GameObject> object, const std::string& key);
    void Unregister(std::weak_ptr<GameObject> object, const std::string& key);
    void Notify(const std::string& message);

    auto KeyLocation(const std::string& key) { return mListeners.find(key); }
private:
    std::unordered_map<std::string, std::vector<std::weak_ptr<GameObject>>> mListeners;
};

}  // namespace CMPUT350

#endif  // NOTIFICATIONMANAGER_H