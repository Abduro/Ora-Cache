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

#pragma region cls::CLoader{}

CLoader::CLoader (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_false = _T("No object file is loaded yet"); }

TError&  CLoader::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CLocator{}

static _pc_sz p_obj_path = _T("obj_path");

CLocator::CLocator (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_false = _T("No object file is located yet"); }

TError&  CLocator::Error (void) const { return this->m_error; }
err_code CLocator::Locate (void) {
	this->m_error <<__METHOD__<<__s_ok;

	CFile file;
	// (1) checks command line first;
	using
	CCmdLine = ::shared::input::CCmdLine;
	CCmdLine cmd_ln;
	if (__failed(cmd_ln.Parse()))
		return this->m_error = cmd_ln.Error();
	if (cmd_ln.Has(p_obj_path)) {
		this->m_obj_path = cmd_ln.Arg(p_obj_path);

		if (__failed(file.Is_valid(this->m_obj_path)))
			return this->m_error = file.Error();
	}

	if (this->m_obj_path.IsEmpty() == false)
		return this->Error();
	// (2) checks the registry root key for value named 'p_obj_path';
	TRegKeyEx the_key;
	this->m_obj_path = the_key.Value().GetString(CLocator::Root(), p_obj_path);
	if (the_key.Error())
		return this->m_error = the_key.Error();

	if (__failed(file.Is_valid(this->m_obj_path)))
		this->m_error = file.Error();
	else {
		using CFormat = ::shared::console::CFormat;
		__trace_impt_2(_T("The object file path:\n%s%s;\n"), CFormat::Indent(), this->Path());
	}

	return this->Error();
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