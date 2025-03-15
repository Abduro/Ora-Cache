/*
	Created by Tech_dog (ebontrop@gmail.com)on 30-Dec-2023 at 12:00:09.5577839, UTC+7, Novosibirsk, Saturday;
	This is shared library Win32 SEH translator interface implementation file;
	-----------------------------------------------------------------------------
	Adopted to Geometry Curve project on 17-Feb-2024 at 06:56:19.8575121, UTC+7, Novosibirsk, Saturday;
*/
#include <sys.seh.except.h>

using namespace shared::sys_core::seh;

/////////////////////////////////////////////////////////////////////////////

#ifndef EXCEPTION_SOFTWARE_ORIGINATE
#define EXCEPTION_SOFTWARE_ORIGINATE (0x80) // 128 decimal;
#endif

namespace shared { namespace sys_core { namespace seh { namespace _impl {

	class CConvertor {
	public:
		 CConvertor (void) {}
		~CConvertor (void) {}

	public:
		CString Code (const DWORD _code) {
			CString cs_result = _T("#n/a");

			switch (_code) {
			case EXCEPTION_ACCESS_VIOLATION         : cs_result = _T("No appropriate access"); break;
			case EXCEPTION_ARRAY_BOUNDS_EXCEEDED    : cs_result = _T("Out of bounds"); break;
			case EXCEPTION_BREAKPOINT               : cs_result = _T("A breakpoint was encountered"); break;
			case EXCEPTION_DATATYPE_MISALIGNMENT    : cs_result = _T("Misaligned data"); break;
			case EXCEPTION_FLT_DENORMAL_OPERAND     : cs_result = _T("Floating-point operation is denormal"); break;
			case EXCEPTION_FLT_DIVIDE_BY_ZERO       : cs_result = _T("Floating-point value is divided by 0"); break;
			case EXCEPTION_FLT_INEXACT_RESULT       : cs_result = _T("Floating-point invalid decimal fraction"); break;
			case EXCEPTION_FLT_INVALID_OPERATION    : cs_result = _T("Floating-point invalid operation"); break;
			case EXCEPTION_FLT_OVERFLOW             : cs_result = _T("Floating-point magnitude is not allowed"); break;
			case EXCEPTION_FLT_STACK_CHECK          : cs_result = _T("The stack overflowed or underflowed"); break;
			case EXCEPTION_FLT_UNDERFLOW            : cs_result = _T("Floating-point magnitude is less than allowed"); break;
			case EXCEPTION_ILLEGAL_INSTRUCTION      : cs_result = _T("An invalid instruction"); break;
			case EXCEPTION_IN_PAGE_ERROR            : cs_result = _T("Accessing a page that is not present"); break;
			case EXCEPTION_INT_DIVIDE_BY_ZERO       : cs_result = _T("Integer value is divided by 0"); break;
			case EXCEPTION_INT_OVERFLOW             : cs_result = _T("Integer value overslow"); break;
			case EXCEPTION_INVALID_DISPOSITION      : cs_result = _T("Invalid disposition to exception dispatcher"); break;
			case EXCEPTION_NONCONTINUABLE_EXCEPTION : cs_result = _T("An execution after noncontinuable exception"); break;
			case EXCEPTION_PRIV_INSTRUCTION         : cs_result = _T("Executing an invalid instruction"); break;
			case EXCEPTION_SINGLE_STEP              : cs_result = _T("Single-step execution"); break;
			case EXCEPTION_STACK_OVERFLOW           : cs_result = _T("Stack overflow"); break;
			}

			return  cs_result;
		}

		CString Flag (const DWORD _flag) {

			CString cs_result = _T("#n/a");

			switch (_flag) {
			case EXCEPTION_NONCONTINUABLE    : cs_result = _T("An execution is noncontinuable"); break;
			case EXCEPTION_SOFTWARE_ORIGINATE: cs_result = _T("Reserved for system use"); break;
			}
			return  cs_result;
		}
	};

}}}}
using namespace shared::sys_core::seh::_impl;
/////////////////////////////////////////////////////////////////////////////

CAction:: CAction (void) : m_data(nullptr), m_type(eType::eRead) {}
CAction:: CAction (const CAction& _ref) : CAction() { *this =  _ref; }
CAction:: CAction (const TRecord& _rec) : CAction() { *this << _rec; }
CAction:: CAction (const TRecord* _rec) : CAction() { *this << _rec; }
CAction:: CAction (const TPointers* _ptrs) : CAction() { *this << _ptrs; }
CAction::~CAction (void) {}

/////////////////////////////////////////////////////////////////////////////
typedef CAction::eType TType;

TAddress  CAction::Data (void) const { return this->m_data; }
TType     CAction::Type (void) const { return this->m_type; }

HRESULT   CAction::Set  (const TPointers* _ptrs) { if (nullptr == _ptrs) return E_POINTER; else return this->Set (_ptrs->ExceptionRecord);  }

HRESULT   CAction::Set  (const TRecord& _rec) {
	_rec;
	HRESULT hr_ = S_OK;
	switch (_rec.ExceptionCode) {
	case EXCEPTION_ACCESS_VIOLATION :
	case EXCEPTION_IN_PAGE_ERROR    : {
		if (0 == _rec.ExceptionInformation[0]) { this->m_type = eType::eRead ; this->m_data = reinterpret_cast<TAddress>(_rec.ExceptionInformation[1]); }
		if (1 == _rec.ExceptionInformation[0]) { this->m_type = eType::eWrite; this->m_data = reinterpret_cast<TAddress>(_rec.ExceptionInformation[1]); }
		if (8 == _rec.ExceptionInformation[0]) { this->m_type = eType::eDepVa; this->m_data = reinterpret_cast<TAddress>(_rec.ExceptionInformation[1]); }
	} break;  // NTSTATUS is not used;
	default:
		this->m_type = eType::eRead; this->m_data = nullptr;
	}
	return  hr_;
}
HRESULT   CAction::Set  (const TRecord* _rec) {
	HRESULT hr_ = S_OK; if (nullptr == _rec) hr_ = E_POINTER; else hr_ = this->Set(*_rec); return hr_;
}

/////////////////////////////////////////////////////////////////////////////

CAction&  CAction::operator = (const CAction& _ref) { *this << _ref.Data() << _ref.Type(); return *this; }
CAction&  CAction::operator <<(const TRecord& _rec) {  this->Set(_rec); return *this; }
CAction&  CAction::operator <<(const TRecord* _rec) {  this->Set(_rec); return *this; }

CAction&  CAction::operator <<(const TPointers* _ptrs) { this->Set(_ptrs); return *this; }

/////////////////////////////////////////////////////////////////////////////

CAction&  CAction::operator <<(const TType   _type) {  this->m_type = _type; return *this; }
CAction&  CAction::operator <<(const TAddress _ptr) {  this->m_data = _ptr ; return *this; } 

/////////////////////////////////////////////////////////////////////////////

CException:: CException (void) { m_ptrs = nullptr; }
CException:: CException (const CException& _ref) : CException() { *this = _ref; }
CException:: CException (const TPointers* _ptrs) : CException() { *this << _ptrs; }
CException::~CException (void) {}

/////////////////////////////////////////////////////////////////////////////

const CAction&   CException::Cause (void) const { return this->m_action; }
const TPointers* CException::Pointers(void) const { return this->m_ptrs; }
const CExState&  CException::State (void) const { return this->m_state; }

/////////////////////////////////////////////////////////////////////////////

bool CException::Is (void) const { return CAccepted()(this->Pointers()); }

bool CException::Set (const TPointers* _ptrs) {
	bool b_changed = (this->Pointers() != _ptrs);
	if ( b_changed ) {
		this->m_ptrs = const_cast<TPointers*>(_ptrs);
		this->m_action << this->Pointers();
		this->m_state  << this->Pointers();
	}
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CException&  CException::operator = (const CException& _ref) { *this << _ref.Pointers(); return *this; }
CException&  CException::operator <<(const TPointers* _ptrs) {  this->Set(_ptrs); return *this; }

/////////////////////////////////////////////////////////////////////////////

CException::operator const TPointers* (void) const { return this->Pointers(); }
CException::operator const CString (void) const { return CException::ToString(this->Pointers()); }

/////////////////////////////////////////////////////////////////////////////

CString CException::ToString (void) const {
	return CException::ToString(this->Pointers());
}

CString CException::ToString (const TPointers*) { return CString(_T("#n/a"));}

/////////////////////////////////////////////////////////////////////////////

CEx_Base:: CEx_Base (const DWORD _value) : m_value(_value) {}
CEx_Base:: CEx_Base (const CEx_Base& _ref) : CEx_Base() { *this = _ref; }
CEx_Base:: CEx_Base (const TPointers* _ptrs) : CEx_Base() { *this << _ptrs; }
CEx_Base:: CEx_Base (const TRecord* _record) : CEx_Base() { *this << _record; }
CEx_Base::~CEx_Base (void) {}

/////////////////////////////////////////////////////////////////////////////

DWORD   CEx_Base::Get (void) const { return this->m_value; }
bool    CEx_Base::Set (const DWORD _value) { bool b_changed = (_value != *this); if (b_changed) this->m_value = _value; return b_changed; }
HRESULT CEx_Base::Set (const TPointers* _ptrs) { if (nullptr == _ptrs) return E_POINTER; else return this->Set(_ptrs->ExceptionRecord); }
HRESULT CEx_Base::Set (const TRecord* _record) { if (nullptr == _record) return E_POINTER; else { this->Set(_record->ExceptionFlags); return S_OK;}}

bool    CEx_Base::Has (const DWORD _value) const { return 0 != (_value & this->Get());}

/////////////////////////////////////////////////////////////////////////////

CEx_Base&  CEx_Base::operator = (const CEx_Base& _ref) { *this << _ref; return *this; }
CEx_Base&  CEx_Base::operator <<(const DWORD _value) { this->Set(_value); return *this; }
CEx_Base&  CEx_Base::operator <<(const TPointers* _ptrs) { this->Set(_ptrs); return *this; }
CEx_Base&  CEx_Base::operator <<(const TRecord* _record) { this->Set(_record); return *this; }

CEx_Base::operator DWORD (void) const { return this->Get(); }

/////////////////////////////////////////////////////////////////////////////

CExState:: CExState (const DWORD _flags) : TBase(_flags), m_continue(false) { m_unwind << _flags; }
CExState:: CExState (const CExState& _ref) : CExState() { *this = _ref; }
CExState::~CExState (void) {}

/////////////////////////////////////////////////////////////////////////////

bool  CExState::CanContinue (void) const { return TBase::Has(EXCEPTION_NONCONTINUABLE) || this->m_continue; }

bool  CExState::Set (DWORD _value) {
	bool b_result = TBase::Set(_value); this->m_unwind << _value;
	return b_result;
}

HRESULT  CExState::Set (const TPointers* _ptrs) {
	HRESULT h_result = CAccepted()(_ptrs) ? S_OK : E_POINTER;

	if (SUCCEEDED(h_result)) {
		(TBase&)*this << (TBase&)this->m_unwind << _ptrs;
		m_continue = 0 != (EXCEPTION_NONCONTINUABLE_EXCEPTION & _ptrs->ExceptionRecord->ExceptionCode);
	}
	else
		m_continue = false;

	return h_result;
}

const
CExUnwind& CExState::Unwind (void) const { return this->m_unwind; }

/////////////////////////////////////////////////////////////////////////////

CExState&  CExState::operator = (const CExState& _ref) { (TBase&)*this = (TBase&)m_unwind = (const TBase&) _ref; *this << _ref.m_continue; return *this; }
CExState&  CExState::operator <<(const TPointers* _ptrs) { this->Set(_ptrs); return *this; }

CExState&  CExState::operator <<(bool _b_continue) { this->m_continue = _b_continue; return *this; }

/////////////////////////////////////////////////////////////////////////////

CExUnwind:: CExUnwind (void) : TBase() {}
CExUnwind:: CExUnwind (const CExUnwind& _ref) : CExUnwind() { *this = _ref; }
CExUnwind::~CExUnwind (void) {}

/////////////////////////////////////////////////////////////////////////////

bool CExUnwind::IsCollided (void) const { return TBase::Has(eStage::eCollided); }
bool CExUnwind::IsExiting  (void) const { return TBase::Has(eStage::eExit); }
bool CExUnwind::InProgress (void) const { return TBase::Has(eStage::eProgress); }
bool CExUnwind::IsTargeted (void) const { return TBase::Has(eStage::eTargeted); }

bool CExUnwind::Is (void) const { return this->InProgress() || this->IsCollided() || this->IsExiting() || this->IsTargeted(); }

/////////////////////////////////////////////////////////////////////////////

CExUnwind&  CExUnwind::operator = (const CExUnwind& _ref) { (TBase&)*this = (const TBase&)_ref; return *this; }

CExUnwind::operator bool (void) const { return this->Is(); }

/////////////////////////////////////////////////////////////////////////////

CTranslator:: CTranslator (void) noexcept : CTranslator(CTranslator::Do) {}
CTranslator:: CTranslator (_se_translator_function _p_fun) noexcept : m_prev_func{ _set_se_translator(_p_fun) }  {}
CTranslator::~CTranslator (void) noexcept { _set_se_translator(this->m_prev_func); }

/////////////////////////////////////////////////////////////////////////////

void CTranslator::Do (UINT _u_code, TPointers* _ptrs) { _u_code; _ptrs;/* throw CException(_ptrs); */}
