#include <windows.h>
#include <tchar.h>
#include <process.h>
#include "resource.h"

BOOL IsWow64()
{
	typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;
	BOOL bIsWow64 = FALSE;

	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
		GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
		{
			// handle error
		}
	}
	return bIsWow64;
}


int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow
				   )
{
	BOOL wow64 = IsWow64();
	INT msiRes = wow64 ? IDR_MSI64 : IDR_MSI32;
	CONST TCHAR* msiName = wow64 ? TEXT("PicasaExt64.msi") : TEXT("PicasaExt32.msi");

	TCHAR tempPath[_MAX_PATH];
	if( !GetTempPath(_MAX_PATH, tempPath) )
	{
		MessageBox(NULL, TEXT("Failed to get a temp path"), TEXT("PicasaExtSetup"), MB_OK|MB_ICONERROR);
		return 1;
	}

	TCHAR path[_MAX_PATH];
	_stprintf_s(path, _MAX_PATH, TEXT("%s%s"), tempPath, msiName);

	HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(msiRes), TEXT("FILE"));
	HGLOBAL hResourceData = LoadResource(NULL, hResource);
	LPVOID pData = LockResource(hResourceData);

	HANDLE hFile = CreateFile(path, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwBytesWritten = 0;
	WriteFile(hFile, pData, SizeofResource(NULL, hResource), &dwBytesWritten, NULL);
	CloseHandle(hFile);
	if( dwBytesWritten != SizeofResource(NULL, hResource))
	{
		MessageBox(NULL, TEXT("Error writing msi"), TEXT("PicasaExtSetup"), MB_OK|MB_ICONERROR);
		return 1;
	}

	TCHAR command[_MAX_PATH * 2];
	_stprintf_s(command, _MAX_PATH * 2, TEXT("msiexec.exe /i \"%s\""), path);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	if( !CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi) )
	{
		MessageBox(NULL, TEXT("Error running msiexec"), TEXT("PicasaExtSetup"), MB_OK|MB_ICONERROR);
	}
	else
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
	}

	DeleteFile(path);

	return 0;
}
