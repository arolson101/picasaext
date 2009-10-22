// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "PicasaExt_i.h"
#include "dllmain.h"
#include "DirectoryChanges.h"
#include "PicasaStarIcon.h"

CPicasaExtModule _AtlModule;

class CMyDirectoryChangeHandler : public CDirectoryChangeHandler
{
public:
	CMyDirectoryChangeHandler(){} 
	virtual ~CMyDirectoryChangeHandler(){}

protected:
	virtual void On_FileAdded(const CString & strFileName) { BrodcastChange(strFileName); }
	virtual void On_FileRemoved(const CString & strFileName) { BrodcastChange(strFileName); }
	virtual void On_FileModified(const CString & strFileName) { BrodcastChange(strFileName); }
	virtual void On_FileNameChanged(const CString & strOldFileName, const CString & strNewFileName) { BrodcastChange(strOldFileName); }
	void BrodcastChange(const CString& strFileName)
	{
		const wchar_t* pwszPath = strFileName;
		wchar_t drive[_MAX_DRIVE];
		wchar_t dir[_MAX_DIR];
		wchar_t filename[_MAX_FNAME];
		wchar_t ext[_MAX_EXT];

		if( 0 == _wsplitpath_s(pwszPath, drive, countof(drive), dir, countof(dir), filename, countof(filename), ext, countof(ext)) )
		{
			wchar_t path[_MAX_PATH];
			if( 0 == _wmakepath_s(path, countof(path), drive, dir, NULL, NULL) )
			{
				SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATH, path, NULL); 
			}
		}
	}
};


class CPicasaExtApp : public CWinApp
{
public:
	CPicasaExtApp() : mMutex(0), mWatcher(false) {}

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	static DWORD WINAPI InitWatchThread(LPVOID param);

	DECLARE_MESSAGE_MAP()

private:
	HANDLE mMutex;
	CRITICAL_SECTION mCritSec;
	CDirectoryChangeWatcher mWatcher;
	CMyDirectoryChangeHandler mHandler;
};

BEGIN_MESSAGE_MAP(CPicasaExtApp, CWinApp)
END_MESSAGE_MAP()

CPicasaExtApp theApp;

BOOL CPicasaExtApp::InitInstance()
{
	BOOL ret = CWinApp::InitInstance();

	InitializeCriticalSection(&mCritSec);
	if( ret )
	{
		mMutex = CreateMutex(NULL, TRUE, TEXT("PicasaExt"));
		DWORD lastError = GetLastError();
		if( mMutex )
		{
			if( lastError != ERROR_ALREADY_EXISTS )
			{
				HANDLE hThread = ::CreateThread(NULL, 0, InitWatchThread, this, 0, NULL);
				CloseHandle(hThread);
			}
			else
			{
				mMutex = 0;
			}
		}
	}

	return ret;
}

DWORD WINAPI CPicasaExtApp::InitWatchThread(LPVOID param)
{
	CPicasaExtApp* self = reinterpret_cast<CPicasaExtApp*>(param);

	EnterCriticalSection(&self->mCritSec);

	DWORD filters = FILE_NOTIFY_CHANGE_FILE_NAME
		| FILE_NOTIFY_CHANGE_SIZE
		| FILE_NOTIFY_CHANGE_LAST_WRITE
		| FILE_NOTIFY_CHANGE_CREATION;

	wchar_t driveStrings[26 * 4];
	GetLogicalDriveStrings(sizeof(driveStrings), driveStrings);

	wchar_t* context = driveStrings;
	for(wchar_t* drive=driveStrings; drive[0]; drive+=_MAX_DRIVE+1)
	{
		UINT driveType = GetDriveType(drive);
		if( driveType == DRIVE_FIXED )
		{
			self->mWatcher.WatchDirectory(drive, filters, &self->mHandler, TRUE, PICASA_INI_FULLNAME, NULL);
		}
	}

	LeaveCriticalSection(&self->mCritSec);
	return 0;
}


int CPicasaExtApp::ExitInstance()
{
	// These lines seem to cause all applications to hang while exiting
	//EnterCriticalSection(&mCritSec);
	//mWatcher.UnwatchAllDirectories();
	//LeaveCriticalSection(&mCritSec);

	DeleteCriticalSection(&mCritSec);

	if( mMutex )
		CloseHandle(mMutex);

	return CWinApp::ExitInstance();
}
