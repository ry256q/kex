#pragma once

#include <windows.h>
#include <memory>

struct handle_deleter
{
	void operator()(HANDLE handle) const
	{
		if (handle != nullptr && handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};

using unique_handler = std::unique_ptr<std::remove_pointer_t<HANDLE>, handle_deleter>;
