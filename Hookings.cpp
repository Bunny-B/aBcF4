#include "pch.h"
#include "hookings.hpp"
#include "Pointers.hpp"
#include "gui.hpp"

hooking::~hooking()
{
	if (m_enabled)
	{
		disable();
	}

	g_hooking = nullptr;
}

LRESULT hooks::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	
	LOG("wndproc");
		if (g_globals.g_running)
		{
			switch (msg)
			{
			case WM_ACTIVATE:
				if (LOWORD(wparam) == WA_INACTIVE) {
					//_log("inactive")
						g_gui.m_opened = false;
						// Window is not active, do not update ImGui state or render ImGui UI.
						return 0;
					}
					break;
					// ...
				}



				g_renderer->wndproc(hwnd, msg, wparam, lparam);
			}
			
			return CallWindowProcW(g_hooking->m_og_wndproc, hwnd, msg, wparam, lparam);

		return NULL;
}

__int64 __fastcall hooks::sub_140821590(__int64 a1, float a2, unsigned __int8 a3)
{
	LOG("sub_140821590"<< std::endl << "a1: " << a1 << std::endl << "a2: " << a2 << std::endl << "a3: " << a3);

	return  g_hooking->get_original<sub_140821590>()(a1,a2,a3);
}
void __fastcall hooks::Screen_Swapchain_Relatedref(__int64 IDXGIAdapter1, __int64 screen, char a3) {
	LOG("Screen_Swapchain_Relatedref");
	LOG("Screen : " << hex(screen));
	return  g_hooking->get_original<Screen_Swapchain_Relatedref>()(IDXGIAdapter1, screen, a3);

}
hooking::hooking() 
	:m_swapchain_hook(g_pointers->m_swapchain, hooks::swapchain_num_funcs)
{
	m_swapchain_hook.hook(hooks::swapchain_present_index, &hooks::swapchain_present);
	m_swapchain_hook.hook(hooks::swapchain_resizebuffers_index, &hooks::swapchain_resizebuffers);

	// The only instances in that vector at this point should only be the "lazy" hooks
	// aka the ones that still don't have their m_target assigned
	for (auto& detour_hook_helper : m_detour_hook_helpers)
	{
		detour_hook_helper->m_detour_hook->set_target_and_create_hook(detour_hook_helper->m_on_hooking_available());
	}

	//detour_hook_helper::add<hooks::sub_140821590>(("testhook"), g_pointers->sub_140821590);
	//detour_hook_helper::add<hooks::Screen_Swapchain_Relatedref>(("ref"), g_pointers->Screen_Swapchain_Relatedref);

	//detour_hook_helper::add<hooks::swapchain_present_index>(("present"), g_pointers->get_scene_preset);

	
	g_hooking = this;
}

void hooking::enable()
{
	m_swapchain_hook.enable(); //vmt hook

	m_og_wndproc = WNDPROC(SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, LONG_PTR(&hooks::wndproc)));

	for (const auto& detour_hook_helper : m_detour_hook_helpers)
	{
		detour_hook_helper->m_detour_hook->enable();
	}

	MH_ApplyQueued();

	m_enabled = true;
}

void hooking::disable()
{
	m_enabled = false;

	for (const auto& detour_hook_helper : m_detour_hook_helpers)
	{
		detour_hook_helper->m_detour_hook->disable();
	}

	SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_og_wndproc));
	m_swapchain_hook.disable();

	MH_ApplyQueued();

	for (const auto& detour_hook_helper : m_detour_hook_helpers)
	{
		delete detour_hook_helper;
	}
	m_detour_hook_helpers.clear();
}

hooking::detour_hook_helper::~detour_hook_helper()
{
	delete m_detour_hook;
}

void hooking::detour_hook_helper::enable_hook_if_hooking_is_already_running()
{
	if (g_hooking && g_hooking->m_enabled)
	{
		if (m_on_hooking_available)
		{
			m_detour_hook->set_target_and_create_hook(m_on_hooking_available());
		}

		m_detour_hook->enable();
		MH_ApplyQueued();
	}
}
