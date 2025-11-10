#include "kex.hpp"
#include "unique_handler.hpp"

#include <format>
#include <stdexcept>
#include <tlhelp32.h>

namespace kex
{
	std::string make_error_message(DWORD error_code)
    {
        return std::format("WinAPI Error {} (0x{:X})", error_code, error_code);
    }

	std::optional<DWORD> find_pid()
	{
		auto snapshot = unique_handler{CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, {})};

		if (snapshot.get() == INVALID_HANDLE_VALUE)
		{
			auto err_msg = make_error_message(GetLastError());
			throw std::runtime_error(std::format("Error creating snapshot | {}", err_msg));
		}

		auto process_entry = PROCESSENTRY32{};
		process_entry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(snapshot.get(), &process_entry))
		{
			do
			{
				if (_wcsicmp(process_entry.szExeFile, excel_str) == 0)
				{
					return process_entry.th32ProcessID;
				}
			}
			while (Process32Next(snapshot.get(), &process_entry) != false);

            if (auto err_code = GetLastError(); err_code != ERROR_NO_MORE_FILES) {
                throw std::runtime_error(std::format("Error processing snapshot | {}", make_error_message(err_code)));
            }
		}

		return {};
	}

	unique_handler get_handle(DWORD pid)
	{
		auto handle = unique_handler{OpenProcess(PROCESS_TERMINATE, false, pid)};

		if (handle == nullptr)
		{
			auto err_msg = make_error_message(GetLastError());
			throw std::runtime_error(std::format("Failed to open process | {}", err_msg));
		}

		return handle;
	}

	void kill(unique_handler proc)
	{
		UINT exit_code{};
		auto result = TerminateProcess(proc.get(), exit_code);

		if (!result)
		{
			auto err_msg = make_error_message(GetLastError());
			throw std::runtime_error(std::format("Failed to kill process | {}", err_msg));
		}
	}
}