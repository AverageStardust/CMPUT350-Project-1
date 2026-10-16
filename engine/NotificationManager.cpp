#include "NotificationManager.h"

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
    auto i = mListeners.begin();
    while (i != mListeners.end()) {
        auto currentI = i++;  // take pre-increment so that it's safe to erase it

        // loop over objects
        auto registeredObjects = (*i).second;
        auto j = (*i).second.begin();
        while (j != registeredObjects.end()) {
            auto currentJ = j++;  // take pre-increment so that it's safe to erase it

            // erase if expired
            if (currentJ->expired()) {
                registeredObjects.erase(currentJ);
            }
        }

        // erase if empty
        if (registeredObjects.empty()) {
            mListeners.erase(currentI);
        }
    }
}

}  // namespace CMPUT350
