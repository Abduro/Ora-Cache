/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jul-2026 at 20:17:59.904, UTC+4, Batumi, Wednesday;
	This is 3D module object file loader interface implementation file;
*/
#include "obj_parser.load.h"
#include "console.format.h"

using namespace ::shared::parsers::obj;

namespace shared { namespace parsers { namespace _impl {

	class CFile {
	public:
		 CFile (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_false = _T("No file path is checked yet"); }
		 CFile (const CFile&) = delete; CFile (CFile&&) = delete;
		~CFile (void) = default;

		TError& Error (void) const { return this->m_error; }

		err_code Is_valid (_pc_sz _p_path) const {
			_p_path;
			this->m_error <<__METHOD__<<__s_ok;
			if (nullptr == _p_path || _MAX_DRIVE >= ::_tcslen(_p_path)) {
				return this->m_error <<__e_inv_arg  = _T("The input path is invalid");
			}
			/* https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesa ;
			   https://learn.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants ;
			   Starting with Windows 10, Version 1607, you can opt-in to remove the MAX_PATH limitation without prepending "\\?\".
			*/
			const dword attrs = ::GetFileAttributes(_p_path);
			if (INVALID_FILE_ATTRIBUTES == attrs)
				return this->m_error.Last();
			if (FILE_ATTRIBUTE_DIRECTORY & attrs)
				return this->m_error <<__e_inv_arg = _T("Input path specifies the directory");

			return this->Error();
		}

	private:
		CFile& operator = (const CFile&) = delete; CFile& operator = (CFile&&) = delete;
		mutable
		CError m_error;
	};

}}} using namespace ::shared::parsers::_impl;

#pragma region cls::CBase{}

using CBase = ::shared::parsers::obj::CBase;

CBase::CBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CBase::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CLoader{}

// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-s-wfopen-s ;
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s ;
#if defined (_UNICODE)
#define fopen_s _wfopen_s
#define strerror_s _wcserror_s
#else
#define strerror_s strerror_s
#define fopen_s fopen_s
#endif

CLoader:: CLoader (void) : TBase(), m_p_file(0) { TBase::m_error >>__CLASS__<<__s_false = _T("No object file is loaded yet"); }
CLoader::~CLoader (void) {
	if (this->Is_opened()) this->Close();
}

err_code CLoader::Close (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (false == this->Is_opened()) {
		__trace_warn_2(_T("No file been opened"));
		return TBase::Error();
	}
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fclose-fcloseall ;
	const errno_t n_result = ::fclose(this->m_p_file);
	if (!!n_result) {
		TBase::m_error << (err_code) TErrCodes::eAccess::eDenied = _T("File close failed");
	}
	else
		this->m_p_file = 0;
	return TBase::Error();
}

bool CLoader::Is_opened (void) const { return nullptr != this->m_p_file; }

err_code CLoader::Open (_pc_sz _path) {
	_path;
	TBase::m_error <<__METHOD__<<__s_ok;

	CFile file;
	if (__failed(file.Is_valid(_path)))
		return TBase::m_error = file.Error();

	if (nullptr != this->m_p_file) {
		return TBase::m_error << (err_code) TErrCodes::eObject::eInited = _T("The file is already open");
	}
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/errno-doserrno-sys-errlist-and-sys-nerr ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/errno-constants ;
	const errno_t n_result = fopen_s(&this->m_p_file, _path, _T("r"));
	if (!!n_result) {
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s ;
		static const size_t req_len = 256u;
		t_char buffer[req_len] = {0};
		if (!!strerror_s(buffer, req_len, n_result)) {}

		return (TBase::m_error = static_cast<dword>(n_result)) = TString().Format(_T("File open failed: errno = %d"), n_result); 
	}
	CString cs_path(_path);
	if (cs_path.GetLength() > 40) {
		cs_path = TString().Format(_T("%s...%s"), (_pc_sz) cs_path.Left(20), (_pc_sz) cs_path.Right(20));
	}

	__trace_info_2(_T("The file '%s' is opened;\n"), (_pc_sz) cs_path);

	return TBase::Error();
}

#pragma endregion
#pragma region cls::CLocator{}

static _pc_sz p_obj_path = _T("obj_path");
static _pc_sz p_err_locate = _T("No object file is located yet");

CLocator::CLocator (void) : TBase() { TBase::m_error >>__CLASS__<<__s_false = p_err_locate; }

bool  CLocator::Is_found (void) const {
	bool b_found = false;
	TBase::m_error <<__METHOD__<<__s_false = p_err_locate;

	if (this->m_obj_path.IsEmpty())
		return b_found;

	CFile file;
	if (__failed(file.Is_valid(this->m_obj_path)))
		TBase::m_error = file.Error();
	else
		b_found = true;

	return b_found;
}

err_code CLocator::Locate (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	CFile file;
	// (1) checks command line first;
	using
	CCmdLine = ::shared::input::CCmdLine;
	CCmdLine cmd_ln;
	if (__failed(cmd_ln.Parse()))
		return TBase::m_error = cmd_ln.Error();
	if (cmd_ln.Has(p_obj_path)) {
		this->m_obj_path = cmd_ln.Arg(p_obj_path);

		if (__failed(file.Is_valid(this->m_obj_path)))
			return TBase::m_error = file.Error();
	}

	if (this->m_obj_path.IsEmpty() == false)
		return TBase::Error();
	// (2) checks the registry root key for value named 'p_obj_path';
	TRegKeyEx the_key;
	this->m_obj_path = the_key.Value().GetString(CLocator::Root(), p_obj_path);
	if (the_key.Error()) {
		::__trace_err_ex_2(the_key.Error());
	}

	if (this->m_obj_path.IsEmpty() == false)
		return TBase::Error();

	if (__failed(file.Is_valid(this->m_obj_path)))
		TBase::m_error = file.Error();
	else {
		using CFormat = ::shared::console::CFormat;
		__trace_impt_2(_T("The object file path:\n%s%s;\n"), CFormat::Indent(), this->Path());
	}

	return TBase::Error();
}

_pc_sz CLocator::Path (void) const { return (_pc_sz) this->m_obj_path; }

_pc_sz CLocator::Root (void) {

	static CString cs_root;
	if (cs_root.IsEmpty()) {
		cs_root = TString().Format(_T("%s\\Utils\\ObjParser"), ::Get_reg_router().Root().Path());
	}

	return (_pc_sz) cs_root;
}

#pragma endregion
#pragma region cls::CReader{}

CReader::CReader (void) : TBase() { TBase::m_error >>__CLASS__<<__s_ok; }

err_code CReader::Read (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	CLocator locator;

	// (1) checks the locator first;
	if (false == locator.Is_found()) { // the file path is empty or does not exist if the file path is read from command line or the registry;
		if (locator.Error()) { // this error is set by locator.Is_found();
			return TBase::m_error = locator.Error(); // returns the error;
		}

		if (__failed(locator.Locate())) { // it is suppossed to try to locate an object file again;
			return TBase::m_error = locator.Error(); // file path is found, but the file does not exist or is the directory;
		}
	}
	// (2) the locator contains the path to the file that is suppossed to be an model object file; tries to opent the file;
	CLoader loader;
	if (__failed(loader.Open(locator.Path()))) {
		return TBase::m_error = loader.Error();
	}

	return TBase::Error();
}

#pragma endregion