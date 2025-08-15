#include "NotiLib.hpp"
// Based off of Lars, "NotificationLib" (https://github.com/larsl2005/GTAG-NotificationLib)
// Lib base from Pubert, "GUIManager" (Discord = pubertcs, GitHub = Pubert-CS)
// Made By Lmko/Ossuary (KawaiiClique)
NotiLib& NotiLib::Instance() {
    static NotiLib instance;
    return instance;
}

NotiLib::NotiLib()
        : initialized(false),
          notifInstance(nullptr),
          notifText(nullptr),
          notificationDecayTime(150),
          decayCounter(0),
          isEnabled(true) {
    BNM_LOG_INFO(BNM_OBFUSCATE("[Kawaii] | Notification Lib Started! | [+]"));//You can delete this if you want
}

void NotiLib::Init(Transform* cameraTransform, TextAnchor dockPos, Font* customFont) {
    NotiLib& self = Instance();
    if (self.initialized) return;
    self.initialized = true;

    self.notifInstance = (GameObject*)GameObject::GetClass().CreateNewObjectParameters(CreateMonoString(O("NotifLib")));

    Canvas* canvas = (Canvas*)self.notifInstance->AddComponent(Canvas::GetType());
    canvas->SetRenderMode(RenderMode::WorldSpace);

    RectTransform* notifTransform = (RectTransform*)self.notifInstance->GetComponent(RectTransform::GetType());

    Font* fontToUse = customFont;
    if (!customFont || !customFont->Alive()) {
        fontToUse = (Font*)Resources::GetBuiltinResource(Font::GetType(), "Arial.ttf");
    }

    self.notifText = (Text*)self.notifInstance->AddComponent(Text::GetType());

    Material* guiMaterial = (Material*)Material::GetClass().CreateNewObjectParameters(Shader::Find("GUI/Text Shader"));

    notifTransform->SetParent(cameraTransform, false);
    self.notifText->SetFont(fontToUse);
    notifTransform->SetLocalEulerAngles(Vector3::zero);
    notifTransform->SetSizeDelta(Vector2(300.0f, 250.0f));
    notifTransform->SetLocalPosition(Vector3(-0.1f, -0.3297f, 1.6f));
    notifTransform->SetLocalScale(Vector3(0.005f, 0.005f, 0.005f));

    self.notifText->SetMaterial(guiMaterial);

    CanvasScaler* canvasScaler = (CanvasScaler*)self.notifInstance->AddComponent(CanvasScaler::GetType());
    canvasScaler->SetDynamicPixelsPerUnit(65.f);
    self.notifText->SetFontStyle(FontStyle::Bold);
    self.SetDock(dockPos);

    self.notifText->SetText("");
    self.notifications.clear();
    self.decayCounter = 0;
    self.previousNotification.clear();
}

void NotiLib::Destroy() {
    if (!initialized) return;
    initialized = false;

    if (notifInstance) {
        GameObject::Destroy(notifInstance);
        notifInstance = nullptr;
    }
}

void NotiLib::SetText(const std::string& text) {
    notifText->SetText(text);
}

void NotiLib::SetDock(TextAnchor dockPos) {
    notifText->SetAlignment((TextAnchor)dockPos);
}

void NotiLib::Update() {
    NotiLib& self = Instance();
    if (!self.initialized || !self.isEnabled) return;

    if (!self.notifications.empty()) {
        self.decayCounter++;
        if (self.decayCounter > self.notificationDecayTime) {
            self.notifications.pop_front();
            self.decayCounter = 0;

            std::string newText;
            for (const auto& line : self.notifications) {
                newText += line + "\n";
            }
            self.SetText(newText);
        }
    }
}

void NotiLib::SendNotification(const std::string& notification) {
    NotiLib& self = Instance();
    if (!self.isEnabled) return;

    std::string notif = notification;
    if (notif.find('\n') == std::string::npos) {
        notif += "\n";
    }
    self.notifications.push_back(notif);
    self.previousNotification = notif;

    std::string newText;
    for (const auto& line : self.notifications) {
        newText += line + "\n";
    }
    self.SetText(newText);
}

void NotiLib::ClearAllNotifications() {
    NotiLib& self = Instance();
    self.notifications.clear();
    self.SetText("");
}

void NotiLib::ClearPastNotifications(int amount) {
    NotiLib& self = Instance();
    if (amount <= 0 || amount >= (int)self.notifications.size()) {
        ClearAllNotifications();
        return;
    }
    for (int i = 0; i < amount; ++i) {
        self.notifications.pop_front();
    }
    std::string newText;
    for (const auto& line : self.notifications) {
        newText += line + "\n";
    }
    self.SetText(newText);
}

void NotiLib::SetEnabled(bool enabled) {
    NotiLib& self = Instance();
    self.isEnabled = enabled;
}

bool NotiLib::GetEnabled() const {
    return isEnabled;
}

const std::string& NotiLib::GetPreviousNotification() const {
    return previousNotification;
}
