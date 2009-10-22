// PicasaStarIcon.h : Declaration of the CPicasaStarIcon

#pragma once
#include "resource.h"       // main symbols

#include "PicasaExt_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

#define PICASA_INI_FNAME L".picasa"
#define PICASA_INI_EXT L".ini"
#define PICASA_INI_FULLNAME (PICASA_INI_FNAME PICASA_INI_EXT)

extern void BroadcastIniChange(const wchar_t* drive, const wchar_t* dir);


// CPicasaStarIcon

class ATL_NO_VTABLE CPicasaStarIcon :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPicasaStarIcon, &CLSID_PicasaStarIcon>,
	public IShellIconOverlayIdentifier,
	public IPersistFile
{
public:
	CPicasaStarIcon()
	{
	}

	// IShellIconOverlayIdentifier Methods
	STDMETHOD(GetOverlayInfo)(LPWSTR pwszIconFile, int cchMax,int *pIndex,DWORD* pdwFlags);
	STDMETHOD(GetPriority)(int* pPriority);
	STDMETHOD(IsMemberOf)(LPCWSTR pwszPath,DWORD dwAttrib);

	// IPersistFile
	STDMETHOD(GetClassID)( CLSID* )       { return E_NOTIMPL; }
	STDMETHOD(IsDirty)()                  { return E_NOTIMPL; }
	STDMETHOD(Save)( LPCOLESTR, BOOL )    { return E_NOTIMPL; }
	STDMETHOD(SaveCompleted)( LPCOLESTR ) { return E_NOTIMPL; }
	STDMETHOD(GetCurFile)( LPOLESTR* )    { return E_NOTIMPL; }
	STDMETHOD(Load)( LPCOLESTR wszFile, DWORD /*dwMode*/ )
	{ 
		USES_CONVERSION;
		lstrcpyn ( m_szFilename, OLE2CT(wszFile), MAX_PATH );
		return S_OK;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PICASASTARICON)


BEGIN_COM_MAP(CPicasaStarIcon)
	COM_INTERFACE_ENTRY(IShellIconOverlayIdentifier)
	COM_INTERFACE_ENTRY(IPersistFile)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	TCHAR     m_szFilename [MAX_PATH];  // Full path to the file in question.
};

OBJECT_ENTRY_AUTO(__uuidof(PicasaStarIcon), CPicasaStarIcon)
