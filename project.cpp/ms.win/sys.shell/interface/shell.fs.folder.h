#ifndef _SHAREDFILESYSTEM_H_42494520_2884_4ba8_9BBD_450E6620FC22_INCLUDED
#define _SHAREDFILESYSTEM_H_42494520_2884_4ba8_9BBD_450E6620FC22_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jun-2016 at 1:11:46p, GMT+7, Phuket, Rawai, Saturday;
	This is shared NTFS library generic folder class(es) declaration file; (thefileguardian.com)
	-----------------------------------------------------------------------------
	Adopted to VS v15 on 9-Jul-2018 at 6:02:31p, UTC+7, Phuket, Rawai, Monday;
*/
#include "sys.shell.inc.h"

// https://learn.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation ;

namespace shared { namespace shell { namespace ntfs {

	using namespace shared::sys_core::shell;

	typedef ::std::vector<CString> TFileList  ;         // just file names collection of the files for concret directory/folder;
	typedef ::std::map<CString, TFileList> TFolderList; // the element key is the folder path, the value is the list of files there;

	class CFolder {
	public:
		 CFolder (void); CFolder (const CFolder&) = delete; CFolder (CFolder&&) = delete;
		~CFolder (void);

	public:
		err_code  EnumItems(TFileList& _files, TFolderList& _subfolders, _pc_sz lpszMask = _T("*")); // enumerates items in specific folder only, no recursion;
		TError&   Error (void) const;

#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif

	private:
		CFolder&  operator = (const CFolder&) = delete; CFolder& operator = (CFolder&&) = delete;
		CError    m_error;
	};

}}}

// this namespace with the class CFolder inside of it is just alternative way of dealing with file system in comparison with the shell class above;
namespace shared { namespace user_32 { namespace ntfs {

	using namespace shared::sys_core::shell;

	using TFindData = WIN32_FIND_DATA;

	typedef ::std::vector<CString> TFileList  ;         // just file names collection of the files for concret directory/folder;
	typedef ::std::map<CString, TFileList> TFolderList; // the element key is the folder path, the value is the list of files there;

	class CFolder;
	typedef ::std::vector<CFolder> TSubDirs;

	class CFolder {
	public:
		 CFolder (void); CFolder (const CFolder&); CFolder (CFolder&&);
		~CFolder (void);

	public:
		err_code  EnumItems (void);    // enumerates files and sub-folders;

		TError&   Error (void) const;
		bool   Is_valid (void) const;  // it returns 'true' in case if the path is set and nothing more specific;

		const
		TFileList& Files(void) const;  // gets a reference to the file list; (ro);

		_pc_sz    Path  (void) const;  // gets the path for wrapped folder by this class;
		err_code  Path  (_pc_sz)    ;  // sets the path for wrapped folder by this class, if the input path does not exist, the error code is returned;

#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		const
		TSubDirs& SubDirs (void) const; // just gets a reference to subfolders map; this map may contain only one folder that is set for enumerating;

	public:
		CFolder&  operator = (const CFolder&);
		CFolder&  operator = (CFolder&&);  // neither swap() nor move() methods applied, but copying data only;
	private:
		CFolder&  operator <<(_pc_sz _path);
		CFolder&  operator <<(const TFileList&);
		CFolder&  operator <<(const TSubDirs&);

	private:
		CError    m_error;
		CString   m_path ; // this is absolute path to the folder that is used by this class for enumerating its (this folder) sub-folders and files;

		TSubDirs  m_subdirs;
		TFileList m_files; // file names that this folder holds inside ;
	};
}}}

#endif/*_SHAREDFILESYSTEM_H_42494520_2884_4ba8_9BBD_450E6620FC22_INCLUDED*/