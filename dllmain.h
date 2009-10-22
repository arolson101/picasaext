// dllmain.h : Declaration of module class.

class CPicasaExtModule : public CAtlDllModuleT< CPicasaExtModule >
{
public :
	DECLARE_LIBID(LIBID_PicasaExtLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PICASAEXT, "{3D38C35E-34B7-476D-837D-6F2A33AE2281}")
};

extern class CPicasaExtModule _AtlModule;
