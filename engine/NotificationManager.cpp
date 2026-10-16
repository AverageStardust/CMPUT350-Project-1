#include "NotificationManager.h"

namespace CMPUT350 {

void NotificationManager::Register(std::weak_ptr<GameObject> object, const std::string& key) {
    if (KeyLocation(key) == mListeners.end()) {
        mListeners.insert({key, std::vector<std::weak_ptr<GameObject>>{object}});
    }
    else {
        mListeners[key].push_back(object);
    }
}

void NotificationManager::Unregister(std::weak_ptr<GameObject> object, const std::string& key) {
    assert(KeyLocation(key) != mListeners.end());

    mListeners.erase(key);
}

void NotificationManager::Notify(const std::string& message) {
    assert(KeyLocation(message) != mListeners.end());

    std::vector<std::weak_ptr<GameObject>> registeredObjects = mListeners[message];

    for (std::vector<std::weak_ptr<GameObject>>::iterator i = registeredObjects.begin(); i != registeredObjects.end(); ++i) {
        auto shared = i->lock();
        if (shared) {
            registeredObjects.erase(i);
        }
        else {
            shared->ReceiveNotification(message);
        }
    }
};

}  // namespace CMPUT350