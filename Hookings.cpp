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

hooking::hooking() :
	// Swapchain
	m_swapchain_hook(g_pointers->m_swapchain, hooks::swapchain_num_funcs)
{
	m_swapchain_hook.hook(hooks::swapchain_present_index, &hooks::swapchain_present);
	m_swapchain_hook.hook(hooks::swapchain_resizebuffers_index, &hooks::swapchain_resizebuffers);

	// The only instances in that vector at this point should only be the "lazy" hooks
	// aka the ones that still don't have their m_target assigned
	for (auto& detour_hook_helper : m_detour_hook_helpers)
	{
		detour_hook_helper->m_detour_hook->set_target_and_create_hook(detour_hook_helper->m_on_hooking_available());
	}

	//detour_hook_helper::add<hooks::add_element_to_scene2>(XOR("Scene2"), g_pointers->add_element_to_scene2);
	//detour_hook_helper::add<hooks::get_scene_preset>(XOR("Scene"), g_pointers->get_scene_preset);


	
	g_hooking = this;
}

void hooking::enable()
{
	m_swapchain_hook.enable();
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
