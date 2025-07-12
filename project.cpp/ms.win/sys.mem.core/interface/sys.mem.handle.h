#ifndef _SHAREDLITEGENERICHANDLE_H_INCLUDED
#define _SHAREDLITEGENERICHANDLE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Apr-2010 at 1:56:43am, Rostov-on-Don, GMT+3, Thursday;
	This is SfxSOA Base Service Memory management class(es) declaration file. [voluntary project]
	-----------------------------------------------------------------------------
	Adopted to Platinum project on 29-Nov-2014 at 0:42:43am, GMT+3, Taganrog, Saturday; (https://platinumpayroll.co.nz) [oDesk.com]
	Adopted to File Guardian project on 27-May-2018 at 3:21:42p, UTC+7, Phuket, Rawai, Sunday; (https://thefileguardian.com/) [Upwork.com]
	Adopted to Geometry Curve project on 17-Feb-2024 at 13:00:28.5230765, UTC+7, Novosibirsk, Saturday; [trying to find work in software ]
*/
#include <atlbase.h>        // for avoiding fatal error C1189: #error:  "No Target Architecture" ;
#include <handleapi.h>      // for GetHandleInformation(), for checking a handle validity;

#include "sys.err.codes.h"
#include "sys.error.h"
#include "sys.sync_obj.h"

#include "shared.string.h"
#include "shared.types.h"

#ifndef __inv_handle_val
#define __inv_handle_val INVALID_HANDLE_VALUE
#endif
/*
namespace SfxSOA { namespace Base { namespace System { namespace Memory {*/
namespace shared { namespace memory
{
	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = shared::common::CString_Ex;
	// https://learn.microsoft.com/en-us/windows/win32/memory/memory-management-functions#bad-memory-functions ;
	using namespace shared::types;
#pragma region __refs_5
	// https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-duplicatehandle ;
	// https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-gethandleinformation ;
	// https://stackoverflow.com/questions/5603625/how-to-check-if-a-handle-is-valid-or-not ;
#pragma endregion
	class CHandle { // in many case or even always, a handle is created or open for different system objects, it is the reason for absence of Open() method of this class; 
	public:
		 CHandle (const handle = __inv_handle_val, bool _b_managed = false); // if handle value is set, this class takes an ownership on its value if required;
		 CHandle (const CHandle&);                            // duplicates a handle;
		 CHandle (CHandle&&)/* = delete*/;                    // required for an element management of the container, for instance, ::std::map;
		~CHandle (void);                                      // destroys encapsulated handle automatically if any;

	public:
		err_code Attach(const handle, bool _manage = false) ; // attaches an input handle value, takes an ownership over it if required;
		handle   Detach(void) ;                               // detaches from the handle that is assigned to this class;

		err_code Clone (const handle _h_source);              // makes a clone of input handle; handle manage flag is set to true;
		err_code Close (void) ;                               // closes the encapsulated handle; returns no error if succeeded;

		TError&  Error (void) const;                          // no comments;

		const bool Is  (void) const;                          // checks a handle validity; calls to GetHandleInformation();
		const bool Managed (void) const;                      // indicates the life cycle of encapsulated handle is controlled or not;
		const bool Managed (bool _yes_or_no);                 // turns off or on the control over life cycle of encapsulated handle value;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		const
		handle&  Value (void) const;                          // gets a value of that is currently set to this class object;
		err_code Value (const handle&, bool _b_clone = true); // sets new handle value, if clone option is on, input handle is duplicated;

	public:
		CHandle& operator = (const CHandle&);          // duplicates a handle of input source object;
		CHandle& operator = (CHandle&&)/* = delete*/;  // required for an element management of the container;
		CHandle& operator = (const handle&);           // assigns a handle by making a duplication of input one;
		CHandle& operator <<(const bool _b_manage);    // sets the handle life cycle management flag;
		CHandle& operator <<(const handle&);           // attaches to input handle and takes an ownership over it;
		CHandle& operator >>(handle& _out );           // detaches to input handle;
		handle*  operator & (void);

	public:
		operator bool (void) const;                // checks a validity of the assigned handle and returns the check result;
		operator handle (void) const;

	public:
		static   err_code Close(handle& _handle);  // closes an input handle, returns error code in case when closing is not succeeded;
		static   err_code Is (const handle);       // returns *no* error in case when input handle is valid, otherwise an *error* code; ToDo: name must to be reviewed;
	
	protected:
		mutable
		CError   m_error;
		handle   m_value;   // a handle value, actually an address of pointer to memory block of void type;
		bool     m_managed; // ththis flag indicates a handle value is manageable, thus must be destroyed automatically if necessary;
	};

#if (0)
	class CAutoHandleArray
	{
	private:
		handle*    m_handles;
		dword      m_size;
		CError     m_error;
	public:
	    CAutoHandleArray(const dword dwSize);
	   ~CAutoHandleArray(void);
	public:
		TErrorRef  Error  (void)const;
		bool       Is     (void)const;
		handle*    Handles(void)const;
		dword      Size   (void)const;
	public:
		handle     operator[] (const INT) const;
		handle&    operator[] (const INT)      ;
	private:
		CAutoHandleArray(const CAutoHandleArray&);
		CAutoHandleArray& operator= (const CAutoHandleArray&);
	};
#endif
	using shared::sys_core::CSyncObject;
#if (0)
	//
	// TODO: actually the handle needs reference counting, otherwise, protected access doesn't protect from
	//       destroying the handle while it is still used in one of the worker threads;
	//       using of ::std::shared_ptr<> is would be better approach;
	//
	class CHandleSafe
	{
	private:
		handle      m_handle  ;
		CSyncObject m_sync_obj;
	public:
		 CHandleSafe(const handle = __inv_handle_val);
		~CHandleSafe(void);
	public:
		CHandleSafe& operator=(const handle);
	public:
		operator    handle(void);
		operator    handle(void) const;
	public:
		handle*     operator&(void);
	private:
		CHandleSafe(const CHandleSafe&);
		CHandleSafe& operator= (const CHandleSafe&);
	public:
		handle      Handle (void) const;
		bool        Is     (void) const;
		void        Reset  (void);
	};
#endif
#if (0)
	class CStdHandle : public CAutoHandle {
	                  typedef CAutoHandle THandle;
	protected:
		dword     m_std_type;
		CError    m_error;

	public:
		 CStdHandle (const dword _handle_type);
		~CStdHandle (void);

	public:
		HRESULT   Close(void)      ;
		TErrorRef Error(void) const;
		dword     Type (void) const;
	public:
		CStdHandle& operator=(const handle);
	};
#endif
}}

typedef shared::memory::CHandle THandle; // for avoiding error C2872: 'CHandle': ambiguous symbol with ATL::CHandle;

#endif/*_SHAREDLITEGENERICHANDLE_H_INCLUDED*/