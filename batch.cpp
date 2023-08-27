#include "pch.h"


namespace memory
{
	void batch::add(std::string name, pattern pattern, std::function<void(handle)> callback)
	{
		m_entries.emplace_back(std::move(name), std::move(pattern), std::move(callback));

	}

	void batch::run(range region)
	{

		bool all_found = true;
		for (auto& entry : m_entries)
		{
			//_log(XOR("Looking For: ") << entry.m_name);
			if (auto result = region.scan(entry.m_pattern))
			{

				if (entry.m_callback)
				{
					std::invoke(std::move(entry.m_callback), result);
					//LOG(("Pointer Found as -> ") << entry.m_name);
				
					LOG("Found " << entry.m_name 
						//<<" ["<< hex(region.begin().as<DWORD64>()) << "]" 
						<< " bf4.exe+" << hex(result.as<DWORD64>() - region.begin().as<DWORD64>())
						<<" result "<<hex(result.as<DWORD64>()));
					//_log(file_out.str());
					//file_out.clear();
				}
				else
				{
					all_found = false;
					LOG(("Failed to find 0 ") << entry.m_name << ".");
				}
			}
			else
			{
				all_found = false;
				LOG(("Failed to find 1 ") << entry.m_name << ".");

			}
		}

		m_entries.clear();
		if (!all_found)
		{
			throw std::runtime_error(("Failed to find some patterns."));
		}
	}
}
