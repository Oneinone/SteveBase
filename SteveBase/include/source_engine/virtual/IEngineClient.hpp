#pragma once

#include <maths/EulerAngle.hpp>
#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Virtual {
    using namespace Maths;

    interface IEngineClient extends Misc::ProxiedClass {
        DefineVFunc(GetScreenSize, (int &width, int &height) -> void)(5)(width, height);
        DefineVFunc(GetLocalPlayer, () -> int)(12)();
    private:
        DefineVFunc(GetViewAngles_Raw, (EulerAngle &angle) -> void)(18)(angle);
        DefineVFunc(SetViewAngles_Raw, (EulerAngle &angle) -> void)(19)(angle);
    public:
        DefineVFunc(GetMaxClients, () -> int)(20)();
        DefineVFunc(IsInGame, () -> bool)(26)();
        DefineVFunc(IsConnected, () -> bool)(27)();
        DefineVFunc(IsDrawingLoadingImage, () -> bool)(28)();
        DefineVFunc(IsTakingScreenshot, () -> bool)(92)();
        DefineVFunc(ClientCmd, (const char *cmd) -> void)(108)(cmd);
        DefineVFunc(ClientCmd_Unrestricted, (const char *cmd) -> void)(114)(cmd);

        EulerAngle GetViewAngles() {
            EulerAngle ret;
            GetViewAngles_Raw(ret);
            return ret;
        }

    };
}