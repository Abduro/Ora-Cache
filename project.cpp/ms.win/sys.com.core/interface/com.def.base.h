#ifndef _COM_DEF_BASE_H_INCLUDED
#define _COM_DEF_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2025 at 18:08:51.3941346, UTC+4, Batumi, Sunday;
	This is Ebo Pack shared system comp-obj-model wrapper library base interface declaration file;
*/
#include <combaseapi.h>
#include <objbase.h>
#include <guiddef.h>

#include <map>
#include <utility>          // for make_pair();

#include "shared.preproc.h"
#include "shared.string.h"
#include "shared.types.h"

#include "sys.error.h"

namespace shared { namespace sys_core { namespace com {

	using namespace shared::types;

	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-progidfromclsid ;
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-clsidfromprogid ;
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-clsidfromprogidex ; (not used here due to auto-install-proc);
	// ToDo: frankly speaking the classes below shouldn't be declared in this file because, for example, 'CGuid' cannot be used here;
	class CClsId { // this class works as GUID data type wrapper and nothing more :( ;
	public:
		 CClsId (_pc_sz _p_cls_id = _T("")); // creates a class id from string; this is supposed to be guid string representation;
		 CClsId (const _guid& _cls_id);      // assigns a class id from input plain guid data structure;
		 CClsId (const CClsId&);             // just regular copy contructor;
		 CClsId (CClsId&&) = delete;         // not required yet;
		~CClsId (void) = default;

	public:
		CString  Get (void) const;           // gets class guid value as a string;
		bool     Set (_pc_sz _p_cls_id);     // returns true if this class id value is changed, otherwise false;
		bool     Set (const _guid& _cls_id); // sets this class value from input guid; it is supposed that given guid is a class id;

		bool  Is_valid (void) const;      // checks class identifier for not null value; no program id check is involved;

		CString  ProgId (void) const;     // tries to get program identifier from this class guid that is currently set;

#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
		const
		_guid& Raw (void) const;          // gets a reference to raw value of this class identifier; (ra)
		_guid& Raw (void) ;               // gets a reference to raw value of this class identifier; (rw)

	public:
		CClsId&  operator = (const CClsId&);
		CClsId&  operator = (CClsId&&) = delete;      // not required yet;
		CClsId&  operator <<(_pc_sz _p_cls_id);       // creates guid from input string;
		CClsId&  operator <<(const CString& _cls_id); // creates guid from input string;
		CClsId&  operator <<(const   _guid& _cls_id); // sets guid value from the input plain structure argument;

		operator const _guid&  (void) const; // gets class identifier as a plain guid data structure; (gets a reference);
		operator const CString (void) const; // gets class identifier as a string data type;

	public:
		static _guid Get(_pc_sz _p_prog_id); // gets a registered class identifier for input program id; if not registered null guid is returned;
		static  bool Has(_pc_sz _p_prog_id); // checks given program identifier for registered class id; if not registered false is returned;

	private:
		_guid   m_cls_id;
	};
	// there is the code duplication, but it is not important for the time being;
	class CProgId {
	public:
		 CProgId (_pc_sz _p_val = _T(""));  // input argument value is supposed to be a program identifier;
		 CProgId (const _guid& _cls_id);    // tries to intialize a program identifier from the input plain GUID structure;
		 CProgId (const CProgId&);
		 CProgId (CProgId&&) = delete;
		~CProgId (void) = default;

	public:
		_guid    Cls (void) const;    // gets class identifier that is registered for this program id; if not found, null guid is returned;
		_pc_sz   Get (void) const;    // returns program identifier plain text pointer;
		bool     Set (_pc_sz)    ;    // returns true if this class value is changed; sets value of prog id as is;
		bool     Set (const _guid&);  // tries to find registered program identifier for input GUID value;

		bool  Is_valid (void) const;  // returns true if the value is not empty; no format check is made;

		const
		CString& Raw (void) const;    // returns a reference to the raw value of this class; (ra)
		CString& Raw (void);          // returns a reference to the raw value of this class; (rw)

#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif

	public:
		CProgId&  operator = (const CProgId&);
		CProgId&  operator = (CProgId&&) = delete;
		CProgId&  operator <<(_pc_sz _p_val);
		CProgId&  operator <<(const  _guid&);
		CProgId&  operator <<(const CString& _cs_val);

		operator _pc_sz (void) const;

	public:
		static _guid    Cls (_pc_sz _p_prog_id); // returns class guid that is registered for input prog-id arg, or null guid if not found;
		static CString  Get (_pc_sz _p_cls_id);  // if no program id is registered for input class guid, empty string is returned;
		static CString  Get (const _guid&);      // tries to get program identifier from input plain guid data arg value;

		static bool Has (_pc_sz _p_cls_id);      // checks the registry for having program identifier for input plain guid; (text) 
		static bool Has (const _guid& _cls_id);  // checks the registry for having program identifier for input plain guid;

	private:
		CString  p_prog_id;
	};

}}}

#endif/*_COM_DEF_BASE_H_INCLUDED*/