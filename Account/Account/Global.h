#pragma once


int LogtoFile(const TCHAR *pszFormat, ...);

void getAppCurDir(TCHAR *curDir);
int al_GetSettingString(LPCTSTR sec,LPCTSTR key,LPTSTR defaultString,LPTSTR string);

