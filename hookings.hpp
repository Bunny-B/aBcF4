#include "pch.h"
#include "detour_hook.hpp"
#include "MinHook.h"
#include "vmt_hook.hpp"
#include "renderer.hpp"


struct hooks
{
	static constexpr auto swapchain_num_funcs = 19;
	static constexpr auto swapchain_present_index = 8;
	static constexpr auto swapchain_resizebuffers_index = 13;

	static HRESULT swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags);
	static HRESULT swapchain_resizebuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);

	static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static __int64 sub_140821590(__int64 a1, float a2, unsigned __int8 a3);
	static void __fastcall Screen_Swapchain_Relatedref(__int64 IDXGIAdapter1, __int64 screen, char a3);

};

class minhook_keepalive
{
public:
	minhook_keepalive()
	{
		MH_Initialize();
	}
	~minhook_keepalive()
	{
		MH_Uninitialize();
	}
};


class hooking
{
	friend hooks;
public:
	explicit hooking();
	~hooking();

	void enable();
	void disable();

	class detour_hook_helper
	{
		friend hooking;

		using ret_ptr_fn = std::function<void* ()>;

		ret_ptr_fn m_on_hooking_available = nullptr;

		detour_hook* m_detour_hook = nullptr;

		~detour_hook_helper();

		void enable_hook_if_hooking_is_already_running();

		template <auto detour_function>
		struct hook_to_detour_hook_helper
		{
			static inline detour_hook* m_detour_hook;
		};

		template <auto detour_function>
		static detour_hook_helper* add_internal(detour_hook* dh)
		{
			auto d = new detour_hook_helper();
			d->m_detour_hook = dh;

			m_detour_hook_helpers.push_back(d);
			hook_to_detour_hook_helper<detour_function>::m_detour_hook = dh;

			return d;
		}

	public:
		template <auto detour_function>
		static void add(const std::string& name, void* target)
		{
#ifndef Bunny_Auth
			//_glog("Hooking " << name);
#endif // !Bunny_Auth

			auto d = add_internal<detour_function>(new detour_hook(name, target, detour_function));

			d->enable_hook_if_hooking_is_already_running();
		}

		template <auto detour_function>
		static void* add_lazy(const std::string& name, detour_hook_helper::ret_ptr_fn on_hooking_available)
		{
			auto d = add_internal<detour_function>(new detour_hook(name, detour_function));
			d->m_on_hooking_available = on_hooking_available;

			d->enable_hook_if_hooking_is_already_running();

			return nullptr;
		}
	};

	template <auto detour_function>
	static auto get_original()
	{
		return detour_hook_helper::hook_to_detour_hook_helper<detour_function>::m_detour_hook->get_original<decltype(detour_function)>();
	}




private:
	bool m_enabled{};
	minhook_keepalive m_minhook_keepalive;
	WNDPROC m_og_wndproc = nullptr;
public:
	vmt_hook m_swapchain_hook;
private:

	static inline std::vector<detour_hook_helper*> m_detour_hook_helpers;


};

inline hooking* g_hooking{};


