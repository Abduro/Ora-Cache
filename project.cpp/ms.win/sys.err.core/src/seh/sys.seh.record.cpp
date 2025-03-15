/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-May-2024 at 10:27:27.4096435, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack SEH EXCEPTION_RECORD structure wrapper interface implementation file;
*/
#include "sys.seh.record.h"

using namespace shared::sys_core::seh;

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CRecord:: CRecord(void) {}
CRecord:: CRecord(const CRecord& _src) : CRecord() { *this = _src; }
CRecord:: CRecord (const TPointers* const _p_ptrs) : CRecord() { *this << _p_ptrs; }
CRecord:: CRecord (const TRecord* const _p_rec) : CRecord() { *this << _p_rec; }
CRecord::~CRecord(void) {}

/////////////////////////////////////////////////////////////////////////////
#if (0)
const
TRecord&  CRecord::Get (void) const { return this->m_raw; }
TRecord&  CRecord::Get (void)       { return this->m_raw; }

err_code  CRecord::Set (const TRecord& _rec) {
	_rec;
	err_code n_result = TErrCodes::no_error;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/memcpy-s-wmemcpy-s ;
	// https://en.cppreference.com/w/c/string/byte/memcpy ;
	// https://stackoverflow.com/questions/40310835/what-memcpy-s-return-error-404-mean ;
	const errno_t e_num = ::memcpy_s(&this->Get(), sizeof(this->Get()), &_rec, sizeof(_rec));
	if (TErrCodes::no_error != e_num) {
	}

	return n_result;
}
#endif
const
CCode&    CRecord::Code (void) const { return this->m_code; }
CCode&    CRecord::Code (void)       { return this->m_code; }
const
TRawFlags& CRecord::Flags (void) const { return this->m_flags; }
TRawFlags& CRecord::Flags (void)       { return this->m_flags; }

err_code  CRecord::Set (const TPointers* const _p_ptrs) {
	_p_ptrs;
	err_code e_result = TErrCodes::no_error;

	if (!CAccepted()(_p_ptrs))
		return e_result = E_POINTER;

	return this->Set (_p_ptrs->ExceptionRecord);
}

err_code  CRecord::Set (const TRecord* const _p_raw_rec) {
	_p_raw_rec;
	err_code e_result = TErrCodes::no_error;

	if (!CAccepted()(_p_raw_rec))
		return e_result = E_POINTER;

	this->Code() = CCode_Fake::Ref().Get(_p_raw_rec);
	this->Flags() = CFlag_Unw_Collection() >> _p_raw_rec; // raw flag collection is not a singleton, thus it makes the result copy here;
	return e_result;
}

#if defined (_DEBUG)
CString   CRecord::Print (_pc_sz _sep) const {

	static _pc_sz pc_sz_pat = _T("%s:%s%s%s%s");
	CString cs_out;
	        cs_out.Format(pc_sz_pat, (_pc_sz)__CLASS__, _sep, (_pc_sz)this->Code().Print(), _sep, (_pc_sz)CFlag_Unw_Collection::Print(this->Flags(), _sep));
	return  cs_out;

}

CString   CRecord::operator >>(const TPointers* const _p_ptrs) {
	if (CAccepted()(_p_ptrs)) { *this << _p_ptrs; return this->Print(); } else { return CString(_T("Exception pointers invalid;")); }}
CString   CRecord::operator >>(const TRecord* const _p_rec) {
	if (CAccepted()(_p_rec)) { *this << _p_rec; return this->Print(); } else { return CString(_T("Exception record invalid;")); }}

#endif

/////////////////////////////////////////////////////////////////////////////

CRecord&  CRecord::operator = (const CRecord& _src) { *this << _src.Code() << _src.Flags(); return *this; }
CRecord&  CRecord::operator <<(const TRecord* const _p_raw_rec) { this->Set(_p_raw_rec); return *this; }

CRecord&  CRecord::operator <<(const TPointers* _p_ptrs) { this->Set(_p_ptrs); return *this; }

CRecord&  CRecord::operator <<(const CCode& _code) { this->Code() = _code; return *this; }
CRecord&  CRecord::operator <<(const TRawFlags& _flags) { this->Flags() = _flags; return *this; }