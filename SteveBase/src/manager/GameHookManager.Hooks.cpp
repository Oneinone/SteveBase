#include <GlobalDefines.hpp>
#include <manager/GameHookManager.hpp>

#include <Interface.hpp>
#include <Singleton.hpp>

#include <assets/Fonts.hpp>
#include <hook/index.hpp>
#include <manager/DrawManager.hpp>
#include <manager/FontManager.hpp>
#include <manager/StateManager.hpp>
#include <maths/ViewMatrix.hpp>
#include <source_engine/index.hpp>

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/dx9/imgui_impl_dx9.h>
#include <vendor/vmthook/VMTHooks.h>

#include <hook/AutoPistol.hpp>

#include <windows.h>
#include <d3d9.h>

// ReSharper disable All
namespace SteveBase::Manager {
    using namespace Assets;
    using namespace SourceEngine::Define;
    using namespace SourceEngine::Structure;
    using namespace SourceEngine::Virtual;
    using namespace Utility;

    decltype(GameHookManager::interfaceHookMap) GameHookManager::interfaceHookMap {
        HookInterface<IBaseClientDLL> {
            Hook<36>("IBaseClientDLL::FrameStageNotify", ActionStdCall<ClientFrameStage> { [](ClientFrameStage stage) {
                static auto fn = GetHookForInterface<IBaseClientDLL>().GetMethod<ActionStdCall<ClientFrameStage>>(36);
                fn(stage);
            }}),

            Hook<77>("IBaseClientDLL::ScreenSizeChanged", ActionStdCall<int, int> { [](int oldWidth, int oldHeight) {
                static auto fn = GetHookForInterface<IBaseClientDLL>().GetMethod<ActionStdCall<int, int>>(77);
                fn(oldWidth, oldHeight);
                FontManager::ResetFont();
            }})
        },

        HookInterface<IClientModeShared> {
            Hook<18>("IClientModeShared::OverrideView", ActionStdCall<CViewSetup *> { [](CViewSetup *setup) {
                static auto fn = GetHookForInterface<IClientModeShared>().GetMethod<ActionStdCall<CViewSetup *>>(18);
                fn(setup);
            }}),
            Hook<24>("IClientModeShared::CreateMove", FuncStdCall<bool(float, CUserCmd *)> { [](float inputSampleTime, CUserCmd *cmd) {
                static auto fn = GetHookForInterface<IClientModeShared>().GetMethod<FuncStdCall<bool(float, CUserCmd *)>>(24);
                
                PVOID _ebp;
                __asm mov _ebp, ebp;
                bool& sendPacket = *(bool*)(*(PDWORD)_ebp - 0x1C);
                

                // prehook
                {
                    // invalid command
                    if (cmd->GetCommandNumber() == 0) return false;
                }

                auto ret = fn(inputSampleTime, cmd);
                if (cmd->GetCommandNumber() == 0) goto exit; // invalid command

                // posthook
                {
                    if (!Get<IEngineClient>()->IsConnected() || !Get<IEngineClient>()->IsInGame()) {
                        goto exit;
                    }

                    auto localPlayer = Get<IClientEntityList>()->GetLocalPlayer();
                    CBaseCombatWeapon *localActiveWeapon = nullptr;

                    if (localPlayer != nullptr) {
                        localActiveWeapon = localPlayer->GetActiveWeapon();
                    }

                    GetSingleton<Hook::AutoPistol>()->CreateMove(cmd, { localPlayer, localActiveWeapon });
                    GetSingleton<Hook::BunnyHop>()->CreateMove(cmd, localPlayer);
                    GetSingleton<Hook::RadarSpotted>()->CreateMove(localPlayer);
                    GetSingleton<Hook::ScopeCrosshair>()->CreateMove({ localPlayer, localActiveWeapon });
                    GetSingleton<Hook::ShowRank>()->CreateMove(cmd);
                }
            exit:
                return ret;
            }})
        },
        HookInterface<IDirect3DDevice9> {
            Hook<16>(&IDirect3DDevice9::Reset, FuncStdCall<HRESULT(IDirect3DDevice9 *, D3DPRESENT_PARAMETERS *)> { [](IDirect3DDevice9 *device, D3DPRESENT_PARAMETERS *pp) {
                static auto fn = GetHookForInterface<IDirect3DDevice9>().GetMethod<FuncStdCall<HRESULT(IDirect3DDevice9 *, D3DPRESENT_PARAMETERS*)>>(16);

                if (!DrawManager::IsInitialized()) {
                    return fn(device, pp);
                }
                // prehook
                {
                    ImGui::GetIO().MouseDrawCursor = StateManager::IsMenuActivated();
                    ImGui_ImplDX9_InvalidateDeviceObjects();
                }
                auto ret = fn(device, pp);
                // posthook
                {
                    ImGui_ImplDX9_CreateDeviceObjects();
                }
                return ret;
            }}),
            Hook<42>(&IDirect3DDevice9::EndScene, FuncStdCall<HRESULT(IDirect3DDevice9 *)> { [](IDirect3DDevice9 *device) {
                static auto fn = GetHookForInterface<IDirect3DDevice9>().GetMethod<FuncStdCall<HRESULT(IDirect3DDevice9 *)>>(42);

                // prehook
                {
                    if (!DrawManager::IsInitialized()) {
                        ImGui_ImplDX9_Init(GetGameWindowHandle(), device);
                        DrawManager::SetInitialized(true);
                    }
                    if (StateManager::IsMenuActivated()) {
                        ImGui::GetIO().MouseDrawCursor = StateManager::IsMenuActivated();

                        // Credit: malaka01
                        // https://www.unknowncheats.me/forum/1384463-post21.html
                        DWORD renderStateColorWrite;
                        device->GetRenderState(D3DRS_COLORWRITEENABLE, &renderStateColorWrite);
                        device->SetRenderState(D3DRS_COLORWRITEENABLE, -1); // wtf microsoft why no true/false flags but 0xffffffff?
                        ImGui_ImplDX9_NewFrame();
                        {
                            DrawManager::Render();
                        }
                        ImGui::Render();
                        device->SetRenderState(D3DRS_COLORWRITEENABLE, renderStateColorWrite);
                    }
                }

                return fn(device);
            }})
        },
        HookInterface<IPanel> {
            Hook<41>("IPanel::PaintTraverse",
                ActionFastCall<unsigned int, bool, bool> { [](void *ecx, void *edx, unsigned vguiPanel, bool forceRepaint, bool allowForce)  {
                    static unsigned matSystemTopPanel = -1;
                    static auto fn = GetHookForInterface<IPanel>().GetMethod<ActionFastCall<unsigned int, bool, bool>>(41);

                    fn(ecx, edx, vguiPanel, forceRepaint, allowForce);

                    if (!FontManager::IsInitialized()) {
                        FontManager::Init();
                    }

                    if (matSystemTopPanel == -1 && strcmp(Get<IPanel>()->GetName(vguiPanel), text("MatSystemTopPanel")) == 0) {
                        matSystemTopPanel = vguiPanel;
                    }

                    if (vguiPanel != matSystemTopPanel) {
                        return;
                    }

                    GetSingleton<Hook::Banner>()->OnPaintTraverse();
                    GetSingleton<Hook::DebugInformation>()->OnPaintTraverse();
                }
            })
        },

        HookInterface<IPrediction> {
            Hook<14>("IPrediction::InPrediction", FuncFastCall<bool()> { [](void *ecx, void *edx) {
                static auto fn = GetHookForInterface<IPrediction>().GetMethod<FuncFastCall<bool()>>(14);
                return fn(ecx, edx);
            }})
        },

        HookInterface<IStudioRender> {
            Hook<9>("IStudioRender::BeginFrame", ActionFastCall<> { [](void *ecx, void *edx) {
                static auto fn = GetHookForInterface<IStudioRender>().GetMethod<ActionFastCall<>>(9);

                fn(ecx, edx);
                GetSingleton<Hook::GlowRender>()->BeginFrame();
            }})
        },

        HookInterface<ISurface> {
            Hook<82>("ISurface::PlaySound", ActionFastCall<const char *> { [](void *ecx, void *edx, const char *fileName) {
                static auto fn = GetHookForInterface<ISurface>().GetMethod<ActionFastCall<const char *>>(82);

                fn(ecx, edx, fileName);
            }})
        },

        HookInterface<IVModelRender> {
            Hook<21>("IVModelRender::OnDrawModelExecute",
                ActionFastCall<void *, const DrawModelState_t &, const ModelRenderInfo &, ViewMatrix *> ( [](void *ecx, void *edx, void *ctx, const DrawModelState_t &state, const ModelRenderInfo &pInfo, ViewMatrix *pCustomBoneToWorld) {
                    static auto fn = GetHookForInterface<IVModelRender>().GetMethod<ActionFastCall<void *, const DrawModelState_t &, const ModelRenderInfo &, ViewMatrix *>>(21);
                    fn(ecx, edx, ctx, state, pInfo, pCustomBoneToWorld);
                })
            )
        },
    };

}