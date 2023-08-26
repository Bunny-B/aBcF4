#pragma once 
#include "pch.h"

class Screen
{
public:
	BYTE pad00[0x58];				//0x00
	unsigned int m_Width;			//0x58
	unsigned int m_Height;			//0x5C
	unsigned int m_WindowWidth;			//0x60
	unsigned int m_WindowHeight;		//0x64
	BYTE pad01[0x88];				//0x68
	IDXGISwapChain* m_pSwapChain;		//0xF0
};

class DxRenderer
{
public:
	BYTE pad00[0x38];                    // 0x00
	Screen* m_pScreen;                    // 0x38
	BYTE pad78[0xC0];                    // 0x40
	ID3D11Device* m_pDevice;            // 0x100
	ID3D11DeviceContext* m_pContext;    // 0x108
	char _0x0110[192];
	void* m_settings; //0x01D0 

	
};//Size=0x0110

class  pointers
{
public:
	explicit pointers();
	~pointers();
public:
	HWND m_hwnd{};
	IDXGISwapChain* m_swapchain{};
	PVOID m_dxrenderer{};
};
inline pointers* g_pointers{};