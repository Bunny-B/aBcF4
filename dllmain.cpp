// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "pch.h"
#include "MinHook.h"
#include "hookings.hpp"
#include "Pointers.hpp"


typedef HRESULT(WINAPI* CreateSwapChainPtr)(IDXGIFactory*, IUnknown*, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**);

CreateSwapChainPtr originalCreateSwapChain = nullptr;

HRESULT WINAPI MyCreateSwapChain(IDXGIFactory* factory, IUnknown* device, DXGI_SWAP_CHAIN_DESC* desc, IDXGISwapChain** swapChain)
{
	// Call the original function
	HRESULT result = originalCreateSwapChain(factory, device, desc, swapChain);

	if (SUCCEEDED(result) && swapChain && *swapChain)
	{
		// Log the address of the IDXGISwapChain instance
		LOG("Passed check");
		LOG( "IDXGISwapChain address: " << hex(*swapChain));
	}
	else
	{
		LOG("Failed to create swap chain");
	}

	return result;
}
typedef HRESULT(WINAPI* Present1Ptr)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Present1Ptr originalPresent1 = nullptr;
HRESULT WINAPI MyPresent1(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	// Log information or do any pre-processing
	LOG("MyPresent1 hook called.");

	// Call the original function
	HRESULT result = originalPresent1(pSwapChain, SyncInterval, Flags);

	// Log information or do any post-processing
	LOG("Original Present1 returned: " << result);

	return result;
}

void HookFunction()
{
	MH_Initialize();
	LOG("Hooking");//only log that get logged
	// Get the base address of dxgi.dll
	HMODULE hDxgiDll = GetModuleHandle(L"dxgi.dll");

	if (hDxgiDll)
	{
		LOG("dxgi.dll found");
		// Calculate the address of Present1 using the base address and offset
		Present1Ptr present1Address = reinterpret_cast<Present1Ptr>(reinterpret_cast<uintptr_t>(hDxgiDll) + 0x68DC0);


		MH_Initialize();
		MH_CreateHook(present1Address, &MyPresent1, reinterpret_cast<void**>(&originalPresent1));
		MH_EnableHook(MH_ALL_HOOKS);
		LOG("Present1 hooked");
	}
}


BOOL APIENTRY DllMain( HMODULE hmod,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	while (!GetModuleHandleW(L"ntdll.dll"))
		std::this_thread::sleep_for(std::chrono::seconds(5));


    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		//disable thread calls
        DisableThreadLibraryCalls(hmod);

        g_globals.g_hmodule = hmod;
		//create handle to main thread
        g_globals.g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
            {
				//g_pointers->m_hwnd = FindWindowA(("Battlefield 4"), NULL);
				g_globals.g_hwnd = FindWindowA(("Battlefield 4"), NULL);
				while (!g_globals.g_hwnd)
					std::this_thread::sleep_for(std::chrono::seconds(1));


				AllocConsole();
				freopen("CONOUT$", "w", stdout); // Redirect stdout to the console

				//set console title
				SetConsoleTitleA("aBcF4");
				try
				{
					LOG("Injected");
					HookFunction();

				//	auto pointers_instance = std::make_unique<pointers>(); LOG("Pointers Init->");
					LOG("Pointers Initiated");
					//auto RendererInstance = std::make_unique<renderer>(); LOG("Renderer Init->");
					//auto hooking_instance = std::make_unique<hooking>(); LOG(("Hooking Init->"));

					//g_hooking->enable();
					LOG("Hooks Initiate");


					while (g_globals.g_running)
					{
						if (GetAsyncKeyState(VK_END) & 0x8000) {
							LOG("UNINJECTED");
							g_globals.g_running = false;

						}

						Sleep(75);
					}
				//	pointers_instance.reset(); LOG(("<- Reset Pointers"));
					//RendererInstance.reset(); LOG(("<- Reset Renderer"));

				}
				catch (std::exception const& ex)
				{
					MessageBoxA(nullptr, ex.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
				}

				//free console and exit thread
				FreeConsole();
				//console is not closed
				//close console
				fclose(stdout);




				//free handle to main thread
				CloseHandle(g_globals.g_main_thread);
				//free library and exit thread
				FreeLibraryAndExitThread(g_globals.g_hmodule, 0);
        }, nullptr, 0, nullptr);


    }
    return TRUE;
}

