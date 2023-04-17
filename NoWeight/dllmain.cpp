#include "global.h"
#include "ModUtils.h"
#include "Detours/include/detours.h"

using namespace ModUtils;

LPVOID noWeightBack = nullptr;

DWORD WINAPI MainThread(LPVOID lpParam)
{
	Log("Activating NoWeight...");
	std::vector<uint16_t> noWeight = { 0xff,0xc3,0x83,0xfb,MASKED,0x7c,MASKED,0x4c,0x8d,0x5c,0x24 };
	uintptr_t noWeightAddr = SigScan(noWeight);

	if (noWeightAddr != 0)
	{
		PDETOUR_TRAMPOLINE lpTrampolineData = {};

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttachEx((PVOID*)&noWeightAddr, (PVOID)&noWeightAsm_func, &lpTrampolineData, nullptr, nullptr);
		DetourTransactionCommit();
		const auto lpDetourInfo = (DETOUR_INFO*)lpTrampolineData;
		noWeightBack = lpDetourInfo->pbRemain;
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