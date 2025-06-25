/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2024 at 22:45:04.2676653, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack MS XML error interface implementation file;
*/
#include "msxml.error.h"

using namespace shared::xml::ms;

/////////////////////////////////////////////////////////////////////////////

CParseError:: CParseError (void) : TBase() { (TBase&)*this >> __CLASS__ << __METHOD__; }
CParseError:: CParseError (const CParseError& _ref) : CParseError() { *this = _ref; }
CParseError:: CParseError (const TErrorPtr& _ptr) : CParseError() { *this << _ptr; }
CParseError::~CParseError (void) {}

/////////////////////////////////////////////////////////////////////////////

long CParseError::Code (void) const {

	long n_code = 0;
	CParseError& this_ = const_cast<CParseError&>(*this);

	if (!this->Inited()) {
		this_.State().Set(OLE_E_BLANK);
		return n_code = TBase::Code();
	}

	HRESULT hr_ = this->Ptr()->get_errorCode(&n_code);
	if (FAILED(hr_)) {
		this_.State().Set(hr_);
	}
	return n_code;
}

long CParseError::Line (void) const {

	long n_line = -1;
	CParseError& this_ = const_cast<CParseError&>(*this);

	if (!this->Inited()) {
		this_.State().Set(OLE_E_BLANK);
		return n_line;
	}

	HRESULT hr_ = this->Ptr()->get_line(&n_line);
	if (FAILED(hr_)) {
		this_.State().Set(hr_);
	}
	else if (S_FALSE == hr_)
		n_line = -1;

	return n_line;
}

long CParseError::Position (void) const {

	long n_position = -1;
	CParseError& this_ = const_cast<CParseError&>(*this);

	if (!this->Inited()) {
		this_.State().Set(OLE_E_BLANK);
		return n_position;
	}

	HRESULT hr_ = this->Ptr()->get_linepos(&n_position);
	if (FAILED(hr_)) {
		this_.State().Set(hr_);
	}
	else if (S_FALSE == hr_)
		n_position = -1;

	return n_position;
}

CString CParseError::Reason (void) const {

	CString cs_reason;
	CParseError& this_ = const_cast<CParseError&>(*this);

	if (!this->Inited()) {
		this_.State().Set(OLE_E_BLANK);
		return CString(TBase::Desc());
	}

	bstr_t bs_reason;

	HRESULT hr_ = this->Ptr()->get_reason(bs_reason.GetAddress());
	if (FAILED(hr_)) {
		this_.State().Set(hr_);
		cs_reason = TBase::Desc();
	}
	else if (S_FALSE == hr_)
		cs_reason = _T("#no_parse");
	else
		cs_reason = (LPCTSTR)bs_reason;

	return  cs_reason;
}

long    CParseError::Shift (void) const {

	long n_shift = -1;
	CParseError& this_ = const_cast<CParseError&>(*this);

	if (!this->Inited()) {
		this_.State().Set(OLE_E_BLANK);
		return n_shift;
	}

	HRESULT hr_ = this->Ptr()->get_filepos(&n_shift);
	if (FAILED(hr_)) {
		this_.State().Set(hr_);
	}
	else if (S_FALSE == hr_)
		n_shift = -1;

	return n_shift;
}

CString CParseError::Text (void) const {

	CString cs_text;
	CParseError& this_ = const_cast<CParseError&>(*this);

	if (!this->Inited()) {
		this_.State().Set(OLE_E_BLANK);
		return CString(TBase::Desc());
	}

	bstr_t bs_text;

	HRESULT hr_ = this->Ptr()->get_srcText(bs_text.GetAddress());
	if (FAILED(hr_)) {
		this_.State().Set(hr_);
		cs_text = TBase::Desc();
	}
	else if (S_FALSE == hr_)
		cs_text = _T("#no_xml");
	else
		cs_text = (LPCTSTR)bs_text;

	return cs_text;
}

CString CParseError::Url (void) const {

	CString cs_url;
	CParseError& this_ = const_cast<CParseError&>(*this);

	if (!this->Inited()) {
		this_.State().Set(OLE_E_BLANK);
		return CString(TBase::Desc());
	}

	bstr_t bs_url;

	HRESULT hr_ = this->Ptr()->get_url(bs_url.GetAddress());
	if (FAILED(hr_)) {
		this_.State().Set(hr_);
		cs_url = TBase::Desc();
	}
	else if (S_FALSE == hr_)
		cs_url = _T("#n/a");
	else
		cs_url = (LPCTSTR)bs_url;

	return cs_url;
}

/////////////////////////////////////////////////////////////////////////////
const
TErrorPtr& CParseError::Ptr (void) const { return this->m_raw_ptr; }
TErrorPtr& CParseError::Ptr (void)       { return this->m_raw_ptr; }

const bool CParseError::Inited (void) const { return nullptr != this->Ptr(); }
#ifdef _DEBUG
CString    CParseError::Print  (void) const {

	static LPCTSTR lp_sz_pat = _T("parse={code=0x%x;line=%d;pos=%d;reason='%s';shift=%d;excerpt='%s';url='%s'}::base={code=%d;class='%s';method='%s';desc='%s'}");
	if (false== this->Inited()) {
		return CString(_T("#n/a"));
	}
	CString cs_out;
	cs_out.Format(lp_sz_pat,
			this->Code(), this->Line(), this->Position(), this->Reason().GetString(), this->Shift(), this->Text().GetString(), this->Url().GetString(),
			TBase::Code(), TBase::Class(), TBase::Method(), TBase::Desc()
		);
	return cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CParseError&  CParseError::operator = (const CParseError& _ref) { (TBase&)*this = (const TBase&)_ref; *this << _ref.Ptr(); return *this; }
CParseError&  CParseError::operator <<(const TErrorPtr& _ptr) { this->Ptr() = _ptr; return *this; }

CParseError::operator const TErrorPtr& (void) const { return  this->Ptr(); }
CParseError::operator       TErrorPtr& (void)       { return  this->Ptr(); }

CParseError::operator const CError& (void) const { return (const TBase&)*this; }
CParseError::operator       CError& (void)       { return (TBase&)*this; }

CError&  CParseError::operator ()(void) { return (TBase&)*this; }