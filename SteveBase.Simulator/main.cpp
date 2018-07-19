#include <GlobalDefines.hpp>

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/dx9/imgui_impl_dx9.h>

#include "manager/VariableManager.hpp"
#include "manager/DrawManager.hpp"
#include "utility/SystemUtility.hpp"
#include "utility/GameUtility.hpp"
#include "manager/StateManager.hpp"
#include "manager/I18NManager.hpp"
#include "maths/Random.hpp"
#include "utility/Logger.hpp"
#include "misc/ZLib.hpp"
#include <assets/hitsound/hitmarker.hpp>
#include "assets/hitsound/quake.hpp"

#define TINYSOUND_IMPLEMENTATION
#include "vendor/tinyheaders/tinysound.h"

#include <windows.h>
#include <d3d9.h>
#include <tchar.h>


using namespace SteveBase::Manager;
using namespace SteveBase::Utility;

// Data
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp;

extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (GetAsyncKeyState(VK_INSERT) & 0x0001) { // if insert is pressed
		StateManager::m_isMenuActivated = !StateManager::m_isMenuActivated; // flip the menu state

		if (!StateManager::IsMenuActivated()) { // if menu is closed
			VariableManager::SaveConfig();
		}
	}

	if (ImGui_ImplDX9_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg) {
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	AllocConsole() ? freopen("CONOUT$", "w", stdout) : 0;
	// Create application window
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL, _T("SteveBase Menu Simulator"), NULL };
	RegisterClassEx(&wc);
	HWND hwnd = CreateWindow(_T("SteveBase Menu Simulator"), _T("SteveBase Menu Simulator"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	LPDIRECT3D9 pD3D;
	if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
		UnregisterClass(_T("SteveBase Menu Simulator"), wc.hInstance);
		return 0;
	}
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Create the D3DDevice
	if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0) {
		pD3D->Release();
		UnregisterClass(_T("SteveBase Menu Simulator"), wc.hInstance);
		return 0;
	}

	// Setup ImGui binding
	
	ImGui_ImplDX9_Init(hwnd, g_pd3dDevice);
	
	bool show_test_window = true;
	ImVec4 clear_col = ImColor(114, 144, 154);

	{
		GameUtility::SetHackDirectory(SystemUtility::ProduceModulePath(nullptr));
		VariableManager::Init();
		DrawManager::Init();
		StateManager::m_isMenuActivated = true;
	}

    tsContext* ctx = tsMakeContext(GetConsoleWindow(), 22050, 15, 5, 0);
    tsLoadedSound loaded;
    SteveBase::Assets::Hitsound::QuakeHitsound h;

    tsReadMemWAV(h.GetHitsound(), &loaded);
    
    tsPlayingSound playing_sound = tsMakePlayingSound(&loaded);
    playing_sound.volume0 = playing_sound.volume1 = 0.5f;

	// Main loop
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		
		ImGui_ImplDX9_NewFrame();

		// Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);

		// Show the simulated hack menu
		{
			DrawManager::Render();
            tsMix(ctx);
		}

		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_col.x*255.0f), (int)(clear_col.y*255.0f), (int)(clear_col.z*255.0f), (int)(clear_col.w*255.0f));
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
		// Rendering
		if (g_pd3dDevice->BeginScene() >= 0) {
			ImGui::Render();
			g_pd3dDevice->EndScene();
		}
		g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	}

	ImGui_ImplDX9_Shutdown();
	if (g_pd3dDevice) g_pd3dDevice->Release();
	if (pD3D) pD3D->Release();
    tsFreeSound(&loaded);

	
	UnregisterClass(_T("SteveBase Menu Simulator"), wc.hInstance);

	return 0;
}
