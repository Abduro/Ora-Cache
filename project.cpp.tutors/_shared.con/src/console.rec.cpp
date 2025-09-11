/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Dec-2022 at 10:04:31.2533034, UTC+7, Novosibirsk, Sunday;
	This is system console output record implementation file;
	-----------------------------------------------------------------------------
	This code is the excerpt from console project of Ebo_Pack package static library code;
*/
#include "console.rec.h"

using namespace shared::console;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace console { namespace _impl {

	class CTimestamp  {
	public:
		 CTimestamp (void) {}
		~CTimestamp (void) {}

	public:
		CString  out (void) const {

			static _pc_sz  lp_sz_tm_pat = _T("%02d/%02d/%02d %02d:%02d:%02d.%03d");
			SYSTEMTIME st = { 0 };
			::GetLocalTime(&st);

			CString cs_timestamp;
			cs_timestamp.Format(
				lp_sz_tm_pat,
				st.wMonth   ,
				st.wDay     ,
				st.wYear%100,  // only 2 digits
				st.wHour    ,
				st.wMinute  ,
				st.wSecond  ,
				st.wMilliseconds
			);
			return cs_timestamp;
		}
	};

}}}
using namespace shared::console::_impl;
/////////////////////////////////////////////////////////////////////////////

CRecord:: CRecord (void) : m_rec_type(TRecType::eInfo) {}
CRecord:: CRecord (const CRecord& _ref) : CRecord() { *this = _ref; }
CRecord:: CRecord (TRecordType _type, _pc_sz _lp_sz_text) : CRecord() { *this << _type << _lp_sz_text; }
CRecord::~CRecord (void) {}

/////////////////////////////////////////////////////////////////////////////

bool      CRecord::IsValid (void) const { return (nullptr != this->Text() && ::_tcslen(this->Text())); }

_pc_sz    CRecord::Text (void) const { return this->m_rec_text; }
err_code  CRecord::Text (_pc_sz _lp_sz_text)
{
	err_code hr_ = S_OK;

	if (nullptr == _lp_sz_text || 0 == ::_tcslen(_lp_sz_text))
		return (hr_ = E_INVALIDARG);

	this->m_rec_text = _lp_sz_text;

	return (hr_);
}

TRecType  CRecord::Type (void) const { return this->m_rec_type; }
err_code  CRecord::Type (TRecType _type)
{
	err_code hr_ = (_type != this->m_rec_type ? S_OK : S_FALSE);

	this->m_rec_type = _type;

	return  hr_;
}

/////////////////////////////////////////////////////////////////////////////

err_code   CRecord::Out(void) const
{
	err_code hr_ = S_OK;
	if (false == this->IsValid())
		return (hr_ = OLE_E_BLANK);

	::ATL::CString cs_out;
	switch(this->Type())
	{
	case TRecordType::eError    : cs_out.Format(_T("\n\t[#ERR] [%s] %s"), (_pc_sz)CTimestamp().out(), this->Text()); break;
	case TRecordType::eInfo     : cs_out.Format(_T("\n\t[INFO] [%s] %s"), (_pc_sz)CTimestamp().out(), this->Text()); break;
	case TRecordType::eWarning  : cs_out.Format(_T("\n\t[WARN] [%s] %s"), (_pc_sz)CTimestamp().out(), this->Text()); break;
	}
	::_tprintf(cs_out.GetString());
	
	return hr_;
}

/////////////////////////////////////////////////////////////////////////////

CRecord&  CRecord::operator = (const CRecord& _ref) { *this << _ref.Type() << _ref.Text(); return *this; }
CRecord&  CRecord::operator <<(_pc_sz _lp_sz_text) {  this->Text(_lp_sz_text); return *this; }
CRecord&  CRecord::operator <<(TRecordType   _type) {  this->Type(_type); return *this; }

/////////////////////////////////////////////////////////////////////////////

CRecord::operator _pc_sz (void) const { return this->Text(); }
CRecord::operator TRecType(void) const { return this->Type(); }

/////////////////////////////////////////////////////////////////////////////

CRec_Err:: CRec_Err (_pc_sz _lp_sz_text) : TBase(TRecType::eError, _lp_sz_text) { TBase::Out(); }
CRec_Err:: CRec_Err (TErrorRef _error) : TBase(TRecType::eError, _T("#n/a")/*(_pc_sz)(CString(_T("Error details:")) + _error.Format(_T("\n\t\t")))*/) { TBase::Out(); _error; }
CRec_Err::~CRec_Err (void) {}

/////////////////////////////////////////////////////////////////////////////

CRec_Info:: CRec_Info (_pc_sz _lp_sz_text) : TBase(TRecType::eInfo, _lp_sz_text) { TBase::Out(); }
CRec_Info::~CRec_Info (void) {}

/////////////////////////////////////////////////////////////////////////////

CRec_Warn:: CRec_Warn (_pc_sz _lp_sz_text) : TBase(TRecType::eWarning, _lp_sz_text) { TBase::Out(); }
CRec_Warn::~CRec_Warn (void) {}

/////////////////////////////////////////////////////////////////////////////