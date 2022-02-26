#include "pch.h"

#include <Windows.h>
#include <wow64apiset.h>
#include <iostream>

using namespace winrt;
using namespace Windows::Foundation;
using namespace std;

int main()
{
	init_apartment();

	HANDLE hCurrentProcess{ GetCurrentProcess() };

	USHORT nImageFileMachine{};
	USHORT nNativeMachine{};
	if (IsWow64Process2(hCurrentProcess,
		&nImageFileMachine, // Returns the type of WoW process, or IMAGE_FILE_MACHINE_UNKNOWN (0) if the target process is not a WOW64 process
		&nNativeMachine))   // Returns IMAGE_FILE_MACHINE_* value identifying the native architecture of host system
	{
		const char* szProcessType
		{
			(nImageFileMachine == IMAGE_FILE_MACHINE_AMD64) ? "x64"
				: (nImageFileMachine == IMAGE_FILE_MACHINE_ARM64) ? "ARM64"
				: (nImageFileMachine == IMAGE_FILE_MACHINE_I386) ? "X86"
				: (nImageFileMachine == IMAGE_FILE_MACHINE_UNKNOWN) ? "Non-WOW64"
				: "Unknown"
		};

		const BOOL fIsMachineARM64
		{
			(nNativeMachine == IMAGE_FILE_MACHINE_ARM64) ? TRUE : FALSE
		};

		const char* msg{ (fIsMachineARM64) ? "emulated on ARM64" : "natively on non-ARM64 device" };

		cout << "This "
			<< szProcessType
			<< " process is running "
			<< msg
			<< endl;
	}
	else
	{
		cout << "Error" << endl;
	}
}
