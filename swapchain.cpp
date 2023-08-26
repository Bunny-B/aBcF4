#include "pch.h"
#include "hookings.hpp"


HRESULT hooks::swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags)
{


	LOG("Present im here");
	if (g_globals.g_running)
	{

		g_renderer->on_present();
	}

	return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_present)>(swapchain_present_index)(this_, sync_interval, flags);
	return NULL;
}
HRESULT hooks::swapchain_resizebuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags)
{
	LOG("Present Resize");

	if (g_globals.g_running)
	{
		g_renderer->pre_reset();

		auto result = g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)
			(this_, buffer_count, width, height, new_format, swapchain_flags);

		if (SUCCEEDED(result))
		{
			g_renderer->post_reset();
		}

		return result;
	}

	return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)
		(this_, buffer_count, width, height, new_format, swapchain_flags);
	return NULL;
}
