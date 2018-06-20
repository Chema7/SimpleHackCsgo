// FirstHax.cpp: define el punto de entrada de la aplicación de consola.
//

#include <Windows.h>
#include <DbgHelp.h>
#include <iostream>
#include "funcs.h"



DWORD processId;
HANDLE handle;
HWND hwnd;

CreateMagic magic;

int main()
{

	while ((hwnd = FindWindowA(NULL, "Counter-Strike: Global Offensive")) == NULL)
		GetWindowThreadProcessId(hwnd, &processId);
	if (processId == NULL)
	{
		std::cout << "Process not found niggah" << std::endl;
		CloseHandle(handle);
		exit(-1);
	}
	//
	handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Process not found niggah" << std::endl;
		CloseHandle(handle);
		exit(-1);
	}

	uintptr_t base, size;
	// 
	bool found = magic.get_process_module_base(processId, "client.dll", base, size);
	
	std::cout << std::hex << base << std::endl;
	std::cout << std::hex << size << std::endl;

	// Gets local Player entity
	auto localPlayero = magic.read<uintptr_t>(base + 0xAAAAB4);

	std::cout << "localPlayero: " << std::hex << localPlayero << std::endl;

	int laif;
	// F8 to stop the hack working
	while (!GetAsyncKeyState(VK_F8))
	{
		laif = magic.read<int>(localPlayero + 0x100);

		if (laif == 0x101 && GetAsyncKeyState(VK_MBUTTON))
		{
			std::cout << "jumping: " << laif << std::endl;
			magic.PressKey(VK_SPACE);
		}

		if (GetAsyncKeyState(VK_NUMPAD1))
		{
			magic.gay_write(localPlayero + 0xA2F4, 0);
		}

		// Antiflash - Probably not working and VAC if used 
		if (GetAsyncKeyState(VK_NUMPAD0))
		{
			auto entity_list = magic.read<uintptr_t>(base + 0x4A8574C);

			for (int i = 0; i < 10; ++i)
			{
				auto player = magic.read<uintptr_t>(entity_list + (i * 0x10));
				if (!player)
					continue;

				std::cout << "Player " << i << ": " << magic.read<int>(player + 0x100) << std::endl;
			}
		}
		Sleep(5);
	}
	CloseHandle(handle);
	std::cin.get();
	std::cin.get();
	


    return 0;
}

