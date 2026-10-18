#ifndef _SHELL_FS_DLG_H_INCLUDED
#define _SHELL_FS_DLG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.ru) on 16-Oct-2026 at 18:39:38.488, UTC+4, Batumi, Friday;
	This is system shell dialogs' wrapper interface declaration file;
*/
#include "sys.shell.inc.h"

namespace shared { namespace shell { namespace ntfs { namespace dialogs { using namespace shared::sys_core::shell;

#if (0)
	typedef ::std::vector<COMDLG_FILTERSPEC> flt_items_t; // this does not work, due to the structure consists of pointers to strings;
	typedef ::std::map<CString, CString> item_map_t   ;   // the key is a spec, the value is a name;
#else
	typedef ::std::vector<::std::pair<CString, CString>> flt_items_t; // the pair second() is spec, the pair first() is element name;
#endif
	class CFilter {
	public:
		CFilter (void); CFilter (const CFilter&) = delete; CFilter (CFilter&&) = delete; ~CFilter (void) = default;

		err_code Append (_pc_sz _p_name, _pc_sz _p_spec);

		TError&   Error (void) const;
		bool   Is_valid (void) const;

		const
		flt_items_t& Items (void) const;
		flt_items_t& Items (void) ;

	private:
		CFilter& operator = (const CFilter&) = delete; CFilter& operator = (CFilter&&) = delete;
		flt_items_t m_items;
		CError      m_error;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ifileopendialog ;
	// https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ifiledialog ;

	class CFileOpen {
	public:
		CFileOpen (void); CFileOpen (const CFileOpen&); CFileOpen (CFileOpen&&) = delete; ~CFileOpen (void) = default;

		err_code Do (_pc_sz _p_title, const HWND _h_owner);

		TError& Error (void) const;
		const
		CFilter& Filter (void) const;
		CFilter& Filter (void) ;
		const
		CString& Selected (void) const;

	private:
		CFileOpen& operator = (const CFileOpen&) = delete; CFileOpen& operator = (CFileOpen&&) = delete;
		mutable
		CError  m_error;
		CFilter m_filter;
		CString m_selected;
	};

}}}}

#endif/*_SHELL_FS_DLG_H_INCLUDED*/