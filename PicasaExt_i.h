

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Sat Oct 24 20:39:07 2009
 */
/* Compiler settings for .\PicasaExt.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __PicasaExt_i_h__
#define __PicasaExt_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPicasaStarIcon_FWD_DEFINED__
#define __IPicasaStarIcon_FWD_DEFINED__
typedef interface IPicasaStarIcon IPicasaStarIcon;
#endif 	/* __IPicasaStarIcon_FWD_DEFINED__ */


#ifndef __PicasaStarIcon_FWD_DEFINED__
#define __PicasaStarIcon_FWD_DEFINED__

#ifdef __cplusplus
typedef class PicasaStarIcon PicasaStarIcon;
#else
typedef struct PicasaStarIcon PicasaStarIcon;
#endif /* __cplusplus */

#endif 	/* __PicasaStarIcon_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IPicasaStarIcon_INTERFACE_DEFINED__
#define __IPicasaStarIcon_INTERFACE_DEFINED__

/* interface IPicasaStarIcon */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPicasaStarIcon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B43D611-DE5D-45E5-9545-269B774472B8")
    IPicasaStarIcon : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPicasaStarIconVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPicasaStarIcon * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPicasaStarIcon * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPicasaStarIcon * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPicasaStarIcon * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPicasaStarIcon * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPicasaStarIcon * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPicasaStarIcon * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IPicasaStarIconVtbl;

    interface IPicasaStarIcon
    {
        CONST_VTBL struct IPicasaStarIconVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPicasaStarIcon_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPicasaStarIcon_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPicasaStarIcon_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPicasaStarIcon_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPicasaStarIcon_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPicasaStarIcon_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPicasaStarIcon_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPicasaStarIcon_INTERFACE_DEFINED__ */



#ifndef __PicasaExtLib_LIBRARY_DEFINED__
#define __PicasaExtLib_LIBRARY_DEFINED__

/* library PicasaExtLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PicasaExtLib;

EXTERN_C const CLSID CLSID_PicasaStarIcon;

#ifdef __cplusplus

class DECLSPEC_UUID("8218849A-80B4-4231-AD8A-5167F27D2F6F")
PicasaStarIcon;
#endif
#endif /* __PicasaExtLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


