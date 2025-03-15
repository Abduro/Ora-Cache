/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-May-2024 at 23:03:03.3846217, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack system SEH EXCEPTION_RECORD code enumeration interface implementation file;
*/
#include "sys.seh.code.h"

using namespace shared::sys_core::seh;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core { namespace seh { namespace _impl {

	struct _code_raw : _raw_data { DWORD n_origin; };

	using TValues = CCode::_values;

	/*static */_code_raw raw_codes[] = {
		{ TValues::e_acc_violate, _T("#ACC_VIOLATE"), _T("Access violation to virtual address of memory."), __ex_acc_violate},
		{ TValues::e_out_bounds , _T("#OUT_RANGE")  , _T("Access to an element by invalid index.")        , __ex_out_bounds },
		{ TValues::e_dbg_break  , _T("#DBG_BREAK")  , _T("A breakpoint was encountered.")                 , __ex_dbg_break  },
//		{ TValues::e_bad_align  , _T("#NOT_ALIGNED"), _T("Out of byte boundaries.")                       , __ex_bad_align  },
//		{ TValues::e_not_operand, _T("#FLT_OPERAND"), _T("The value is small to hold float data type.")   , __ex_not_operand},
		{ TValues::e_div_flt_0  , _T("#DIV_FLT_0")  , _T("Division by zero.")                             , __ex_div_flt_0  },
		{ TValues::e_div_int_0  , _T("#DIV_INT_0")  , _T("Division by zero.")                             , __ex_div_int_0  },
		{ TValues::e_ovr_stack  , _T("#OVERFLOW" )  , _T("Stack is overflowed.")                          , __ex_ovr_stack  },
		{ TValues::e_err_page   , _T("#PAGE_ERR" )  , _T("Page of data is lost.")                         , __ex_err_page   },
	};

}}}}
using namespace shared::sys_core::seh::_impl;

/////////////////////////////////////////////////////////////////////////////

CCode:: CCode (void) : TBase(), m_origin(0) {}
CCode:: CCode (const CCode& _ref) : CCode() { *this = _ref; }
CCode:: CCode (const errno_l _code, _pc_sz _alias, _pc_sz _desc, uint32_t _origin) : TBase(_code, _alias, _desc), m_origin(_origin) {}
CCode::~CCode (void) {}

/////////////////////////////////////////////////////////////////////////////

bool CCode::Is (void) const { return (TBase::Is() && !TBase::m_alias.IsEmpty()); }

#if defined(_DEBUG)
CString     CCode::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat = _T("%s;origin=0x%x;");
	CString cs_out; cs_out.Format(pc_sz_pat, (_pc_sz)TBase::Print (e_opt, (_pc_sz)__CLASS__), this->Origin());
	return  cs_out;
}
#endif

uint32_t CCode::Origin (void) const { return this->m_origin; }
bool CCode::Origin (uint32_t _value) {
	_value;
	const bool b_changed = this->Origin() != _value;
	if (b_changed) {
		this->m_origin = _value;
		TBase::m_code = __sys_ex_code_2_errno(_value);
	}

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CCode&  CCode::operator = (const CCode& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Origin(); return *this; }

CCode&  CCode::operator <<(const uint32_t _origin) { this->Origin(_origin); return *this; }

/////////////////////////////////////////////////////////////////////////////

CCode_Fake:: CCode_Fake (void) : TBase() { this->Set(); }
CCode_Fake::~CCode_Fake (void) {}

/////////////////////////////////////////////////////////////////////////////

bool CCode_Fake::Has (errno_l _value) const { return (this->Get().end() != this->Get().find(_value)); }
const
CCode& CCode_Fake::Find (errno_l _value) const {
	_value;
	TSafe_Code();
	TCodes::const_iterator it_found = this->Get().find(_value);

	if (this->Get().end() == it_found) {
		static CCode fake_;

		fake_ >> _T("#FAKE") << TString().Format(_T("Fake exception code<%d>"), _value) << _value;

		return fake_;
	}
	else
		return it_found->second;
}
const
CCode& CCode_Fake::Find (uint32_t _u_origin) const {
	_u_origin;
	TSafe_Code();
	for (TCodes::const_iterator it_ = this->Get().begin(); it_ != this->Get().end(); ++it_) {
		if (it_->second.Origin() == _u_origin)
			return it_->second;
	}
	static CCode fake_;

	fake_ >> _T("#FAKE") << (_pc_sz)TString().Format(_T("Fake exception code origin<0x%x>"), _u_origin) << (errno_l)__sys_ex_code_2_errno(_u_origin);
	fake_ << _u_origin;

	return fake_;

}

/////////////////////////////////////////////////////////////////////////////
const
CCode&   CCode_Fake::Get (const TPointers* const _pointers) const {
	_pointers;
	if (!CAccepted()(_pointers)) {
		static CCode inv_code(__HresultToDword(E_POINTER), _T("#pointer"), _T("Invalid exception pointers."), 0); // works like an error object;
		return inv_code;
	}
	return this->Get(_pointers->ExceptionRecord);
}
const
CCode&   CCode_Fake::Get (const TRecord* const _p_rec) const {
	_p_rec;
	if (!CAccepted()(_p_rec)) {
		static CCode inv_code(__HresultToDword(E_POINTER), _T("#pointer"), _T("Invalid exception record."), 0); // works like an error object;
		return inv_code;
	}
	return this->Find((uint32_t)_p_rec->ExceptionCode);
}

const
TCodes&  CCode_Fake::Get (void) const { return this->m_codes; }
err_code CCode_Fake::Set (void) {

	err_code n_result = TErrCodes::no_error;

	if (this->m_codes.empty() == false)
		this->m_codes.clear();
#if (0)
	try {
		this->m_codes.insert(::std::make_pair(CCode::eAccessViolate, CCode(CCode::eAccessViolate, _T("#ACC_VIOLATE"), _T("Access violation to virtual address of memory."))));
		this->m_codes.insert(::std::make_pair(CCode::eOutOfBounds  , CCode(CCode::eOutOfBounds  , _T("#OUT_RANGE"), _T("Access to an element by invalid index."))));
	}
	catch (const ::std::bad_alloc&) {
		n_result = __e_no_memory;
	}
#else
	for (uint16_t i_ = 0; i_ < _countof(raw_codes); i_++)
		this->m_codes.insert(
			::std::make_pair(
				raw_codes[i_]._code,  CCode(raw_codes[i_]._code, raw_codes[i_]._p_alias, raw_codes[i_]._p_desc, raw_codes[i_].n_origin)
			));
#endif

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

const CCode&  CCode_Fake::operator <<(const TPointers* const _p_ptrs) { return this->Get(_p_ptrs); }
const CCode&  CCode_Fake::operator <<(const TRecord* const _p_rec) { return this->Get(_p_rec); }

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString CCode_Fake::Print (_pc_sz _pfx, _pc_sz _sfx) const {
	_pfx;_sfx;

	static _pc_sz p_sz_pat = _T("cls::[%s]%s%s");

	CString cs_out;
	CString cs_codes;

	for (TCodes::const_iterator it_ = this->Get().begin(); it_ != this->Get().end(); ++it_) {

		cs_codes += _pfx;
		cs_codes += it_->second.Print(CNode::e_req);
		cs_codes += _sfx;

	}

	cs_out.Format(p_sz_pat, (_pc_sz)__CLASS__, _sfx, (_pc_sz)cs_codes);

	return  cs_out;
} 
#endif

/////////////////////////////////////////////////////////////////////////////

CCode_Fake& CCode_Fake::Ref (void) {

	static CCode_Fake the_fake;
	return the_fake;
}