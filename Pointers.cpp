#include "pch.h"
#include "Pointers.hpp"

pointers::pointers()
{
	memory::batch main_batch;
	main_batch.add(("DX_Renderer"), ("48 8B 0D ? ? ? ? 48 8B 01 FF 50 08 85 C0 75 2D 48 8B 05 ? ? ? ? 48 85 C0 75 1A 48 8B 0D ? ? ? ? 48 8D 15 ? ? ? ?"), [this](memory::handle ptr) {
		m_dxrenderer = ptr.add(0x3).rip().as<DxRenderer*>();
		//	 *(DxRenderer**)OFFSET_DXRENDERER; //0x142738080
		auto dxrenderer = ptr.add(0x3).rip().as<DxRenderer*>();
		LOG(hex(dxrenderer)<< " render");


		const auto screen = dxrenderer->m_pScreen;
		if (!screen) return nullptr;
		LOG(hex(screen) << " screen");
		auto swapchain = screen->m_pSwapChain;
		if (!swapchain) return nullptr;
		LOG(hex(swapchain) << " swapchain");

		m_swapchain = &swapchain;

	});
	auto game_region = memory::module(("bf4.exe"));
	main_batch.run(game_region);

	/*
	auto mem_region = memory::module("dxgi.dll");
	memory::batch dxgi;
	/*
	/*
	//48 89 5C 24 ? 55 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27  on_present
	dxgi.add("on_present", ("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 60 45 33 F6 44 89 44 24 ? 44 39 35 ? ? ? ? 41 8B F0 8B FA 89 54 24 40 48 8B D9 48 89 4D 20 C6 44 24 ? ?"), [this](memory::handle ptr)
	{
			m_swapchain = ptr.as<IDXGISwapChain**>();
	});
	*/
	
	
	/*
	if (mem_region.wait_for_module())
	{
		LOG("dxgi.dll found");
		dxgi.run(mem_region);
	}

	*/

		m_hwnd = FindWindowW(L"Battlefield 4", nullptr);

	if (!m_hwnd)
		throw std::runtime_error(("Failed to find the game's window."));

	g_pointers = this;

}

pointers::~pointers()
{
	//memory::byte_patch::restore_all();

	g_pointers = nullptr;
}