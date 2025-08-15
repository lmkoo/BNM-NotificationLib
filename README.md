# BNM-NotificationLib
NotificationLib port from Lars's Gorilla Tag Lib for C++ using BNM.
--

# Usage for hooks
```cpp
NotiLib* noti;
void new_Awake(void* instance) {
    noti = new NotiLib();
    noti->Init(GameObject::Find("Main Camera")->GetTransform(), TextAnchor::MiddleLeft, nullptr);
}

void new_LateUpdate(void* instance) {
    noti->Update();
}
```

# Notif Usage
```cpp
NotiLib::SendNotification("Testtest"); //Sends a notification.
NotiLib::ClearAllNotifications(); //Clears all notifications.
NotiLib::ClearPastNotifications(2); //Clears a certain amount of notifications.
NotiLib::SetEnabled(true); //Used to turn off and on the notifications with a button.
```
--
# Dependencies

- [BNMResolve](https://github.com/Livku2/BNMResolve)
- [BNM-Android](https://github.com/ByNameModding/BNM-Android)

--
This code is allowed to be used by anyone
