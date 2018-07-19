#include <GlobalDefines.hpp>
#include <hook/DebugInformation.hpp>

#include <assets/Fonts.hpp>
#include <manager/DrawManager.hpp>

#include <source_engine/index.hpp>

#include <vendor/hash/hash.h>
#include <vendor/XorStr/XorStr.h>
#include <vendor/ggformat/ggformat.h>

namespace SteveBase::Hook {
    using namespace SourceEngine::Define;
    using namespace SourceEngine::Structure;
    using namespace SourceEngine::Virtual;


#define INDENT "    "
    void DebugInformation::OnPaintTraverse() {
        if (!DynamicVariable(misc.drawdebuginfo).Get<bool>())
            return;

        int x, y;

        Get<ISurface>()
            ->SetTextFont<Assets::Fonts::ESP::Regular>()
            ->SetTextPos(x = DrawManager::GetScreenSize().Width() / 2 - 30, y = 10)
            ->PrintText(text("SteveBase Debug Mode"));
        Get<ISurface>()
            ->SetTextPos(x, y += 12)
            ->PrintText(text(INDENT "-> CGlobalVarsBase:"));
        Get<ISurface>()
            ->SetTextPos(x, y += 12)
            ->PrintText(ggformat_to_string(
                text(INDENT INDENT "-> Real Time: {0}"),
                Get<CGlobalVarsBase>()->GetRealTime()
            ));
        Get<ISurface>()
            ->SetTextPos(x, y += 12)
            ->PrintText(ggformat_to_string(
                text(INDENT INDENT "-> Frame Count: {0}"),
                Get<CGlobalVarsBase>()->GetFrameCount()
            ));
        Get<ISurface>()
            ->SetTextPos(x, y += 12)
            ->PrintText(ggformat_to_string(
                text(INDENT INDENT "-> Current Time: {0}"),
                Get<CGlobalVarsBase>()->GetCurrentTime()
            ));
        Get<ISurface>()
            ->SetTextPos(x, y += 12)
            ->PrintText(ggformat_to_string(
                text(INDENT INDENT "-> Frame Time: {0}"),
                Get<CGlobalVarsBase>()->GetFrameTime()
            ));

        if (Get<IEngineClient>()->IsConnected() && Get<IEngineClient>()->IsInGame()) {
            auto localPlayer = Get<IClientEntityList>()->GetLocalPlayer();

            Get<ISurface>()
                ->SetTextPos(x, y += 12)
                ->PrintText(ggformat_to_string(
                    text(INDENT "-> LocalPlayer: 0x{x}"),
                    (uintptr_t)localPlayer
                ));
            Get<ISurface>()
                ->SetTextPos(x, y += 12)
                ->PrintText(ggformat_to_string(
                    text(INDENT INDENT "-> Origin: {0}"),
                    localPlayer->GetOrigin().ToString()
                ));
            Get<ISurface>()
                ->SetTextPos(x, y += 12)
                ->PrintText(ggformat_to_string(
                    text(INDENT INDENT "-> Angle: {0}"),
                    localPlayer->GetRotation().ToString()
                ));
            Get<ISurface>()
                ->SetTextPos(x, y += 12)
                ->PrintText(ggformat_to_string(
                    text(INDENT INDENT "-> Eye Position: {0}"),
                    localPlayer->GetEyePosition().ToString()
                ));
            Get<ISurface>()
                ->SetTextPos(x, y += 12)
                ->PrintText(ggformat_to_string(
                    text(INDENT INDENT "-> Eye Angle: {0}"),
                    localPlayer->GetEyeAngle().ToString()
                ));
            Get<ISurface>()
                ->SetTextPos(x, y += 12)
                ->PrintText(ggformat_to_string(
                    text(INDENT INDENT "-> Aim Punch: {0}"),
                    localPlayer->GetAimPunchAngle().ToString()
                ));
            Get<ISurface>()
                ->SetTextPos(x, y += 12)
                ->PrintText(ggformat_to_string(
                    text(INDENT INDENT "-> View Punch: {0}"),
                    localPlayer->GetViewPunchAngle().ToString()
                ));

            CGameTrace pTrace;
            Ray pRay;

            auto eye = localPlayer->GetEyePosition();
            auto vDirection = eye + localPlayer->GetEyeAngle().GetUnitForwardVector().Normalize() * 8192;
            // and now direction focusing on eye, with scan maximum of 8192 HU

            pRay.Init(eye, vDirection); // straight line

            Get<IEngineTrace>()->TraceRay(pRay, ContentMask::EveryThing, &filter, &pTrace);

            Get<ISurface>()
                ->SetTextPos(x, y += 12)
                ->PrintText(ggformat_to_string(
                    text(INDENT INDENT "-> Tracing End Position: {0}"),
                    pTrace.endpos.ToString()
                ));
            if (pTrace.m_pEnt != nullptr && pTrace.m_pEnt != Get<IClientEntityList>()->GetClientEntity(0)) {
                Get<ISurface>()
                    ->SetTextPos(x, y += 12)
                    ->PrintText(ggformat_to_string(
                        text(INDENT INDENT "-> Tracing Entity: {0}"),
                        pTrace.m_pEnt->GetNetworkable()->GetClientClass()->GetName()
                    ));
                auto model = pTrace.m_pEnt->GetRenderable()->GetModel();
                if (model != nullptr) {
                    Get<ISurface>()
                        ->SetTextPos(x, y += 12)
                        ->PrintText(text(INDENT INDENT INDENT "-> Model"));

                    Get<ISurface>()
                        ->SetTextPos(x, y += 12)
                        ->PrintText(ggformat_to_string(
                            text(INDENT INDENT INDENT INDENT "-> Address: {x}"),
                            (uintptr_t)model
                        ));

                    Get<ISurface>()
                        ->SetTextPos(x, y += 12)
                        ->PrintText(ggformat_to_string(
                            text(INDENT INDENT INDENT INDENT "-> Name: {0}"),
                            model->GetName()
                        ));
                }
            }
        } else {
            Get<ISurface>()
                ->SetTextPos(x, y += 12)
                ->PrintText(text(INDENT "-> LocalPlayer: Not Connected"));
        }
    }
}
