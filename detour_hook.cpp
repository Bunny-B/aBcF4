//#include "pch.h"
#include "detour_hook.hpp"


	detour_hook::detour_hook(std::string name, void* detour) :
		m_name(std::move(name)),
		m_detour(detour)
	{

	}

	detour_hook::detour_hook(std::string name, void* target, void* detour) :
		m_name(std::move(name)),
		m_target(target),
		m_detour(detour)
	{
		create_hook();
	}

	void detour_hook::set_target_and_create_hook(void* target)
	{
		m_target = target;
		create_hook();
	}

	void detour_hook::create_hook()
	{
		fix_hook_address();
		if (auto status = MH_CreateHook(m_target, m_detour, &m_original); status != MH_OK)
			throw std::runtime_error(std::format(" {} '{}' {} {:X} {} {})", ("Failed to create hook"), m_name,("at 0x"), uintptr_t(m_target),("(error: "), MH_StatusToString(status)));
	}

	detour_hook::~detour_hook() noexcept
	{
		if (auto status = MH_RemoveHook(m_target); status != MH_OK) {
			throw std::runtime_error((("Failed to remove hook '") + m_name + ("' at ") +std::to_string(uintptr_t(m_target)) + ("(error: ") + m_name + (")")));
		}
	}

	void detour_hook::enable()
	{
		if (auto status = MH_QueueEnableHook(m_target); status != MH_OK)
			throw std::runtime_error(std::format("{} 0x{:X} ({})",("Failed to enable hook"), uintptr_t(m_target), MH_StatusToString(status)));
	}

	void detour_hook::disable()
	{
		if (auto status = MH_QueueDisableHook(m_target); status != MH_OK)
			throw std::runtime_error(("Failed to disable hook '") + m_name + "'.");
	}

	DWORD exp_handler(PEXCEPTION_POINTERS exp, std::string const& name)
	{
		return exp->ExceptionRecord->ExceptionCode == STATUS_ACCESS_VIOLATION
			? EXCEPTION_EXECUTE_HANDLER
			: EXCEPTION_CONTINUE_SEARCH;
	}

	void detour_hook::fix_hook_address()
	{
		
		auto ptr = memory::handle(m_target);
		while (ptr.as<std::uint8_t&>() == 0xE9)
			ptr = ptr.add(1).rip();
		
		m_target = ptr.as<void*>();
	}

