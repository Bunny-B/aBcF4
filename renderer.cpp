#include "pch.h"

#include "renderer.hpp"
#include "Pointers.hpp"
#include "gui.hpp"


#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_internal.h"

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



renderer::renderer() :

	m_dxgi_swapchain(*g_pointers->m_swapchain)
{
	LOG("renderer Ctor");//dont even get called

	void* d3d_device{};
	if (SUCCEEDED(m_dxgi_swapchain->GetDevice(__uuidof(ID3D11Device), &d3d_device)))
	{
		m_d3d_device.Attach(static_cast<ID3D11Device*>(d3d_device));
	}
	else
	{
		throw std::runtime_error("Failed to get D3D device.");
	}
	m_d3d_device->GetImmediateContext(m_d3d_device_context.GetAddressOf());


	ImGui_ImplDX11_Init(m_d3d_device.Get(), m_d3d_device_context.Get());
	ImGui_ImplWin32_Init(g_pointers->m_hwnd);


	g_renderer = this;
}

renderer::~renderer()
{
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();

	g_renderer = nullptr;
}

void renderer::on_present()
{

	if (g_gui.m_opened)
	{
		ImGui::GetIO().MouseDrawCursor = true;
		ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
	}
	else
	{
		ImGui::GetIO().MouseDrawCursor = false;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (ImGui::IsKeyPressed(static_cast<ImGuiKey>(ImGuiKey_Insert), false))
		g_gui.m_opened ? g_gui.m_opened = false : g_gui.m_opened = true;

	if (g_gui.m_opened)
	{
		if(ImGui::Begin("test")){

			ImGui::End();
		}
	}
	
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

void renderer::pre_reset()
{
	ImGui_ImplDX11_InvalidateDeviceObjects();
}

void renderer::post_reset()
{
	ImGui_ImplDX11_CreateDeviceObjects();
}

void renderer::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LOG("wndproc");
	//CHINESS
	if (msg == WM_KEYUP && wparam == VK_INSERT)
	{
		//Persist and restore the cursor position between menu instances.
		static POINT cursor_coords{};
		if (g_gui.m_opened)
		{
			GetCursorPos(&cursor_coords);
		}
		else if (cursor_coords.x + cursor_coords.y != 0)
		{
			SetCursorPos(cursor_coords.x, cursor_coords.y);
		}

		g_gui.m_opened ^= true;
	}


	//if (g_gui.m_opened)
	{

		ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
	}
}

