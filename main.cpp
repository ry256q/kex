#include "kex.hpp"
#include <print>

int main()
{
	try
	{
		if (auto pid = kex::find_pid(); pid.has_value())
		{
			kex::kill(kex::get_handle(pid.value()));
		}
		else
		{
			std::println("Excel not running!");
		}
	}
	catch (const std::exception& e)
	{
		std::println("{}", e.what());
		return 1;
	}
}