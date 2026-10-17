#include "NotificationManager.h"
#include <iostream>

namespace CMPUT350 {
void NotificationManager::Register(std::weak_ptr<GameObject> object,
                                   const std::string &notification) {
    // If the notification already exists, add the object to it. If not, add a new notification
    if (mListeners.contains(notification)) {
        mListeners.insert({notification, {object}});
    } else {
        mListeners[notification].insert(object);
    }
}

void NotificationManager::Unregister(std::weak_ptr<GameObject> object,
                                     const std::string &notification) {
    // Check that the notification exists, then remove the object
    if (mListeners.contains(notification)) {
        mListeners[notification].extract(object);
    }
}

void NotificationManager::Notify(const std::string &notification) {
    // Notify all GameObjects that have registered for the notification
    if (mListeners.contains(notification)) {
        auto registeredObjects = mListeners[notification];

        for (auto gObj : registeredObjects) {
            auto shared = gObj.lock();

            if (shared != nullptr) {
                shared->ReceiveNotification(notification);
            }
        }
    }
};

void NotificationManager::Clean() {
    // loop over notification sets
    auto notificationIter = mListeners.begin();
    while (notificationIter != mListeners.end()) {
        auto notification = notificationIter++;  // take pre-increment so that it's safe to erase it

        // loop over objects
        auto& registeredObjects = (*notification).second;
        auto gameObjectIter = registeredObjects.begin();

        while (gameObjectIter != registeredObjects.end()) {
            auto gameObject = gameObjectIter++;  // take pre-increment so that it's safe to erase it

            // erase if expired
            if (gameObject->expired()) {
                registeredObjects.erase(gameObject);
            }
        }

        // erase if empty
        if (registeredObjects.empty()) {
            mListeners.erase(notification);
        }
    }
}

}  // namespace CMPUT350
