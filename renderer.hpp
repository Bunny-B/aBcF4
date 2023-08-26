#pragma once
#include "ImGui/imgui.h"
#include <wrl/client.h>
#include <d3d11.h>
template <typename T>
using comptr = Microsoft::WRL::ComPtr<T>;

class renderer
{
public:
	explicit renderer();
	~renderer();

	void on_present();

	void pre_reset();
	void post_reset();

	void wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	comptr<IDXGISwapChain> m_dxgi_swapchain;
	comptr<ID3D11Device> m_d3d_device;
	comptr<ID3D11DeviceContext> m_d3d_device_context;
};

inline renderer* g_renderer{};

