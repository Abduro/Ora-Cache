/*
	Createed by Tech_dog (ebontrop@gmail.com) on 02-Oct-2026 at 09:47:30.670, UTC+4, Batumi, Friday;
	This is IE web url locator interface implementation file.
*/
#include "web.ie.locator.h"

using namespace ::ex_ui::web::IE;
using namespace ::ex_ui::web::IE::urls;

using e_url_type = CType::e_url_type;
using e_res_type = CExe_Url::e_res_type;

namespace ex_ui { namespace web { namespace IE { namespace _impl {

	class CLocator_helper {
	public:
		 CLocator_helper (const CLocator_helper&) = delete; CLocator_helper (CLocator_helper&&) = delete;
		~CLocator_helper (void) = default;

		CLocator_helper (void) { this->m_error >> __CLASS__<<__METHOD__<<__s_ok; }

		const
		CString& Cached (void) const { return this->m_cache; }

		CString& CurrentModulePath (void) {

			static const uint32_t u_buf_len = 512;

			CString cs_path;
			try {
				// https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/csimplestringt-class?view=msvc-150#getbuffer ;
				cs_path.GetBuffer(u_buf_len);

			} catch (::ATL::CAtlException&) {
				this->m_error.Last(); return cs_path;
			}

			cs_path.ReleaseBuffer(); // it is required before futher calling any function of CString class;
			CLocator_helper::Normalize(cs_path);

			return (this->m_cache = cs_path);
		}

		TError&  Error (void) const { return this->m_error; }

		bool Is_valid (_pc_sz _exe_or_dll_path) {
			_exe_or_dll_path;
			this->m_error <<__METHOD__<<__s_ok;
			this->m_cache = _exe_or_dll_path;

			static _pc_sz p_ext[] = {_T(".exe"), _T(".dll")}; // it is assumed the two file type extensions are acceptable;
			static uint32_t u_ext_len = static_cast<uint32_t>(::_tcslen(p_ext[0]));
			static uint32_t u_min_req = u_ext_len + 1; // minimal file path length: ?.exe or ?.dll ;

			// https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class?view=msvc-150#makelower ;
			this->m_cache = _exe_or_dll_path; this->m_cache.Trim(); this->m_cache.MakeLower();

			const uint32_t path_len = static_cast<uint32_t>(this->m_cache.GetLength());

			// https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class?view=msvc-150#reversefind << can find only one char;
			// https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class?view=msvc-150#find << can find either a char or a substring;
			if (false) {}
			else if (path_len < u_min_req) {
				this->m_error <<__e_inv_arg = TString().Format(_T("__e_inv_arg: input path has invalid length (%d chars)"), m_cache.GetLength());
			}
			else if (-1 == this->m_cache.Find(p_ext[0], path_len - u_ext_len) &&
			         -1 == this->m_cache.Find(p_ext[1], path_len - u_ext_len)
			     ) { this->m_error << __e_inv_arg = _T("__e_inv_arg: input path file extension is invalid;");
			} else {}

			return false == this->Error();
		}

		static void Normalize (CString& _path) { _path.Replace(_T('/'), _T('\\')); }

	private:
		CLocator_helper& operator = (const CLocator_helper&) = delete; CLocator_helper& operator = (CLocator_helper&&) = delete;
		CError  m_error;
		CString m_cache;
	};

}}}} using namespace ::ex_ui::web::IE::_impl;

#pragma region cls::CExe_Url{}

CExe_Url::CExe_Url (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError&   CExe_Url::Error (void) const { return this->m_error; }
_pc_sz    CExe_Url::Get (void) const { return (_pc_sz)this->m_cache; }

err_code  CExe_Url::Set (_pc_sz _file_path, const e_res_type _res_type, const uint32_t _res_id) {
	_file_path; _res_type; _res_id;
	this->m_error <<__METHOD__<<__s_ok;

	CLocator_helper helper;
	if (false == helper.Is_valid(_file_path))
		return this->m_error = helper.Error();

	static _pc_sz p_format[] = {
		_T("res://%s/%u"),
		_T("res://%s/%u/%u")
	};

	if (e_res_type::e__undef == _res_type)
		this->m_cache = TString().Format(p_format[0], _res_id);
	else
		this->m_cache = TString().Format(p_format[1], _res_type, _res_id);
	return this->Error();
}

#pragma endregion
#pragma region cls::CLocator{}

CLocator:: CLocator (const e_url_type _type) : m_type(_type), m_data((long_t)0) { this->m_error >> __CLASS__ << __METHOD__; }
CLocator:: CLocator (_pc_sz _lp_sz_pat) : CLocator() { this->URL(_lp_sz_pat); }
CLocator::~CLocator (void) {}

bool CLocator::Accept (_pc_sz _lp_sz_pat) const {
	_lp_sz_pat;
	this->m_error << __METHOD__ << __s_ok;
	bool b_accept = false;

	CType type_(_lp_sz_pat); // this object is just for pattern type test, otherwise, this method cannot be const;
	if (type_ == false)
		return (m_error = type_);

	switch (type_.Get()) {
	case e_url_type::eHostExecutable: {
			CString cs_pat(_lp_sz_pat);
			const INT n_pos = cs_pat.Find(_T("%s"));
			b_accept = (n_pos != -1);
		} break;
	case e_url_type::eInterCommand  :
	case e_url_type::eOuterBrowser  : {
			b_accept = true;
		} break;
	}

	return b_accept;
}

const
_variant_t&   CLocator::Data (void) const { return this->m_data; }
dword_t       CLocator::DataAsCommand (void) const { if (VT_I4 != m_data.vt) return 0; else return this->m_data.lVal; }

TErrorRef     CLocator::Error (void) const { return this->m_error; }
const
CType& CLocator::Type (void) const { return this->m_type ; }
CType& CLocator::Type (void)       { return this->m_type ; }

_pc_sz CLocator::URL (void) const { return this->m_url.GetString(); }
_pc_sz CLocator::URL (_pc_sz lpszPattern) { this->URL(lpszPattern, this->m_url);  return this->URL(); }

err_code CLocator::URL (_pc_sz lpszPattern, CString& _result) {
	lpszPattern; _result;
	this->m_error << __METHOD__ << __s_ok;

	this->m_type << lpszPattern;
	if (m_type == false)
		return (this->m_error = this->m_type);

	switch (this->Type().Get()) {
	case e_url_type::eHostExecutable: {

		t_char buffer[512] = {0};

		// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenameW ;
		const bool b_result = !!::GetModuleFileName(0, buffer, _countof(buffer));
		if (false == b_result)
			return this->m_error.Last();

		CString cs_path(buffer); cs_path.Replace(_T('/'), _T('\\'));
#if (0)
		// Unfortunately GetFileAttributesEx() fails on paths, which contain dot(s) inside, like c:\\folder_1\\..\\ ;
		// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesW ;
		const dword_t n_result = ::GetFileAttributes(cs_path.GetString());
		if ((dword_t)-1 == n_result)
			return this->m_error.Last();
		else if (0 != (FILE_ATTRIBUTE_DIRECTORY & n_result)) // it's not applicable;
			return this->m_error << __e_inv_arg = _T("Invalid executable file path");


			CStringW cs_file  = the_app.GetFileName(false);
			cs_path.Format(
				_T("%s%s"), (LPCWSTR)path_, cs_file.GetString()
			);

			_result.Format(
					lpszPattern, cs_path.GetString()
				);
#endif
		} break;
	case e_url_type::eExternalLink: { _result = lpszPattern; } break;
	case e_url_type::eOuterBrowser: {

			CString cs_pat(lpszPattern);
			CString cs_pfx = CType::Prefix(m_type);

			if (0 == cs_pat.Find(cs_pfx)) {
				_result = cs_pat.Right(cs_pat.GetLength() - cs_pfx.GetLength());
			}
			else
				m_error.State().Set((DWORD)ERROR_INVALID_DATA, _T("Input URL pattern cannot be parsed."));

		} break;
	case e_url_type::eInterCommand: {

		CString cs_pat(lpszPattern);
		CString cs_pfx = CType::Prefix(m_type);

			if (0 == cs_pat.Find(cs_pfx)) {
				_result = cs_pat.Right(cs_pat.GetLength() - cs_pfx.GetLength());
				m_data = ::_tstol(_result.GetString());
			}
			else
				m_error.State().Set((DWORD)ERROR_INVALID_DATA, _T("Input URL pattern does not provide internal command ID."));

		} break;

	default:
		m_error = DISP_E_TYPEMISMATCH;
	}
	return this->Error();
}

#pragma endregion
#pragma region cls::CType{}

CType:: CType (_pc_sz _lp_sz_pat) : m_type (e_url_type::eHostExecutable) { this->m_error >> __CLASS__ << __METHOD__;
	this->Set(_lp_sz_pat);
}
CType:: CType (const e_url_type _type) : CType(0) { this->m_type = _type; }
CType::~CType (void) {}

TError& CType::Error (void) const  { return m_error; }
bool    CType::IsCmd (void) const  { return (e_url_type::eInterCommand == this->Get()); }
bool    CType::IsExt (void) const  { return (e_url_type::eExternalLink == this->Get()); }
bool    CType::IsOut (void) const  { return (e_url_type::eOuterBrowser == this->Get()); }

CType::e_url_type CType::Get (void) const { return this->m_type ; }

void   CType::Set (const e_url_type _value) { this->m_type = _value; }

err_code CType::Set (_pc_sz _lp_sz_pat) {
	_lp_sz_pat;
	this->m_error << __METHOD__ << __s_ok;

	CString cs_pat(_lp_sz_pat);

	if (cs_pat.IsEmpty()) return (this->m_error << __e_inv_arg);
	if (cs_pat.GetLength() < CType::MinLen()) return this->m_error << (err_code)TErrCodes::eData::eInvalid;

	m_type = CType::ToType(_lp_sz_pat);

	return this->Error();
}

CType& CType::operator << (_pc_sz _lp_sz_pat)  { this->Set(_lp_sz_pat); return *this; }
CType& CType::operator << (const e_url_type _type) { this->Set(_type); return *this; }

CType::operator TError& (void) const { return this->Error(); }
CType::operator e_url_type (void) const { return this->Get(); }
CType::operator bool (void) const { return this->Error() == false; }

int32_t CType::MinLen (void) {
	static const int32_t n_min_len = 7; // equals to length of possible prefix plus one character for URL itself;
	return n_min_len;
}

CString CType::Prefix (const e_url_type _type) {
	CString cs_pfx;
	switch (_type) {
	case CType::eExternalLink  : {} break;
	case CType::eHostExecutable: { cs_pfx = _T("res://" ); } break;
	case CType::eOuterBrowser  : { cs_pfx = _T("outer::"); } break;
	case CType::eInterCommand  : { cs_pfx = _T("inter::"); } break;
	}
	return cs_pfx;
}

e_url_type  CType::ToType (_pc_sz _lp_sz_pat) {
	_lp_sz_pat;
	e_url_type value = CType::eExternalLink;
	CString cs_pat(_lp_sz_pat);

	if (cs_pat.IsEmpty()) return value;
	if (cs_pat.GetLength() < CType::MinLen()) return value;

	if (0 == cs_pat.Find(CType::Prefix(CType::eHostExecutable))) value = e_url_type::eHostExecutable;
	if (0 == cs_pat.Find(CType::Prefix(CType::eOuterBrowser)))   value = e_url_type::eOuterBrowser;
	if (0 == cs_pat.Find(CType::Prefix(CType::eInterCommand)))   value = e_url_type::eInterCommand;

	return value;
}

#pragma endregion