#pragma once

#include <windows.h>
#include <optional>
#include "unique_handler.hpp"

constexpr auto excel_str = L"EXCEL.EXE";

namespace kex
{
	void report_error();

	std::optional<DWORD> find_pid();

	unique_handler get_handle(DWORD pid);

	void kill(unique_handler proc);
}
