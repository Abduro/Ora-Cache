#ifndef _MSXML_PROV_NTFS_H_INCLUDED
#define _MSXML_PROV_NTFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Apr-2024 at 00:08:45.2034130, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack MSXML ntfs data provider interface declaration file;
*/
#include "msxml.base.h"

namespace shared { namespace xml { namespace ms { namespace ntfs {

	class CLocator {
	public:
		enum e_finder : uint32_t {
		     e_dll = 0x0, // the finding of module path is made from the dynamic library; this is for MSTest environment especially;
		     e_exe = 0x1, // the finding of module path is made from the executable file; that is from the desktop app;
		};
	public:
		 CLocator (void); CLocator (const CLocator&) = delete; CLocator (CLocator&&) = delete;
		~CLocator (void);

	public:
		_pc_sz   File (void) const;
		TError&  Error(void) const;
		_pc_sz   Path (void) const;

		bool Is_valid (void) const;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		err_code Refresh (const e_finder = e_finder::e_dll);  // gets XML file name and the current path of the exeutable module of the application; 

	private:
		CLocator&  operator = (const CLocator&) = delete;
		CLocator&  operator = (CLocator&&) = delete;

	public:
		mutable
		CError   m_error;
		CString  m_file ;  // this is XML file name only; not path is included;
		CString  m_path ;  // this is the path to the XML file; no file name is included;
	};

	class CProvider : public shared::xml::ms::CProv_Base { typedef shared::xml::ms::CProv_Base TBase;
	public:
		 CProvider (void);
		 CProvider (const CProvider&);
		 CProvider (CProvider&&) = delete;
		~CProvider (void);

	public:
		err_code  Load (_pc_sz _p_file, bool _b_async = false); // opens a file that resides on given path; ToDo: _b_async is not implemented yet; XMLDocument has property of async parsing;

	public:
		CProvider& operator = (const CProvider&);
		CProvider& operator = (CProvider&&) = delete;
	};
}}}}

#endif/*_MSXML_PROV_NTFS_H_INCLUDED*/