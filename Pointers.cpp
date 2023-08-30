#include "pch.h"
#include "Pointers.hpp"

pointers::pointers()
{
	memory::batch main_batch;
	main_batch.add(("DX_Renderer"), ("48 8B 0D ? ? ? ? 48 8B 01 FF 50 08 85 C0 75 2D 48 8B 05 ? ? ? ? 48 85 C0 75 1A 48 8B 0D ? ? ? ? 48 8D 15 ? ? ? ?"), [this](memory::handle ptr) {
		m_dxrenderer = ptr.add(0x3).rip().as<DxRenderer*>();
		//	 *(DxRenderer**)OFFSET_DXRENDERER; //0x142738080
		auto dxrenderer = ptr.add(0x3).rip().as<DxRenderer*>();
		LOG(hex((DWORD64)((QWORD*)dxrenderer))<< " render");


		const auto screen = dxrenderer->m_pScreen;
		if (!screen) return nullptr;
		LOG(hex(screen) << " screen");
		auto swapchain = screen->m_pSwapChain;
		if (!swapchain) return nullptr;
		LOG(hex(swapchain) << " swapchain");

		//	IDXGISwapChain** m_swapchain{};
		//swapchain = swapchain pointer IDXGISwapChain* m_pSwapChain;	
		m_swapchain = &swapchain;
		
	});
	//E8 ? ? ? ? 48 8B D7 48 8B CE E8 ? ? ? ? C6 46 40 01  0xCA _qword_1423EC238_render_related
	main_batch.add(("render_qword"), ("E8 ? ? ? ? 48 8B D7 48 8B CE E8 ? ? ? ? C6 46 40 01"), [this](memory::handle ptr) {
		render = ptr.add(0x1).rip().add(0xCA).as<PVOID>();
		LOG("render: " << hex(render));
	});
	//E8 ? ? ? ? 48 8B D7 48 8B CE E8 ? ? ? ? C6 46 40 01 void __fastcall Screen_Swapchain_Relatedref(__int64 IDXGIAdapter1, __int64 screen, char a3)
	 
	main_batch.add(("Screen_Swapchain_Relatedref"), ("E8 ? ? ? ? 48 8B D7 48 8B CE E8 ? ? ? ? C6 46 40 01"), [this](memory::handle ptr) {
		Screen_Swapchain_Relatedref = ptr.add(0x1).rip().as<PVOID>();
		});

	//E8 ? ? ? ? 4C 89 76 30 a2_class
	main_batch.add(("a2_class"), ("E8 ? ? ? ? 4C 89 76 30"), [this](memory::handle ptr) {
		_unk_142317F68_a2_class = ptr.add(0x1).rip().add(0x3).as<PVOID>();
		LOG("a2_class: " << hex(_unk_142317F68_a2_class));

	});

	//45 88 BE ? ? ? ? 48 8D 15 ? ? ? ?  no result 

	//48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B D8 49 8B 4E 48 <code>Engine.BuildInfo_Win64_retail.dll

	//49 8B CD FF 15 ? ? ? ? 48 2B DE 48 C1 FB 03 msvcr110.dll rti

	/*
	main_batch.add(("render_qword"), ("49 8B CD FF 15 ? ? ? ? 48 2B DE 48 C1 FB 03 "), [this](memory::handle ptr) {
		render = ptr.add(0x5).rip().as<PVOID>();
		LOG("render: " << hex(render));
	});
	//E8 ? ? ? ? 48 8B 4E 40 F3 0F 10 4F ?  //sub_140821590
	main_batch.add(("sub_140821590"), ("E8 ? ? ? ? 48 8B 4E 40 F3 0F 10 4F ?"), [this](memory::handle ptr) {
		sub_140821590 = ptr.add(0x1).rip().as<PVOID>();
		LOG("sub_140821590: " << hex(sub_140821590));
	});

	*/
	auto game_region = memory::module(("bf4.exe"));
	main_batch.run(game_region);

	
	auto mem_region = memory::module("dxgi.dll");
	memory::batch dxgi;

	//E9 3B 72 FF BF  Present dxgi.dll
	dxgi.add(("Present"), ("E9 3B 72 FF BF"), [this](memory::handle ptr) {
		m_present = ptr.as<PVOID>();
		LOG("Present: " << hex(m_present));
	});
	/*
	/*
	//48 89 5C 24 ? 55 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 27  on_present
	dxgi.add("on_present", ("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 60 45 33 F6 44 89 44 24 ? 44 39 35 ? ? ? ? 41 8B F0 8B FA 89 54 24 40 48 8B D9 48 89 4D 20 C6 44 24 ? ?"), [this](memory::handle ptr)
	{
			m_swapchain = ptr.as<IDXGISwapChain**>();
	});
	*/
	
	
	
	if (mem_region.wait_for_module())
	{
		LOG("dxgi.dll found");
		dxgi.run(mem_region);
	}

	

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