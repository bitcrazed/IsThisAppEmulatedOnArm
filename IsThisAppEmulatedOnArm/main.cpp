#include "pch.h"

#include <Windows.h>
#include <iostream>
#include <wow64apiset.h>

using namespace std;
using namespace winrt;
using namespace Windows::Foundation;

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
		wchar_t szProcessType
		{
			(nImageFileMachine == IMAGE_FILE_MACHINE_ARM64) ? "ARM64" :
				(nImageFileMachine == IMAGE_FILE_MACHINE_I386) ? "X86" :
					(nImageFileMachine == IMAGE_FILE_MACHINE_AMD64 } ? "x64"
						: "Unknown"
						: "Unknown"
						: "Unknown"
	};

	BOOL fIsProcessARM64 = nNativeMachine == IMAGE_FILE_MACHINE_ARM64;
	BOOL fIsProcessX86 = nNativeMachine == IMAGE_FILE_MACHINE_I386;
	BOOL fIsProcessX64 = nNativeMachine == IMAGE_FILE_MACHINE_AMD64;

	cout << "This " << (fIsProcessX64 ? "x64" : "x86") << " process is " << (fIsMachineARM64 ? "emulated on Arm64" : "running natively on x64");

}
}
