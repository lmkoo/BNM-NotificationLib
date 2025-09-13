#pragma once
#include <BNMResolve.hpp>
#include <deque>
#include <string>

using namespace BNM;
using namespace BNM::Structures;
using namespace BNM::Structures::Unity;
using namespace BNM::IL2CPP;

#define O(str) BNM_OBFUSCATE(str)

struct NotiLib {
private:
    bool initialized;
    GameObject* notifInstance;
    Text* notifText;
    std::deque<std::string> notifications;
    int notificationDecayTime;
    int decayCounter;
    bool isEnabled;
    std::string previousNotification;
    static NotiLib& Instance();
public:
    NotiLib();

    void Init(Transform* cameraTransform, TextAnchor dockPos, Font* customFont = nullptr);
    void Destroy();
    void SetText(std::string text);
    void SetDock(TextAnchor dockPos);
    void Update();

    static void SendNotification(std::string notification);
    static void ClearAllNotifications();
    static void ClearPastNotifications(int amount);
    static void SetEnabled(bool enabled);

    bool GetEnabled();
    std::string GetPreviousNotification();
};
