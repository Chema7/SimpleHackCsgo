#include "funcs.h"
#include <TlHelp32.h>
 
bool CreateMagic::get_process_base_address(const DWORD& pid, uintptr_t& base, uintptr_t& size)
{
	HANDLE mod = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (!mod)
		return false;

	MODULEENTRY32 entry;

	entry.dwSize = sizeof(MODULEENTRY32);

	Module32First(mod, &entry);

	base = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
	size = entry.modBaseSize;

	CloseHandle(mod);

	return true;
}

bool CreateMagic::get_process_module_base(const DWORD& pid, const char* module_name, uintptr_t& base, uintptr_t& size)
{
	HANDLE mod = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (!mod)
		return false;

	MODULEENTRY32 entry;
	entry.dwSize = sizeof(MODULEENTRY32);

	do
	{
		if (!strcmp(entry.szModule, module_name))
		{
			base = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
			size = static_cast<uintptr_t>(entry.modBaseSize);
			CloseHandle(mod);
			return true;
		}
	} while (Module32Next(mod, &entry));

	CloseHandle(mod);

	return false;
}

void CreateMagic::PressKey(int key)
{
	INPUT input;
	WORD vkey = key;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, NULL);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
	Sleep(1);
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}


