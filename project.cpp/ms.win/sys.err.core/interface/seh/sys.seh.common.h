#ifndef _SYS_SEH_COMMON_H
#define _SYS_SEH_COMMON_H
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-May-2024 at 08:01:29.8297682, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack system SEH common definition interface declaration file;
*/
#include <atlbase.h>
#include <errno.h>
#include <map>
#include <utility>          // for make_pair();
#include <iterator>

#include "shared.preproc.h" // for getting __CLASS__ that is required in output of CNode::Print();

#include "shared.string.h"
#include "sys.err.codes.h"

#include "shared.types.h"   // using shared::types;

#if(0)
#include "sys.sync_obj.h"   // for getting error fake number safely from multiple threads;
#else
#include <mutex>
namespace shared { namespace safe {

	typedef ::std::lock_guard<std::recursive_mutex> TGuard;
	static  ::std::recursive_mutex TMutex;
}}
#endif

#ifndef __HresultToDword
#define __HresultToDword(_hres) (_hres & 0x0000FFFF)
#endif
#ifndef __DwordToHresult
#define __DwordToHresult(_word)  HRESULT_FROM_WIN32(_word)
#endif
namespace shared { namespace sys_core { namespace seh {

	using namespace shared::types;

	using TString = TStringEx;
	/*
		https://www.boost.org/doc/libs/1_78_0/libs/system/doc/html/system.html ;
		https://learn.microsoft.com/en-us/windows/win32/winsock/error-codes-errno-h-errno-and-wsagetlasterror-2 ;
		
		error and exception codes have different data types compared to each other, for instance:
		DWORD (unsigned long) - exception code, for example, CONTROL_C_EXIT >> STATUS_CONTROL_C_EXIT >> ((DWORD)0xC000013AL) ;
		DWORD << GetLastError() https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-getlasterror ;
		HRESULT << long << COM related functionality ;
		errno_t << int << c-runtime functionality ;
	*/
	typedef LONG errno_l; // makes an error number data type is a little bit different in comparison with integer (int) one;

	typedef EXCEPTION_RECORD   TRecord;    // https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-exception_record ;
	typedef EXCEPTION_POINTERS TPointers;  // https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-exception_pointers ;
	typedef LPCVOID TAddress;
#if (0)
	bool  Acceptable (const TRecord* _record) { return (nullptr != _record); }
	bool  Acceptable (const TPointers* _ptrs) { return (nullptr != _ptrs &&  Acceptable(_ptrs->ExceptionRecord)); }
#else
	class CAccepted {
	public:
		bool operator()(const TRecord* _record) { return (nullptr != _record); }
		bool operator()(const TPointers* _ptrs) { return (nullptr != _ptrs) && CAccepted()(_ptrs->ExceptionRecord); }
	};
#endif

	struct _raw_data {    // this data structure is used for setting the predefined data to exception code, flag, number;
		errno_l  _code; _pc_sz _p_alias; _pc_sz _p_desc;
	};

	// https://stackoverflow.com/questions/9979172/difference-between-node-object-and-element-object ;
	// https://dom.spec.whatwg.org/#concept-node ;
	// https://dom.spec.whatwg.org/#concept-element ;
	class CNode {
	public:
		 CNode (void);
		 CNode (const CNode&);
		 CNode (CNode&&) = delete; // it is not required;
		 CNode (const errno_l _code, _pc_sz _alias, _pc_sz _desc);
		~CNode (void);

	public:
		_pc_sz  Alias (void) const;  // gets a pointer alias of this node;
		bool    Alias (_pc_sz )   ;  // sets new alias, returns true if changed; 

		errno_l Code  (void) const;  // gets node code;
		bool    Code  (errno_l)   ;  // sets node code, if changed, true is returned;

		_pc_sz  Desc  (void) const;  // gets a pointer to the description of this node;
		bool    Desc  (_pc_sz)    ;  // sets new description, returns true if changed;

		bool Is (void) const;        // checks the code value only, returns true if the code does not equal to zero;
#if defined(_DEBUG)
		enum e_print {
			e_all = 0, // prints this class name, alias, code value and description;
			e_req = 1, // prints required info only: alias, code value and description of this element;
		};
		CString  Print(const e_print = e_print::e_req, _pc_sz _p_class = 0) const;
#endif
	public:
		CNode& operator = (const CNode&);
		CNode& operator = (CNode&&) = delete;
		CNode& operator >>(_pc_sz _p_alias);
		CNode& operator <<(errno_l _code);
		CNode& operator <<(_pc_sz _p_desc);

	public:
		operator errno_l (void) const; // returns code value ;
		operator _pc_sz  (void) const; // returns alias name ;

	protected:
		CString  m_alias;
		CString  m_desc ;
		errno_l  m_code ;

	};
	// https://en.wiktionary.org/wiki/zyme ;
	class CZyme {
	public:
		 CZyme (void);
		 CZyme (const CZyme&);
		 CZyme (CZyme&&) = delete;
		~CZyme (void);

	public:
		CZyme& operator = (const CZyme&);
		CZyme& operator = (CZyme&&) = delete;
	};

}}}

#endif/*_SYS_SEH_COMMON_H*/