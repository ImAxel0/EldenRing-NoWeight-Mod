#include <Windows.h>

extern "C" void noWeightAsm_func();

extern "C" LPVOID noWeightBack;


struct DETOUR_ALIGN
{
	BYTE    obTarget : 3;
	BYTE    obTrampoline : 5;
};

struct DETOUR_INFO
{
	BYTE            rbCode[30];     // target code + jmp to pbRemain.
	BYTE            cbCode;         // size of moved target code.
	BYTE            cbCodeBreak;    // padding to make debugging easier.
	BYTE            rbRestore[30];  // original target code.
	BYTE            cbRestore;      // size of original target code.
	BYTE            cbRestoreBreak; // padding to make debugging easier.
	DETOUR_ALIGN    rAlign[8];      // instruction alignment array.
	PBYTE           pbRemain;       // first instruction after moved code. [free list]
	PBYTE           pbDetour;       // first instruction of detour function.
	BYTE            rbCodeIn[8];    // jmp [pbDetour]
};