#include "pch.h"
#include <Windows.h>

#include "ModUtils.h"

using namespace ModUtils;

DWORD WINAPI MainThread(LPVOID lpParam)
{
	Log("Activating NoWeight...");
	std::vector<uint16_t> pattern = { 0x74, MASKED, 0xf3, 0x0f, 0x58, 0x70, MASKED, 0xff, 0xc7, 0x83, 0xff, MASKED, 0x7c, MASKED, 0x41, 0x8b, 0xfe };
	std::vector<uint16_t> originalBytes = { 0x74, 0x05 };
	std::vector<uint8_t> newBytes = { 0xeb, 0x05 };

	uintptr_t patchAddress = SigScan(pattern);
	if (patchAddress != 0)
	{
		Replace(patchAddress, originalBytes, newBytes);
	}
	
	std::vector<uint16_t> pattern1 = { 0x74, MASKED, 0xf3, 0x0f, 0x58, 0x70, MASKED, 0xff, 0xc7, 0x83, 0xff, MASKED, 0x7c, MASKED, 0x41, 0x8b, 0xde };
	std::vector<uint16_t> originalBytes1 = { 0x74, 0x05 };
	std::vector<uint8_t> newBytes1 = { 0xeb, 0x05 };

	uintptr_t patchAddress1 = SigScan(pattern1);
	if (patchAddress1 != 0)
	{
		Replace(patchAddress1, originalBytes1, newBytes1);
	}
	CloseLog();
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);
		CreateThread(0, 0, &MainThread, 0, 0, NULL);
	}
	return 1;
}