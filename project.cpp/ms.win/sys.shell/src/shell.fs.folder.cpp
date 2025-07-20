/*
	Created by Tech_dog (ebontrop@gmail.com) on 7-Jun-2016 at 4:55:53p, GMT+7, Phuket, Rawai, Tuesday;
	This is shared NTFS library generic file class(es) implementation file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 27-May-2018 at 3:25:45p, UTC+7, Phuket, Rawai, Sunday;
	Adopted to Ebo Pack on 11-Sep-2019 at 01:00:37a, UTC+7, Novosibirsk, Wednesday;
*/
#include "shell.fs.folder.h"

using TFindData = WIN32_FIND_DATA;
/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace shell { namespace ntfs {

CFolder:: CFolder (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CFolder::~CFolder (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code  CFolder::EnumItems(TFileList& _files, TFolderList& _subfolders, _pc_sz lpszMask/* = _T("*")*/) {
	_files; _subfolders; lpszMask;
	this->m_error <<__METHOD__<<__s_ok;

	return this->Error();
}

TError&   CFolder::Error (void) const { return this->m_error; }

}}}

namespace shared { namespace user_32 { namespace ntfs {
namespace _impl  {

	class CEnumerator {
	public:
		CEnumerator (void) {}
	
	};

}

using namespace _impl;

CFolder:: CFolder (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CFolder:: CFolder (const CFolder& _src) : CFolder() { *this = _src; }
CFolder:: CFolder (CFolder&& _victim) : CFolder() { *this = _victim; }
CFolder::~CFolder (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code  CFolder::EnumItems (_pc_sz _p_ext/* = _T("*")*/) {
	_p_ext;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false)
		return this->m_error << __e_not_inited = _T("No target folder path is set");

	if (this->m_files.empty() == false)
		this->m_files.clear();

	if (this->m_subdirs.empty() == false)
		this->m_subdirs.clear();

	CString cs_query;
	cs_query.Format(_T("%s\\%s"), this->Path(), _T("*")); // selects all files for enumerating, the extention of the each file will be checked below;

	CString cs_ext(_p_ext);

	// https://learn.microsoft.com/en-us/windows/win32/fileio/listing-the-files-in-a-directory ;

	TFindData data_ = {0};
	HANDLE h_found  = ::FindFirstFile((_pc_sz) cs_query, &data_); // https://learn.microsoft.com/en-us/windows/win32/api/FileAPI/nf-fileapi-findfirstfilea ;

	if (__inv_handle_val == h_found) {
		this->m_error.Last();

		if (this->m_error.Result() == (err_code)TErrCodes::ePath::eNoFile) // the currently set directory or path is empty;
			this->m_error << __s_ok;

		return this->Error();
	}
	do {
		CString cs_name = data_.cFileName;

		if (!!(FILE_ATTRIBUTE_DIRECTORY & data_.dwFileAttributes)) {

			CString cs_folder = cs_name;
			
			if (cs_folder.GetAt(0) != _T('.')){ // checks for special folder names (parent and root folders) ;

				cs_folder.Format(_T("%s%s"), this->Path(), data_.cFileName);

				CFolder sub_dir;
				if (__failed(sub_dir.Path((_pc_sz) cs_folder))) {
					this->m_error = sub_dir.Error(); break;
				}
				if (__failed(sub_dir.EnumItems(_p_ext))) {
					this->m_error = sub_dir.Error(); break;
				}

				try {
					this->m_subdirs.push_back(sub_dir);
				}
				catch (const ::std::bad_alloc&) {
					this->m_error << __e_no_memory; break;
				}
			}
		}
		else {
			try {
				if (_p_ext && 0 == cs_ext.CompareNoCase(cs_name.Right(static_cast<int>(::_tcslen(_p_ext))))) {
					this->m_files.push_back(cs_name);
				}
				else if (nullptr == _p_ext)
					this->m_files.push_back(cs_name);
			}
			catch (const ::std::bad_alloc&) {
				this->m_error << __e_no_memory; break;
			}
		}

	} while (::FindNextFileW(h_found, &data_));

	if (0 == ::FindClose(h_found)) // https://learn.microsoft.com/en-us/windows/win32/api/FileAPI/nf-fileapi-findclose ;
		this->m_error.Last();

	return this->Error();
}

TError&   CFolder::Error (void) const { return this->m_error; }
const
TFileList& CFolder::Files (void) const { return this->m_files; }

bool      CFolder::Is_valid (void) const { return this->m_path.IsEmpty() == false; }

_pc_sz    CFolder::Path  (void) const { return this->m_path.GetString(); }
err_code  CFolder::Path  (_pc_sz _p_path) {
	_p_path;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_path || 0 == ::_tcslen(_p_path))
		return this->m_error << __e_inv_arg;

	// https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathfileexistsa ;
	if (false == !!::PathFileExists(_p_path))
		return this->m_error << (err_code) TErrCodes::ePath::eNoPath;

	if (0 == this->m_path.CompareNoCase(_p_path)) // no error is thrown and no cleaning data up is made;
		return this->Error();

	this->m_path = _p_path;

	this->m_subdirs.clear(); // this means that the list of subfolders of newly set path must be cleared and enumerated again;
	this->m_files.clear();

	return this->Error();
}

#if defined(_DEBUG)
CString   CFolder::Print (const e_print _e_opt, _pc_sz _p_pfx/* = _T("\t\t")*/, _pc_sz _p_sfx/* = _T("\n")*/) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%spath=%s;valid=%s;%s%sfiles:%s%s%ssubdirs:%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {%s%spath=%s;valid=%s;%s%sfiles:%s%s%ssubdirs:%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s%spath=%s;valid=%s;%s%sfiles:%s%s%ssubdirs:%s}");

	CString cs_path  = this->m_path.IsEmpty() ? _T("#not_set") : this->Path();
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_files;
	for (uint32_t i_ = 0; i_ < this->Files().size(); i_++) {
		cs_files += _p_sfx;
		cs_files += _p_pfx;
		cs_files += this->Files().at(i_);
	}
	if (cs_files.IsEmpty()) {
		cs_files += _p_sfx;
		cs_files += _p_pfx;
		cs_files += _T("no files;");
	}

	CString cs_dirs;
	for (uint32_t i_ = 0; i_ < this->SubDirs().size(); i_++) {
		cs_dirs += _p_sfx;
		cs_dirs += _p_pfx;
		cs_dirs += this->SubDirs().at(i_).Print(_e_opt, _p_pfx, _p_sfx);
	}
	if (cs_dirs.IsEmpty()) {
		cs_dirs += _p_sfx;
		cs_dirs += _p_pfx;
		cs_dirs += _T("no sub-dirs;");
		cs_dirs += _p_sfx;
		cs_dirs += _p_pfx;
	}

	CString cs_out;

	if (e_print::e_all == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_path , (_pc_sz) cs_valid,
		_p_sfx, _p_pfx, (_pc_sz) cs_files,
		_p_sfx, _p_pfx, (_pc_sz) cs_dirs );
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_path , (_pc_sz) cs_valid,
		_p_sfx, _p_pfx, (_pc_sz) cs_files,
		_p_sfx, _p_pfx, (_pc_sz) cs_dirs );
	}
	if (e_print::e_req == _e_opt) { cs_out.Format (pc_sz_pat_r,
		_p_sfx, _p_pfx, (_pc_sz) cs_path , (_pc_sz) cs_valid,
		_p_sfx, _p_pfx, (_pc_sz) cs_files,
		_p_sfx, _p_pfx, (_pc_sz) cs_dirs );
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	
	return  cs_out;
}
#endif

const
TSubDirs& CFolder::SubDirs (void) const { return this->m_subdirs; }

/////////////////////////////////////////////////////////////////////////////

CFolder&  CFolder::operator = (const CFolder& _src) { *this << _src.Files() << _src.SubDirs() << _src.Path(); return *this; }
CFolder&  CFolder::operator = (CFolder&& _victim) { *this = (const CFolder&)_victim; return *this; }

CFolder&  CFolder::operator <<(_pc_sz _path) {  this->m_path = _path; return *this; }
CFolder&  CFolder::operator <<(const TFileList& _files) {  this->m_files = _files; return *this; }
CFolder&  CFolder::operator <<(const TSubDirs& _dirs)  { this->m_subdirs = _dirs; return *this; }

}}}