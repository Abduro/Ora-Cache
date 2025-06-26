/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2024 at 22:45:04.2676653, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack MS XML error interface implementation file;
*/
#include "msxml.error.h"

using namespace shared::xml::ms;

/////////////////////////////////////////////////////////////////////////////

CErr_Desc:: CErr_Desc (void) : m_code(0) {}
CErr_Desc:: CErr_Desc (const CErr_Desc& _src) : CErr_Desc() { *this = _src; }
CErr_Desc:: CErr_Desc (CErr_Desc&& _victim) : CErr_Desc() { *this = _victim; }
CErr_Desc::~CErr_Desc (void) {}

/////////////////////////////////////////////////////////////////////////////

long   CErr_Desc::Code  (void) const { return this->m_code; }
bool   CErr_Desc::Code  (const long _n_code) { const bool b_changed = this->Code() != _n_code; if (b_changed) this->m_code = _n_code; return b_changed; }

_pc_sz CErr_Desc::Reason(void) const { return (_pc_sz) this->m_reason; }
bool   CErr_Desc::Reason(_pc_sz _p_reason) {
	_p_reason;
	CString cs_reason(_p_reason); cs_reason.Trim();
	const bool b_changed = !!cs_reason.Compare(this->Reason());
	if (b_changed)
		this->m_reason = cs_reason;
	return b_changed;
}

_pc_sz CErr_Desc::Text  (void) const { return this->m_text.GetString(); }
bool   CErr_Desc::Text  (_pc_sz _p_text) {
	_p_text;

	CString cs_text(_p_text); cs_text.Trim();

	const bool b_changed = !!cs_text.Compare(this->Text());

	if (b_changed)
		this->m_text = cs_text;

	return b_changed;
}

#if defined(_DEBUG)
CString CErr_Desc::Print(const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {code=%d;reason=%s;text=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {code=%d;reason=%s;text=%s}");
	static _pc_sz pc_sz_pat_r = _T("code=%d;reason=%s;text=%s");

	CString cs_reason = this->m_reason.IsEmpty() == false ? this->Reason() : _T("#n/a");
	CString cs_text   = this->m_text.IsEmpty() == false ? this->Text() : _T("#n/a");

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz) __CLASS__,
		this->Code(), (_pc_sz) cs_reason, (_pc_sz) cs_text);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz) __CLASS__,
		this->Code(), (_pc_sz) cs_reason, (_pc_sz) cs_text);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r,
		this->Code(), (_pc_sz) cs_reason, (_pc_sz) cs_text);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

err_code  CErr_Desc::Set (const TErrorPtr _p_from) {
	_p_from;
	err_code n_result = __s_ok;

	if (!_p_from)
		return n_result = __e_pointer;

	err_code n_prev = n_result; // for saving the last error result of failed calls, if occurred;

	n_result = _p_from->get_errorCode(&this->m_code);
	if (__failed(n_result)) {
		n_prev = n_result;
	}

	_bstr_t bs_value;

	n_result = _p_from->get_reason(bs_value.GetAddress());
	if (__failed(n_result)) {
		n_prev = n_result;

		CError err_; err_ << n_result; this->Reason(err_.Desc());
	}
	else if (__s_false == n_result) {  this->Reason(_T("#no_error")); }
	else {
		this->Reason((_pc_sz)bs_value);
	}

	n_result = _p_from->get_srcText(bs_value.GetAddress());
	if (__failed(n_result)) {
		n_prev = n_result;
	}
	else if (__s_false == n_result) {  this->Text(_T("#no_xml")); }
	else {
		this->Text((_pc_sz)bs_value);
	}

	return n_prev;
}

/////////////////////////////////////////////////////////////////////////////

CErr_Desc& CErr_Desc::operator = (const CErr_Desc& _src) { *this << _src.Code() << _src.Reason() >> _src.Text(); return *this; }
CErr_Desc& CErr_Desc::operator = (CErr_Desc&& _victim) { *this = (const CErr_Desc&)_victim; return *this; }

CErr_Desc& CErr_Desc::operator <<(const long _n_code) { this->Code(_n_code); return *this; }
CErr_Desc& CErr_Desc::operator <<(_pc_sz _p_reason) { this->Reason(_p_reason); return *this; }
CErr_Desc& CErr_Desc::operator >>(_pc_sz _for_fixing) { this->Text(_for_fixing); return *this; }

/////////////////////////////////////////////////////////////////////////////

CErr_Pos:: CErr_Pos (void) : m_col(not_set), m_row(not_set), m_offset(not_set) {}
CErr_Pos:: CErr_Pos (const CErr_Pos& _src) : CErr_Pos() { *this = _src; }
CErr_Pos:: CErr_Pos (CErr_Pos&& _victim) : CErr_Pos() { *this = _victim; }
CErr_Pos::~CErr_Pos (void) {}

/////////////////////////////////////////////////////////////////////////////

long  CErr_Pos::Col (void) const { return this->m_col; }
bool  CErr_Pos::Col (const long _n_col) {
	_n_col;
	const bool b_changed = (this->Col() != _n_col);

	if (b_changed)
		this->m_col = _n_col;

	return b_changed;
}

long  CErr_Pos::Offset (void) const { return this->m_offset; }
bool  CErr_Pos::Offset (const long _n_off) {
	_n_off;
	const bool b_changed = (this->Offset() != _n_off);

	if (b_changed)
		this->m_offset = _n_off;

	return b_changed;
}

#if defined(_DEBUG)
CString   CErr_Pos::Print  (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {col=%d;row=%d;offset=%d}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {col=%d;row=%d;offset=%d}");
	static _pc_sz pc_sz_pat_r = _T("col=%d;row=%d;offset=%d");

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz) __CLASS__, this->Col(), this->Row(), this->Offset()); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz) __CLASS__, this->Col(), this->Row(), this->Offset()); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r, this->Col(), this->Row(), this->Offset()); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

long  CErr_Pos::Row (void) const { return this->m_row; }
bool  CErr_Pos::Row (const long _n_row) {
	_n_row;
	const bool b_changed = (this->Row() != _n_row);

	if (b_changed)
		this->m_row = _n_row;

	return b_changed;
}

err_code CErr_Pos::Set (const TErrorPtr _p_from) {
	_p_from;
	err_code n_result = __s_ok;

	if (!_p_from)
		return n_result = __e_pointer;

	// the result is important only for above case; in other cases the particular value is set to default one in case of failed call to raw interface;
	err_code n_prev = n_result;
	long l_value = 0;

	n_result = _p_from->get_line(&l_value);
	if (__failed(n_result)) {
		this->Row(CErr_Pos::not_set); n_prev = n_result; // saves the last error result of the failed call;
	}
	else this->Row(l_value);

	n_result = _p_from->get_linepos(&l_value);
	if (__failed(n_result)) {
		this->Col(CErr_Pos::not_set); n_prev = n_result;
	}
	else this->Col(l_value);

	n_result = _p_from->get_filepos(&l_value);
	if (__failed(n_result)) {
		this->Offset(CErr_Pos::not_set); n_prev = n_result;
	}
	else this->Offset(l_value);

	return n_prev; // returns the last error result of the failed call, if occurred;
}

bool  CErr_Pos::Set (const long _n_col, const long _n_row, const long _n_offset) {
	_n_col; _n_row; _n_offset;
	bool b_changed = false;

	if (this->Col(_n_col)) b_changed = true;
	if (this->Offset(_n_offset)) b_changed = true;
	if (this->Row(_n_row)) b_changed = true;

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CErr_Pos& CErr_Pos::operator = (const CErr_Pos& _src) { *this << _src.Col() ^ _src.Row() >> _src.Offset(); return *this; }
CErr_Pos& CErr_Pos::operator = (CErr_Pos&& _victim) { *this = (const CErr_Pos&)_victim; return *this; }

CErr_Pos& CErr_Pos::operator <<(const long _n_col)    { this->Col(_n_col); return *this; }
CErr_Pos& CErr_Pos::operator ^ (const long _n_row)    { this->Row(_n_row); return *this; }
CErr_Pos& CErr_Pos::operator >>(const long _n_off)    { this->Offset(_n_off); return *this; }

/////////////////////////////////////////////////////////////////////////////

CParseError:: CParseError (void) : TBase() { (*this)() >> __CLASS__ << __METHOD__; }
CParseError:: CParseError (const CParseError& _src) : CParseError() { *this = _src; }
CParseError:: CParseError (const TErrorPtr& _ptr) : CParseError() { *this << _ptr; }
CParseError::~CParseError (void) {}

/////////////////////////////////////////////////////////////////////////////

const
CErr_Desc&    CParseError::Desc (void) const { return this->m_desc; }
CErr_Desc&    CParseError::Desc (void)       { return this->m_desc; }

bool   CParseError::Is (void) const {

	bool b_error = TBase::Is();
	if ( b_error == false && nullptr != (*this)[0]) {
		 b_error = !!this->Desc().Code(); // it is not informative due to the update or refresh data is not called yet, thus mo error is indicated;
	}
	else
		 b_error = !!this->Desc().Code(); // exception code might be set from outside;

	return b_error;
}

const
CErr_Pos& CParseError::Pos (void) const { return this->m_position; }
CErr_Pos& CParseError::Pos (void)       { return this->m_position; }

const
TErrorPtr& CParseError::Ptr (void) const { return this->m_raw_ptr; }
TErrorPtr& CParseError::Ptr (void)       { return this->m_raw_ptr; }

err_code CParseError::Refresh (void) {
	(*this)() << __METHOD__ << __s_ok;

	if (nullptr == (*this)[0]) // the raw parse error pointer is not set yet;
		return *this;

	err_code n_result = (*this)();
	err_code n_prev = n_result; // for saving the last error that may occur in this error components;

	_bstr_t bs_src_url;
	n_result = (*this)[1]->get_url(bs_src_url.GetAddress());

	if (__failed(n_result)) n_prev = n_result;
	else if (__s_false == n_result)
		this->m_src_url = _T("#n/a");
	else
		this->m_src_url = (_pc_sz) bs_src_url;

	n_result = this->Desc().Set((*this)[2]); if (__failed(n_result)) n_prev = n_result;
	n_result = this->Pos ().Set((*this)[3]); if (__failed(n_result)) n_prev = n_result;

	if (__failed(n_result))
		(*this)() << n_result;
	// the sync XML parse error data must be made with parent error ebject:
	(*this)() << this->Desc().Code() = this->Desc().Reason();

	return *this;
}

_pc_sz   CParseError::Source (void) const {
	return (_pc_sz) this->m_src_url;
}

/////////////////////////////////////////////////////////////////////////////

CParseError&  CParseError::operator = (const CParseError& _src) {
	(TBase&)*this = (const TBase&)_src;
	*this << _src.Ptr() << _src.Desc() << _src.Pos(); return *this;
}
CParseError&  CParseError::operator <<(const TErrorPtr& _ptr) { this->Ptr() = _ptr; return *this; }

CParseError&  CParseError::operator <<(const CErr_Desc& _desc) { this->Desc() = _desc; return *this; }
CParseError&  CParseError::operator <<(const CErr_Pos & _pos ) { this->Pos() = _pos; return *this; }

/////////////////////////////////////////////////////////////////////////////

CParseError::operator const CError& (void) const { return (const TBase&)*this; }
CParseError::operator       CError& (void)       { return (TBase&)*this; }
const
CError&  CParseError::operator ()(void) const { return (TBase&)*this; }
CError&  CParseError::operator ()(void)       { return (TBase&)*this; }

CParseError::operator const TErrorPtr& (void) const { return  this->Ptr(); }
CParseError::operator       TErrorPtr& (void)       { return  this->Ptr(); }
const
TErrorPtr&  CParseError::operator [](const long _not_used) const { _not_used; return this->Ptr(); }
TErrorPtr&  CParseError::operator [](const long _not_used)       { _not_used; return this->Ptr(); }

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
CString     CParseError::Print (const ::e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%sdesc={%s}%s%spos={%s}%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {%s%sdesc={%s}%s%spos={%s}%s%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s%sdesc={%s}%s%spos={%s}%s%s}");

	using e_print = ::e_print;

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, 
		_p_sfx, _p_pfx, (_pc_sz) this->Desc().Print(e_print::e_req),
		_p_sfx, _p_pfx, (_pc_sz) this->Pos ().Print(e_print::e_req), _p_sfx, _p_pfx);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n,(_pc_sz)__CLASS__, 
		_p_sfx, _p_pfx, (_pc_sz) this->Desc().Print(e_print::e_req),
		_p_sfx, _p_pfx, (_pc_sz) this->Pos ().Print(e_print::e_req), _p_sfx, _p_pfx);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r, 
		_p_sfx, _p_pfx, (_pc_sz) this->Desc().Print(e_print::e_req),
		_p_sfx, _p_pfx, (_pc_sz) this->Pos ().Print(e_print::e_req), _p_sfx, _p_pfx);
	}

#if (0)
	static LPCTSTR lp_sz_pat = _T("parse={code=0x%x;line=%d;pos=%d;reason='%s';shift=%d;excerpt='%s';url='%s'}::base={code=%d;class='%s';method='%s';desc='%s'}");
	if (false== this->Inited()) {
		return CString(_T("#n/a"));
	}
	CString cs_out;
	cs_out.Format(lp_sz_pat,
			this->Code(), this->Line(), this->Position(), this->Reason().GetString(), this->Shift(), this->Text().GetString(), this->Url().GetString(),
			TBase::Code(), TBase::Class(), TBase::Method(), TBase::Desc()
		);
#endif
	return cs_out;
}
#endif