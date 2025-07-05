/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Oct-2018 at 6:55:26a, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared lite library string common functionality interface implementation file.
	-----------------------------------------------------------------------------
	Adopted to Geometry Curve project on 17-Feb-2024 at 07:07:45.1072129, UTC+7, Novosibirsk, Saturday;
*/
#include "shared.str.ext.h"

using namespace shared::common;

/////////////////////////////////////////////////////////////////////////////
#if (1)
CString_Ex:: CString_Ex (const bool  _b_value) : TBase() { *this << _b_value; }
CString_Ex:: CString_Ex (const dword _d_value) : TBase() { *this << _d_value; }
CString_Ex:: CString_Ex (const float _f_value) : TBase() { *this << _f_value; }
CString_Ex:: CString_Ex (const long  _l_value) : TBase() { *this << _l_value; }

CString_Ex:: CString_Ex (_pc_sz  _lp_sz_value) : TBase(_lp_sz_value) {}
CString_Ex:: CString_Ex (const CString_Ex& _ref) : TBase() { *this = _ref; }
#endif
/////////////////////////////////////////////////////////////////////////////
#if (1)
USHORT  CString_Ex::Bytes (void) const { return static_cast<ushort>((TBase::IsEmpty() ? 0 : (TBase::GetLength() + 1) * sizeof(t_char))); }

bool    CString_Ex::Bool  (void) const {

	bool b_result = false;

	if (false == this->Is())
		return b_result;

	if (TBase::CompareNoCase(_T("true"))
		|| !!::_tstol (TBase::GetString())
		|| !!::_tstof (TBase::GetString())
		)
		b_result = true;

	return b_result;
}
_pc_sz  CString_Ex::Bool  (const bool _b_value) {
	_b_value;
	*this = (_b_value ? _T("true") : _T("false"));

	return (_pc_sz)*this;
}

dword   CString_Ex::Dword (void) const {

	dword u_result = 0;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strtoul-strtoul-l-wcstoul-wcstoul-l ;
	if (this->Is()) {
		t_char* p_sz_end = 0;
		u_result = ::_tcstoul(TBase::GetString(), &p_sz_end, 10);
	}
	return u_result;
}

_pc_sz  CString_Ex::Dword(dword _u_value) {
	_u_value;
	TBase::Format(_T("%u"), _u_value);
	return (_pc_sz)*this;
}

float   CString_Ex::Float (void) const {

	float f_result = 0.0;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strtod-strtod-l-wcstod-wcstod-l ; _tstof ();
	if (false == this->Is())
		return f_result;
	else
		f_result = static_cast<float>(::_tstof (TBase::GetString()));

	return f_result;
}

_pc_sz  CString_Ex::Float (float _f_value, t_fmt_spec _spec) {
	_f_value; _spec;

//	https://stackoverflow.com/questions/45068641/c-format-code-for-positive-and-negative-float-numbers ;
	_pc_sz lp_sz_fmt = (t_fmt_spec::e_hex == _spec ? _T("%a") : (t_fmt_spec::e_scientific == _spec ? _T("%+e") : _T("%+f")));

	TBase::Format(lp_sz_fmt, _f_value);
	
	return (_pc_sz)*this;
}

_guid   CString_Ex::Guid  (void) const {

	static const _guid empty_ = __guid_null;

	_guid result_ = empty_;

	if (TBase::IsEmpty())
		return result_;
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-clsidfromstring ;
	HRESULT hr_ = ::CLSIDFromString(TBase::GetString(), &result_);
	if (FAILED(hr_))
		return empty_; // looks like the result is already set to this value;

	return result_;
}

_pc_sz  CString_Ex::Guid  (const _guid& _guid) {
	_guid;
	if (TBase::IsEmpty() == false)
		TBase::Empty();

	static const _pc_sz lp_sz_pat = _T("{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}");
	static const size_t n_req_size = ::_tcslen(lp_sz_pat) + 1; // adds one char for ending by zero;

	::std::vector<TCHAR> v_buffer(n_req_size, _T('\0'));
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-stringfromclsid ;
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-stringfromguid2 ;
	const int n_copied = ::StringFromGUID2(_guid, &v_buffer[0], static_cast<int>(n_req_size));

	const bool b_result = 0 != n_copied;
	if (b_result)
		*this = &v_buffer.at(0);

	return TBase::GetString();
}

long    CString_Ex::Long  (void) const {

	long l_result = 0;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/atol-atol-l-wtol-wtol-l ; _tstol ();
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strtol-wcstol-strtol-l-wcstol-l ; _tcstol();
	if (this->Is())
		l_result = ::_tstol(TBase::GetString());

	return l_result;
}

_pc_sz  CString_Ex::Long  (long _l_value) {
	_l_value;
	TBase::Format(_T("%d"), _l_value);
	return (_pc_sz)*this;
}

bool    CString_Ex::Is (void) const { return false == TBase::IsEmpty(); }
#endif
/////////////////////////////////////////////////////////////////////////////
#if (0)
_var    CString_Ex::Var  (void) const {
	return _variant_t();
}
_pc_sz  CString_Ex::Var  (const _var&, _pc_sz _fmt/* = _T("type=%s;value=%s")*/) {
	_fmt;
	*this = _T("$var");
	return (_pc_sz)*this;
}
#endif
/////////////////////////////////////////////////////////////////////////////
#if(1)
#if defined WIN64
_pc_sz CString_Ex::__address_of (const void* const _p_fun_or_obj_ptr) {
	return this->__address_of (_p_fun_or_obj_ptr, _T("0x%x"));
}

_pc_sz CString_Ex::__address_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format) {
	_p_fun_or_obj_ptr; _p_format;

	if (!_p_fun_or_obj_ptr) {
		TBase::SetString(_T("#not_set"));
		return TBase::GetString();
	}

	if (INVALID_HANDLE_VALUE == _p_fun_or_obj_ptr) {
		TBase::SetString(_T("#invalid"));
		return TBase::GetString();
	}
	// https://stackoverflow.com/questions/22846721/pointer-outputs  ;
	const
	uint64_t* p_address = reinterpret_cast<const uint64_t*>(_p_fun_or_obj_ptr);
//	uint64_t  n_address = (p_address ? *p_address : 0);
	if (nullptr == _p_format)
		TBase::Format(_T("0x%x"), &p_address);
	else
		TBase::Format(_p_format , &p_address);

	return TBase::GetString();
}
#else
_pc_sz CString_Ex::__address_of (const void* const _p_fun_or_obj_ptr) {
	return this->__address_of (_p_fun_or_obj_ptr, _T("0x%x"));
}

_pc_sz CString_Ex::__address_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format) {
	_p_fun_or_obj_ptr;

	if (!_p_fun_or_obj_ptr) {
		TBase::SetString(_T("#not_set"));
		return TBase::GetString();
	}

	if (INVALID_HANDLE_VALUE == _p_fun_or_obj_ptr) {
		TBase::SetString(_T("#invalid"));
		return TBase::GetString();
	}

	const
	uint32_t* p_address = reinterpret_cast<const uint32_t*>(_p_fun_or_obj_ptr);
	uint32_t  n_address = (!!p_address ? *p_address : 0);
	
	if (nullptr == _p_format)
		TBase::Format(_T("0x%x"), n_address);
	else
		TBase::Format(_p_format , n_address);

	return TBase::GetString();
}
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
#if (1)
_pc_sz  CString_Ex::Before(t_char _lp_sz_sep, _pc_sz _lp_sz_pfx, const bool _b_exc_sep) {
	_lp_sz_sep; _lp_sz_pfx;
	const INT n_pos = TBase::ReverseFind(_lp_sz_sep);
	if (-1 == n_pos)
		return TBase::GetString();

	CString cs_cat(_lp_sz_pfx);
	cs_cat += TBase::Right(TBase::GetLength() - n_pos - (_b_exc_sep ? 1 : 0));
	(TBase&)*this = cs_cat.GetString();
	return TBase::GetString();
}

_pc_sz  CString_Ex::Format(_pc_sz _lp_sz_fmt, ...) {

	va_list  args_;
	va_start(args_, _lp_sz_fmt);

	this->Format(_lp_sz_fmt, args_);
	
	va_end  (args_);
	return  (_pc_sz)*this;
}

_pc_sz  CString_Ex::Format(_pc_sz _lp_sz_fmt, va_list _args) {

	size_t t_size = 0;
	HRESULT hr_ = S_OK;
	if (nullptr == _args) {
		TBase::Format(_lp_sz_fmt, _args);
		return  (_pc_sz)*this;
	}
	try {
		do {
			t_size += 2048;
			TCHAR*   p_sz_buf = new TCHAR[t_size];
			::memset(p_sz_buf, 0, t_size * sizeof(TCHAR));
			// https://learn.microsoft.com/en-us/windows/win32/api/strsafe/nf-strsafe-stringcchvprintfexw ;
			hr_ = ::StringCchVPrintfEx(
				p_sz_buf, t_size, NULL, NULL, 0, _lp_sz_fmt, _args
			);
			if (SUCCEEDED(hr_))
				*this = p_sz_buf;
			if (p_sz_buf) {
				delete p_sz_buf; p_sz_buf = NULL;
			}
		}
		while(STRSAFE_E_INSUFFICIENT_BUFFER == hr_);
	}
	catch (const ::std::bad_alloc&)
	{}
	return  (_pc_sz)*this;
}

TParts  CString_Ex::Split (_pc_sz _lp_sz_sep, const bool _b_preserve_sep) const {
	TParts  vec_;
	if (NULL == _lp_sz_sep || 0 == ::lstrlen(_lp_sz_sep))
		return vec_;
	INT n_pos = 0;
	CString cs_item = TBase::Tokenize(_lp_sz_sep, n_pos); if (cs_item.IsEmpty() == false) cs_item.Trim();

	while (cs_item.IsEmpty() == false) {
		try {
			if (_b_preserve_sep) {
				CString cs_preserved = cs_item; cs_preserved += _lp_sz_sep;
				vec_.push_back(cs_preserved);
			}
			else
			vec_.push_back(cs_item);
		}
		catch (::std::bad_alloc&) {
			return vec_;
		}
		cs_item = TBase::Tokenize(_lp_sz_sep, n_pos); if (cs_item.IsEmpty() == false) cs_item.Trim();
	}

	return vec_;
}
#endif
/////////////////////////////////////////////////////////////////////////////
#if(0)
CStdString&  CStdString::operator=(const _variant_t& _var) {

	switch (_var.vt) {
	case VT_BSTR: {
		*this = _bstr_t(_var.bstrVal, FALSE);
	} break;
	default:
		_variant_t v_bstr;
		v_bstr.ChangeType(VT_BSTR, &_var);
		if (VT_BSTR == v_bstr.vt) {
			*this = _bstr_t(v_bstr.bstrVal, FALSE);
		}
	}

	return *this;
}
#endif
/////////////////////////////////////////////////////////////////////////////
#if (1)
CString_Ex& CString_Ex::operator = (const CString_Ex& _ref) { (TBase&)*this = (const TBase&)_ref; return *this; }
CString_Ex& CString_Ex::operator <<(bool  _b_value) { _pc_sz lp_sz_result  = this->Bool (_b_value); lp_sz_result; return *this; }
CString_Ex& CString_Ex::operator <<(dword _d_value) { _pc_sz lp_sz_result  = this->Dword(_d_value); lp_sz_result; return *this; }
CString_Ex& CString_Ex::operator <<(float _f_value) { _pc_sz lp_sz_result  = this->Float(_f_value); lp_sz_result; return *this; }
CString_Ex& CString_Ex::operator <<(long  _l_value) { _pc_sz lp_sz_result  = this->Long (_l_value); lp_sz_result; return *this; }

CString_Ex& CString_Ex::operator <<(_pc_sz _lp_sz_value) { *this = _lp_sz_value; return *this; }
CString_Ex& CString_Ex::operator <<(_guid& _guid_value) { this->Guid(_guid_value); return *this; }

/////////////////////////////////////////////////////////////////////////////

CString_Ex::operator CString (void) const { return CString(TBase::GetString()); }
CString_Ex::operator bool    (void) const { return this->Bool (); }
CString_Ex::operator dword   (void) const { return this->Dword(); }
CString_Ex::operator float   (void) const { return this->Float(); }
CString_Ex::operator _guid   (void) const { return this->Guid (); }
CString_Ex::operator long    (void) const { return this->Long (); }
CString_Ex::operator _pc_sz  (void) const { return TBase::GetString(); }
#endif
/////////////////////////////////////////////////////////////////////////////
#if (1)
CString_2:: CString_2 (void) : TBase() {}
CString_2::~CString_2 (void) {}

/////////////////////////////////////////////////////////////////////////////

void CString_2::Format (_pc_sz _p_sz_format, ...) {
	_p_sz_format;
	va_list argList;
	va_start( argList, _p_sz_format );
	TBase::FormatV( _p_sz_format, argList );
	va_end( argList );
}
#endif
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////