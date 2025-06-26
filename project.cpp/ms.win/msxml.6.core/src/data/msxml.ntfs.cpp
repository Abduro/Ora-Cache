/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Apr-2024 at 00:17:33.8665231, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack MSXML ntfs data provider interface implementation file;
*/
#include "msxml.ntfs.h"

using namespace shared::xml::ms;
using namespace shared::xml::ms::ntfs;

#ifndef __max_path_len
#define __max_path_len 512
#endif

/////////////////////////////////////////////////////////////////////////////

CLocator:: CLocator (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CLocator::~CLocator (void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz   CLocator::File  (void) const { return (_pc_sz)this->m_file; }
TError&  CLocator::Error (void) const { return this->m_error; }
_pc_sz   CLocator::Path  (void) const { return (_pc_sz)this->m_path; }

bool  CLocator::Is_valid (void) const {

	this->m_error << __METHOD__ << __s_ok;

	if (this->m_file.IsEmpty() || this->m_path.IsEmpty()) {
		this->m_error << __e_not_inited;
		return false;
	}

	CString cs_full_path;

	cs_full_path += this->Path();
	cs_full_path += this->File();

	// https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathfileexistsa ;

	const bool b_valid = !!::PathFileExists((_pc_sz)cs_full_path);
	if (false == b_valid)
		this->m_error.Last();

	return b_valid;
}

#if defined(_DEBUG)
CString  CLocator::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("csl::[%s::%s] >> {file=%s;path=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("csl::[%s] >> {file=%s;path=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("file=%s;path=%s;valid=%s");

	CString cs_file = this->m_file.IsEmpty() ? _T("#na") : this->File();
	CString cs_path = this->m_path.IsEmpty() ? _T("#na") : this->Path();
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		(_pc_sz) cs_file, (_pc_sz) cs_path, (_pc_sz) cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz) cs_file, (_pc_sz) cs_path, (_pc_sz) cs_valid);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r,
		(_pc_sz) cs_file, (_pc_sz) cs_path, (_pc_sz) cs_valid);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

err_code CLocator::Refresh (const e_finder _e_what_is) {
	this->m_error << __METHOD__ << __s_ok;

	// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamea ;
	t_char sz_path[__max_path_len] = {0};

	HMODULE h_module = nullptr;

	if (e_finder::e_dll == _e_what_is) {

		CString cs_module(_T("ebo_test_$9$.msxml.dll")); // this is predefined project name for running under MSTest unit testing;

		// https://stackoverflow.com/questions/6924195/get-dll-path-at-runtime ;
		// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandleexa 
		static dword dw_flags = /*GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | */GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;

		if (false == ::GetModuleHandleEx (dw_flags, cs_module.GetBuffer(), &h_module))
			return this->m_error.Last();
	}

	const dword dw_result = ::GetModuleFileName(h_module, sz_path, _countof(sz_path));

	this->m_error.Last(); // error_insufficient_buffer is not expected but nevertheless;

	if (this->Error().Is())
		return this->Error();

	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/splitpath-s-wsplitpath-s ;

	t_char sz_drv_[_MAX_DRIVE] = {0}; t_char sz_dir_[_MAX_DIR] = {0}; t_char sz_file[_MAX_FNAME] = {0}; t_char sz_ext[_MAX_EXT] = {0};

	const errno_t n_result = ::_tsplitpath_s(
		sz_path, sz_drv_, _countof(sz_drv_), sz_dir_, _countof(sz_dir_), sz_file, _countof(sz_file), sz_ext, _countof(sz_ext)
	);
	if (!!n_result)
		return this->m_error = (dword)n_result; // it is assumed the error code of win32 is positive;

	if (this->m_file.IsEmpty() == false) this->m_file.Empty();
	if (this->m_path.IsEmpty() == false) this->m_path.Empty();

	this->m_path += sz_drv_;
	this->m_path += sz_dir_;

	this->m_file += sz_file;
	this->m_file += _T(".xml");

	this->Is_valid(); // just for checking existance of the file which path has been just composed;

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CProvider:: CProvider (void) : TBase() { TBase::m_error >> __CLASS__; }
CProvider:: CProvider (const CProvider& _ref) : CProvider() { *this = _ref; }
CProvider::~CProvider (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code    CProvider::Load (_pc_sz _p_sz_path, bool b_async) {
	_p_sz_path; b_async;

	TBase::m_error << __METHOD__ << TErrCodes::no_error;

	if (TBase::Doc().Is() == false)
		TBase::Doc().Create();

	if (TBase::Doc().Error().Is())
		return TBase::m_error = TBase::Doc().Error();

	TBase::Doc().Load(_p_sz_path);
	if (TBase::Doc().Error().Is())
		return TBase::m_error = TBase::Doc().Error(); // taking into account the error is contained in child error object, the parent does not know about it :(

	return TBase::Error();
}


/////////////////////////////////////////////////////////////////////////////

CProvider&  CProvider::operator = (const CProvider& _ref) { (TBase&)*this = (const TBase&)_ref; return *this; }