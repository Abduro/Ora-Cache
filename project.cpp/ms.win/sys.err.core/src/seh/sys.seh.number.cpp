/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-May-2024 at 14:16:27.4165176, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack errno constant enumeration interface implementation file;
*/
#include "sys.seh.number.h"

using namespace shared::sys_core::seh;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core { namespace seh { namespace _impl {
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/errno-constants ;
}}}}
using namespace shared::sys_core::seh::_impl;
/////////////////////////////////////////////////////////////////////////////

CNumber:: CNumber (void) : TBase() {}
CNumber:: CNumber (const CNumber& _ref) : CNumber() { *this = _ref; }
CNumber:: CNumber (const errno_l _code, _pc_sz _p_alias, _pc_sz _p_desc) : CNumber() { *this >> _p_alias << _code << _p_desc; }
CNumber::~CNumber (void) {}

/////////////////////////////////////////////////////////////////////////////

bool      CNumber::Is (void) const { return (!!this->Code() && !this->m_desc.IsEmpty()); }

#if defined(_DEBUG)
CString   CNumber::Print (const e_print e_opt) const {
	return  TBase::Print (e_opt, (_pc_sz)__CLASS__);
}
#endif
/////////////////////////////////////////////////////////////////////////////

CNumber&  CNumber::operator = (const CNumber& _src) { (TBase&)*this = (const TBase&)_src; return *this; }

/////////////////////////////////////////////////////////////////////////////
#if (0)
CNumber_Enum:: CNumber_Enum (void) { this->Set(); }
CNumber_Enum:: CNumber_Enum (const CNumber_Enum& _ref) { *this = _ref; }
CNumber_Enum::~CNumber_Enum (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TNumbers& CNumber_Enum::Get (void) const { return this->m_numbers; }

err_code  CNumber_Enum::Set (void) {

	err_code n_result =  TErrCodes::no_error;

	if (this->m_numbers.empty() == false)
		this->m_numbers.clear();

	for (uint16_t i_ = 0; i_ < _countof(numbers); i_++)
		this->m_numbers.insert(
			::std::make_pair(numbers[i_]._code,  CNumber(numbers[i_]._code, numbers[i_]._p_sz_short, numbers[i_]._p_sz_desc)
			));

	return n_result;
}

err_code  CNumber_Enum::Set (const TNumbers& _numbers) {
	_numbers;
	err_code n_result = TErrCodes::no_error;
	// https://stackoverflow.com/questions/1067422/how-can-i-append-the-content-of-one-map-to-another-map ;
	// https://en.cppreference.com/w/cpp/iterator/insert_iterator ;
	::std::copy(_numbers.begin(), _numbers.end(), ::std::insert_iterator(this->m_numbers, this->m_numbers.begin()));

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

bool CNumber_Enum::Has (errno_t _value) const { return this->Get().end() != this->Get().find(_value); }
const
CNumber& CNumber_Enum::Find (errno_t _value) const {
	_value;

	TNumbers::const_iterator it_found = this->Get().find(_value);

	if (this->Get().end() == it_found) {
		static CNumber fake_(numbers[0]._code, numbers[0]._p_sz_short, numbers[0]._p_sz_desc);
		return fake_;
	}
	else
		return it_found->second;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CNumber_Fake:: CNumber_Fake (void) : TBase() { this->Set(); }
CNumber_Fake::~CNumber_Fake (void) {}

/////////////////////////////////////////////////////////////////////////////

bool CNumber_Fake::Has (errno_l _value) const { return (this->Get().end() != this->Get().find(_value)); }
const
CNumber& CNumber_Fake::Find (errno_l _value) const {
	_value;
	TSafe_No();
	TNumbers::const_iterator it_found = this->Get().find(_value);

	if (this->Get().end() == it_found) {
		static CNumber fake_;

		fake_ >> _T("#FAKE") << TString().Format(_T("Fake exception number<%d>"), _value) << _value;

		return fake_;
	}
	else
		return it_found->second;
}
const
TNumbers& CNumber_Fake::Get (void) const { return this->m_numbers; }
err_code  CNumber_Fake::Set (void) {

	err_code n_result = TErrCodes::no_error;

	if (this->m_numbers.empty() == false)
		this->m_numbers.clear();

	try {
		this->m_numbers.insert(::std::make_pair(EINVAL, CNumber(EINVAL, _T("#EINVAL"), _T("Invalid value."))));
		this->m_numbers.insert(::std::make_pair(ERANGE, CNumber(ERANGE, _T("#ERANGE"), _T("Memory overlapping or out of range."))));
	}
	catch (const ::std::bad_alloc&) {
		n_result = __e_no_memory;
	}

	return n_result;

}
/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString CNumber_Fake::Print (_pc_sz _pfx, _pc_sz _sfx) const {
	_pfx;_sfx;

	static _pc_sz p_sz_pat = _T("cls::[%s]%s%s");

	CString cs_out;
	CString cs_numbers;

	for (TNumbers::const_iterator it_ = this->Get().begin(); it_ != this->Get().end(); ++it_) {

		cs_numbers += _pfx;
		cs_numbers += it_->second.Print(CNode::e_req);
		cs_numbers += _sfx;

	}

	cs_out.Format(p_sz_pat, (_pc_sz)__CLASS__, _sfx, (_pc_sz)cs_numbers);

	return  cs_out;
} 
#endif

/////////////////////////////////////////////////////////////////////////////

CNumber_Fake& CNumber_Fake::Ref (void) {

	static CNumber_Fake the_fake;
	return the_fake;
}