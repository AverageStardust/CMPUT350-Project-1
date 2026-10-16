#include "NotificationManager.h"

namespace CMPUT350 {

void NotificationManager::Register(std::weak_ptr<GameObject> object, const std::string& key) {
    // If the key already exists, add the GameObject to it. If not, add a new key to the mapping
    if (KeyLocation(key) == mListeners.end()) {
        mListeners.insert({key, std::vector<std::weak_ptr<GameObject>>{object}});
    }
    else {
        mListeners[key].push_back(object);
    }
}

void NotificationManager::Unregister(std::weak_ptr<GameObject> object, const std::string& key) {
    // Check that the key exists, then erase it
    assert(KeyLocation(key) != mListeners.end());

    mListeners.erase(key);
}

void NotificationManager::Notify(const std::string& message) {
    // Notify all GameObjects that have registered for the notification specified by message
    if (KeyLocation(message) != mListeners.end()) {
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
    }
};

}  // namespace CMPUT350