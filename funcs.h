#pragma once
#include <Windows.h>


class CreateMagic
{
	private:

	public:
		static bool get_process_base_address(const DWORD& pid, uintptr_t& base, uintptr_t& size);
		static bool get_process_module_base(const DWORD& pid, const char* module_name, uintptr_t& base, uintptr_t& size);
		static void PressKey(int key);
		template <typename T>
		static T read(const uintptr_t& base)
		{
			T buffer;
			ReadProcessMemory(handle, reinterpret_cast<void*>(base), &buffer, sizeof(T), nullptr);
			return buffer;
		}
		template <typename T>
		static void gay_write(const uintptr_t& base, T value)
		{
			WriteProcessMemory(handle, reinterpret_cast<void*>(base), &value, sizeof(T), nullptr);
		}
};


