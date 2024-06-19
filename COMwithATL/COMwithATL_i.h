

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for COMwithATL.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __COMwithATL_i_h__
#define __COMwithATL_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IATLSimpleObject1_FWD_DEFINED__
#define __IATLSimpleObject1_FWD_DEFINED__
typedef interface IATLSimpleObject1 IATLSimpleObject1;

#endif 	/* __IATLSimpleObject1_FWD_DEFINED__ */


#ifndef __ATLSimpleObject1_FWD_DEFINED__
#define __ATLSimpleObject1_FWD_DEFINED__

#ifdef __cplusplus
typedef class ATLSimpleObject1 ATLSimpleObject1;
#else
typedef struct ATLSimpleObject1 ATLSimpleObject1;
#endif /* __cplusplus */

#endif 	/* __ATLSimpleObject1_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IATLSimpleObject1_INTERFACE_DEFINED__
#define __IATLSimpleObject1_INTERFACE_DEFINED__

/* interface IATLSimpleObject1 */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IATLSimpleObject1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7fe23f27-a903-4296-878f-11331aa2beec")
    IATLSimpleObject1 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PrintHelloWorld( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CalculateCircleArea( 
            /* [in] */ DOUBLE radius,
            /* [retval][out] */ DOUBLE *area) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IATLSimpleObject1Vtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IATLSimpleObject1 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IATLSimpleObject1 * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IATLSimpleObject1 * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IATLSimpleObject1 * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IATLSimpleObject1 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IATLSimpleObject1 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IATLSimpleObject1 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IATLSimpleObject1, PrintHelloWorld)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PrintHelloWorld )( 
            IATLSimpleObject1 * This);
        
        DECLSPEC_XFGVIRT(IATLSimpleObject1, CalculateCircleArea)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CalculateCircleArea )( 
            IATLSimpleObject1 * This,
            /* [in] */ DOUBLE radius,
            /* [retval][out] */ DOUBLE *area);
        
        END_INTERFACE
    } IATLSimpleObject1Vtbl;

    interface IATLSimpleObject1
    {
        CONST_VTBL struct IATLSimpleObject1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IATLSimpleObject1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IATLSimpleObject1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IATLSimpleObject1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IATLSimpleObject1_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IATLSimpleObject1_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IATLSimpleObject1_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IATLSimpleObject1_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IATLSimpleObject1_PrintHelloWorld(This)	\
    ( (This)->lpVtbl -> PrintHelloWorld(This) ) 

#define IATLSimpleObject1_CalculateCircleArea(This,radius,area)	\
    ( (This)->lpVtbl -> CalculateCircleArea(This,radius,area) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IATLSimpleObject1_INTERFACE_DEFINED__ */



#ifndef __COMwithATLLib_LIBRARY_DEFINED__
#define __COMwithATLLib_LIBRARY_DEFINED__

/* library COMwithATLLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_COMwithATLLib;

EXTERN_C const CLSID CLSID_ATLSimpleObject1;

#ifdef __cplusplus

class DECLSPEC_UUID("bd17af18-97bd-4dc3-ae82-a97335617070")
ATLSimpleObject1;
#endif
#endif /* __COMwithATLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


