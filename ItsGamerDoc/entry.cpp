#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include "driver.h"
#include "ue4.h"
#include "offsets.h"
#include <iostream>
#include "utils.h"
#include "cheat.h"

auto main() -> NTSTATUS
{
	printf("Start Valorant...\n");

	int ProcessID = 0;
	while (ProcessID == 0)
	{
		ProcessID = myGetProcessID("VALORANT-Win64-Shipping.exe");
		Sleep(1);
	}

	system("cls");
	printf("Loaded.\n");

	Cool = CoolDriver(ProcessID);

	std::thread(GlowThread).detach();

	Sleep(-1);
}