#ifndef _SYS_PROCS_LIST_H__INCLUDED
#define _SYS_PROCS_LIST_H__INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Feb-2023 at 12:04:15.5064037, UTC+7, Novosibirsk, Monday;
	This is Process Prying Eyes project system process interface declaration file;
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack system shell lib project on 25-06-2025 on 15:39:45.225, UTC+4, Batumi;
*/
#include "sys.shell.inc.h"

namespace shared { namespace sys_core { namespace shell {

	using CAutoHandle = shared::memory::CHandle;

	class CCertInfo_fake { // this class is created for temporarily replacement of the actual checking a process for a certificate;
	public:
		 CCertInfo_fake (void) {}
		 CCertInfo_fake (const CCertInfo_fake& _src) : CCertInfo_fake() { *this = _src; }
		 CCertInfo_fake (CCertInfo_fake&& _victim) : CCertInfo_fake() { *this = _victim; }
		~CCertInfo_fake (void) {}

	public:
		CCertInfo_fake& operator = (const CCertInfo_fake& _src) { _src; return *this; }
		CCertInfo_fake& operator = (CCertInfo_fake&& _victim) { *this = (const CCertInfo_fake&)_victim; return *this; } 
	};

	typedef CCertInfo_fake TCertInfo;

	typedef ::std::vector<CString> TModules; // process module list;

	class CProcess { // this class does not control a process life-cycle, thus its data can be copied;
	public:
		 CProcess (void) ;
		 CProcess (const CProcess&) ; CProcess (CProcess&&);
		~CProcess (void) ;

	public:
		const
		TCertInfo&Cert (void) const;
		dword     Id   (void) const ;
		bool      Is   (void) const ;   // is true when ID and path are valid, i.e. ID is not zero and process path is not empty;
		_pc_sz    Name (void) const ;   // this is just executable name;
		_pc_sz    Path (void) const ;   // this is full path to executable binary file;
#if defined(_DEBUG)
		CString   Print(const e_print = e_print::e_all) const;
#endif
		const
		TModules& Modules (void) const;
		TModules& Modules (void)      ;

	public:
		CProcess& operator = (const CProcess&);
		CProcess& operator = (CProcess&&) = delete;
		CProcess& operator <<(const TCertInfo&);
		CProcess& operator <<(dword _dw_id);    // no error check is performed when this attribute is set to given value;
		CProcess& operator <<(_pc_sz _name);    // no error check is performed when this attribute is set to given value;
		CProcess& operator >>(_pc_sz _path);    // no error check is performed when this attribute is set to given value;

		CProcess& operator <<(const TModules&); // input data does not have a lot of modules/dlls for one process;

	private:
		dword     m_id  ;
		CString   m_name;
		CString   m_args;
		CString   m_path;
		TCertInfo m_cert;
		TModules  m_dlls; // is not used yet;
	};

	typedef ::std::map<dword, CProcess> TProc_map; // a key is process ID, a value - a process instance;
	typedef ::std::vector<CProcess> TRaw_List;

	class CProcess_List {
	public:
		 CProcess_List (void);
		 CProcess_List (const CProcess_List&); CProcess_List (CProcess_List&&) = delete;
		~CProcess_List (void);

	public:
		TError&   Error (void) const;
		err_code  Get_It(void); // synch method yet;

		const
		TProc_map&  Raw (void) const;

		const
		TRaw_List&  List (void) const;

	public:
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	public:
		CProcess_List& operator = (const CProcess_List&);
		CProcess_List& operator = (CProcess_List&&) = delete;
	private:
		TProc_map m_procs;
		TRaw_List m_list ;
		CError    m_error;
	};

}}}

#endif/*_SYS_PROCS_LIST_H__INCLUDED*/