#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include "Global.h"
#include "Account.h"
#include "AccountDlg.h"


extern "C";


int LogtoFile(const TCHAR *pszFormat, ...)
{
	return 0;

	FILE *	fileHdl;
	BOOL	ret = TRUE;
	TCHAR tempBuffer[1024];
	TCHAR logFileName[1024];
	CTime t =CTime::GetCurrentTime();
	_stprintf(tempBuffer,_T("%02d-%02d %02d:%02d:%02d "),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());

	TCHAR Path[MAX_PATH];
	TCHAR *s;
	GetModuleFileName(NULL,Path,MAX_PATH);
	s = wcsrchr(Path,'\\');
	if (s) 
		s[1]=0;
	wsprintf(logFileName,_T("%s%s"),Path,_T("log.txt"));
	

	va_list vaArguments;
	va_start(vaArguments, pszFormat);
	vswprintf(&(tempBuffer[_tcslen(tempBuffer)]), pszFormat, vaArguments);
	va_end(vaArguments);
	_tcscat(tempBuffer, _T("\r\n"));



	fileHdl = _tfopen(logFileName,_T("a+"));
	if(fileHdl != NULL)
	{
		fseek(fileHdl,0,SEEK_END);
		_fputts(tempBuffer,fileHdl);
		fclose(fileHdl);
	}
	return ret;
}

void getAppCurDir(TCHAR *curDir)
{
	TCHAR szPath[MAX_PATH];
	//TCHAR Path[MAX_PATH];
	TCHAR *s;

	ZeroMemory(szPath,MAX_PATH); 
	GetModuleFileName(NULL, szPath, MAX_PATH);
	//wsprintf(Path,_T("%s"),szPath);

	s = wcsrchr(szPath,'\\');
	if (s) 
		s[1]=0;
	//wsprintf(Path,_T("%s%s"),szPath,_T("log.txt"));

	wsprintf(curDir,_T("%s"),szPath);
}

int al_GetSettingString(LPCTSTR sec,LPCTSTR key,LPTSTR defaultString,LPTSTR string)
{
	TCHAR tempBuffer[MAX_PATH]={0};
	char filename[MAX_PATH]={0};
	FILE *stream = NULL;
	char szString[MAX_PATH]={0};

	wsprintf(tempBuffer,_T("%s"),defaultString);

	int iLength ;    
	iLength = WideCharToMultiByte(CP_ACP, 0, tempBuffer, -1, NULL, 0, NULL, NULL);     
	WideCharToMultiByte(CP_ACP, 0, tempBuffer, -1, filename, iLength, NULL, NULL); 

	/*int j=strlen(filename);
	for(j=strlen(filename);filename[j]!='\\';j--);
	filename[j]='\0';*/
	

	if(filename<=0)
		return -1;

	errno_t err;
	err=fopen_s(&stream,filename,"r");
	if(err==0)
	{
		fseek(stream, 0, SEEK_SET);
		fgets(szString,sizeof(szString),stream);
		//printf("Thefile'tempBuffer'wasopened\n");
		/*size_t len = wcslen(szString) + 1;
		size_t converted = 0;
		char *CStr;
		CStr=(char*)malloc(len*sizeof(char));
		wcstombs_s(&converted, CStr, len, szString, _TRUNCATE);
		fgets(CStr,sizeof(CStr),stream);
		printf("%s\n",stream);
		printf("%s\n",szString);*/

		// for  test  WideChar  display
		/*CString strChar;
		strChar.Empty();

		int length = strlen(szString)+1;
		wchar_t *WStr = (wchar_t*)malloc(sizeof(wchar_t)*length);
		memset(WStr,0,length*sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP,0,szString,strlen(szString),WStr,length);

		strChar.Format(_T("%s"),WStr);
		printf("%s\n",strChar);
		AfxMessageBox(strChar);*/   


		
	}
	else
	{
		//printf("The file'tempBuffer'was not opened\n");
		return -1;//要返回错误代码
	}
	//if(NULL == fp)
	//{
	//	return -1;//要返回错误代码
	//}
	//else
	//{
	//	size_t len = wcslen(szString) + 1;
	//	size_t converted = 0;
	//	char *CStr;
	//	CStr=(char*)malloc(len*sizeof(char));
	//	wcstombs_s(&converted, CStr, len, szString, _TRUNCATE);
	//	fgets(CStr,sizeof(CStr),fp);
	//	printf("%s\n",szString);
	//	free(CStr);
	//}

//	fflush(stdin);
//	system("pause");

	fclose(stream);
	stream=NULL;//需要指向空，否则会指向原打开文件地址
	return 0;

}
int readCharOfLine(char *fileName)
{
	char tempBuffer[1024]={0};
	FILE *stream = NULL;
	char szString[MAX_PATH]={0};

	strncpy_s(tempBuffer,fileName,strlen(fileName));

	/*printf("%s\n",fileName);
	printf("%s\n",tempBuffer);*/

	/*char *strPath;
	strPath = getwd(NULL,0);
	printf("%s\n",strPath);
	*/

	if(tempBuffer<=0)
		return -1;

	errno_t err;
	err=fopen_s(&stream,tempBuffer,"r");
	if(err==0)
	{
		fseek(stream, 0, SEEK_SET);
		fgets(szString,sizeof(szString),stream);
		//printf("Thefile'tempBuffer'wasopened\n");
		/*size_t len = wcslen(szString) + 1;
		size_t converted = 0;
		char *CStr;
		CStr=(char*)malloc(len*sizeof(char));
		wcstombs_s(&converted, CStr, len, szString, _TRUNCATE);
		fgets(CStr,sizeof(CStr),stream);
		printf("%s\n",stream);
		printf("%s\n",szString);*/

		CString strChar;
		strChar.Empty();

		size_t len = strlen(szString) + 1;
		size_t converted = 0;
		wchar_t *WStr = NULL;
		WStr=(wchar_t*)malloc(len*sizeof(wchar_t));
		mbstowcs_s(&converted, WStr, len, szString, _TRUNCATE);
		
		strChar.Format(_T("%s"),WStr);

		/*printf("%s\n",strChar);
		AfxMessageBox(strChar);*/
	}
	else
	{
		//printf("The file'tempBuffer'was not opened\n");
		return -1;//要返回错误代码
	}
	//if(NULL == fp)
	//{
	//	return -1;//要返回错误代码
	//}
	//else
	//{
	//	size_t len = wcslen(szString) + 1;
	//	size_t converted = 0;
	//	char *CStr;
	//	CStr=(char*)malloc(len*sizeof(char));
	//	wcstombs_s(&converted, CStr, len, szString, _TRUNCATE);
	//	fgets(CStr,sizeof(CStr),fp);
	//	printf("%s\n",szString);
	//	free(CStr);
	//}

//	fflush(stdin);
//	system("pause");

	fclose(stream);
	stream=NULL;//需要指向空，否则会指向原打开文件地址
	return 0;
}