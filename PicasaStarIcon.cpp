// PicasaStarIcon.cpp : Implementation of CPicasaStarIcon

#include "stdafx.h"
#include "PicasaStarIcon.h"

// CPicasaStarIcon

/*
Provides the location of the icon overlay's bitmap.

This method is first called during initialization, it 
returns the fully qualified path of the file containing 
the icon overlay image, and its zero-based index within 
the file. The icon can be contained in any of the 
standard file types, including .exe, .dll, and .ico.
*/

// IShellIconOverlayIdentifier::GetOverlayInfo
// returns The Overlay Icon Location to the system

STDMETHODIMP CPicasaStarIcon::GetOverlayInfo(
	LPWSTR pwszIconFile,
	int cchMax,
	int* pIndex,
	DWORD* pdwFlags)
{
	// Get our module's full path
	GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), pwszIconFile, cchMax);

	// Use first icon in the resource
	*pIndex=0; 

	*pdwFlags = ISIOI_ICONFILE | ISIOI_ICONINDEX;
	return S_OK;
}


/*
Specifies the priority of an icon overlay.

This method is called only during initialization. It 
assigns a priority value (ranging from 0=Highest to 
100=Lowest priority) to the handler's icon overlay.

Priority helps resolve the conflict when multiple 
handlers are installed.
*/

// IShellIconOverlayIdentifier::GetPriority
// returns the priority of this overlay 0 being the highest. 

STDMETHODIMP CPicasaStarIcon::GetPriority(int* pPriority)
{
	// we want highest priority 
	*pPriority=0;
	return S_OK;
}


static bool FileExists(LPCWSTR pwszPath)
{
	DWORD dwAttribs = GetFileAttributes(pwszPath);
	return( (dwAttribs != INVALID_FILE_ATTRIBUTES) &&
		!(dwAttribs & FILE_ATTRIBUTE_DIRECTORY) );
}


static bool IsStarred(LPCWSTR pwszIniPath, LPCWSTR pwszFileName, LPCWSTR pwszFileExt)
{
	wchar_t iniKey[_MAX_PATH];
	if( -1 == swprintf_s(iniKey, countof(iniKey), L"[%s%s]", pwszFileName, pwszFileExt) )
		return false;

	CStdioFile file;
	if( !file.Open(pwszIniPath, CFile::modeRead|CFile::shareDenyNone|CFile::typeText|CFile::osSequentialScan) )
		return false;

	bool bStarred = false;
	CString line;
	while( file.ReadString(line) )
	{
		if( line == iniKey )
		{
			while( file.ReadString(line) && line[0] != '[' )
			{
				if( line == L"star=yes" )
				{
					bStarred = true;
					break;
				}
			}
			break;
		}
	}

	return bStarred;
}


/*
Specifies whether an icon overlay should be added to 
a Shell object's icon.

You may return S_OK to allow adding the overlay icon 
or S_FALSE to keep object's icon intact.
*/

// IShellIconOverlayIdentifier::IsMemberOf
// Returns whether the object should have this overlay or not 

STDMETHODIMP CPicasaStarIcon::IsMemberOf(LPCWSTR pwszPath, DWORD dwAttrib)
{
	HRESULT r = S_FALSE;
	wchar_t drive[_MAX_DRIVE];
	wchar_t dir[_MAX_DIR];
	wchar_t filename[_MAX_FNAME];
	wchar_t ext[_MAX_EXT];

	if( !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY) && 
		0 == _wsplitpath_s(pwszPath, drive, countof(drive), dir, countof(dir), filename, countof(filename), ext, countof(ext)) )
	{
		wchar_t iniPath[_MAX_PATH];
		if( 0 == _wmakepath_s(iniPath, countof(iniPath), drive, dir, PICASA_INI_FNAME, PICASA_INI_EXT) &&
			FileExists(iniPath) )
		{
			if( IsStarred(iniPath, filename, ext) )
			{
				r = S_OK;
			}
		}
	}

	return r;
}

