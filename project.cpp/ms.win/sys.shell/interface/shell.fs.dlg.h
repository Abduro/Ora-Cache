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

	// https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/ne-shobjidl_core-_fileopendialogoptions ;

	typedef CComPtr<IFileOpenDialog> IFileOpenDlgPtr;

	class CFileOpts {
	public:
		enum e_common : dword_t {
		e_hidden_yes = FOS_FORCESHOWHIDDEN,    // shows hidden and system items;
		e_no_change_dir = FOS_NOCHANGEDIR,     // don't change the current working directory;
		e_no_mru     = FOS_HIDEMRUPLACES,      // hides the list of places from which the user has recently opened or saved items;
		e_no_okay    = FOS_OKBUTTONNEEDSINTERACTION, // 'OK' button is disabled until the user navigates the view or edits the filename (if applicable);
		e_no_pinned  = FOS_HIDEPINNEDPLACES,   // hides items shown by default in the view's navigation pane;
		e_no_recent  = FOS_DONTADDTORECENT,    // does not allow to add the item being opened or saved to the recent documents list;
		};
		enum e_open : dword_t {
		e_do_prompt  = FOS_CREATEPROMPT,       // prompts for creation if the item returned in the open dialog does not exist;
		e_folder     = FOS_PICKFOLDERS,        // offers a choice of folders rather than files;
		e_links      = FOS_NODEREFERENCELINKS, // shortcuts should not be treated as their target items;
		e_multiple   = FOS_ALLOWMULTISELECT,   // enables to select multiple items in the open dialog;
		e_no_download = (dword_t)FOS_SUPPORTSTREAMABLEITEMS, // indicates that the caller is opening a file as a stream, so there is no need to download that file;
		e_no_stg     = FOS_ALLNONSTORAGEITEMS, // enables to choose any item in the shell namespace;
		e_no_valid   = FOS_NOVALIDATE,         // does not check preventation of file to be open, such as sharing violations or access denied errors;
		e_file_exist = FOS_FILEMUSTEXIST,      // the item returned must exist; this is a default value for the 'Open' dialog;
		e_path_exist = FOS_PATHMUSTEXIST,      // the item returned must be in an existing folder; this is a default value;
		e_preview    = FOS_FORCEPREVIEWPANEON, // indicates to the 'Open' dialog box that the preview pane should always be displayed;
		e_system     = FOS_FORCEFILESYSTEM,    // ensures that returned items are file system items;
		e_violate    = FOS_SHAREAWARE,         // allows a sharing violation when an application is opening a file;
		};
		enum e_save : dword_t {
		e_extended   = FOS_DEFAULTNOMINIMODE,  // allows to open 'Save As' dialog in in expanded mode;
		e_prompt     = FOS_OVERWRITEPROMPT,    // prompt before overwriting an existing file of the same name; is set by default;
		e_no_read    = FOS_NOREADONLYRETURN,   // does not allow to return read-only items; this is a default value for the 'Save' dialog;
		e_no_test    = FOS_NOTESTFILECREATE,   // does not test whether creation of the item as specified in the 'Save' dialog will be successful;
		e_strict     = FOS_STRICTFILETYPES,    // allows to choose a file that has one of the file name extensions;
		};

		CFileOpts (void); CFileOpts (const CFileOpts&) = delete; CFileOpts (CFileOpts&&) = delete; ~CFileOpts (void) = default;

		TError& Error (void) const;

		dword_t  Flags (void) const;
		static
		err_code Get (IFileOpenDlgPtr&, dword_t& _flags, CError&);
		err_code Get (void);

		static bool Has (const e_common, const dword_t _flags); // checks for presenting a specific flag in the given set of flags;
		static bool Has (const e_open, const dword_t _flags);
		static bool Has (const e_save, const dword_t _flags);
		const
		IFileOpenDlgPtr& Ptr (void) const; // gets a reference to 'Open File' dialog smart pointer;
		err_code Ptr (IFileOpenDlgPtr&);   // sets a reference to 'OPen File' dialog interface pointer;

		static
		err_code Set (IFileOpenDlgPtr&, const dword_t flags, CError&);
		err_code Set (const dword_t _dw_flags);

		CFileOpts& operator <<(IFileOpenDlgPtr&); // sets input pointer as 'Open File' dialog interface object;

	private:
		CFileOpts& operator = (const CFileOpts&) = delete; CFileOpts& operator = (CFileOpts&&) = delete;
		CError  m_error;
		dword_t m_flags;
		IFileOpenDlgPtr  m_p_dlg;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ifileopendialog ;
	// https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ifiledialog ;

	class CFileOpen {
	public:
		using COpts = CFileOpts;

		CFileOpen (void); CFileOpen (const CFileOpen&); CFileOpen (CFileOpen&&) = delete; ~CFileOpen (void) = default;

		err_code Do (_pc_sz _p_title, const HWND _h_owner);

		TError& Error (void) const;
		const
		CFilter& Filter (void) const;
		CFilter& Filter (void) ;
		const
		COpts&   Opts (void) const; // gets the reference to 'Open File' interface object in order to get/set options for configuring the dialog; (ro)
		COpts&   Opts (void) ;      // gets the reference to 'Open File' interface object in order to get/set options for configuring the dialog; (rw)
		const
		CString& Selected (void) const;

	private:
		CFileOpen& operator = (const CFileOpen&) = delete; CFileOpen& operator = (CFileOpen&&) = delete;
		mutable
		CError   m_error;
		CFilter  m_filter;
		COpts    m_opts;     // this is options that are used for open dialog 'Show' method;
		CString  m_selected;
		IFileOpenDlgPtr m_p_dlg;
	};

}}}}

#endif/*_SHELL_FS_DLG_H_INCLUDED*/