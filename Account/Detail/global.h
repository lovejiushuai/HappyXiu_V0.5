#pragma once


struct AccountData
{
	enum ModuleNum
	{
		bModuleFirst    =  0,
		bModuleSecond   =  1,
		bModuleThird    =  2
	};
	enum SlotNum
	{
		bSlot0    =  0,
		bSlot1,
		bSlot2,
		bSlot3
	};
};


void getAppCurDir(TCHAR *curDir);
int LogtoFile(const TCHAR *pszFormat, ...);
