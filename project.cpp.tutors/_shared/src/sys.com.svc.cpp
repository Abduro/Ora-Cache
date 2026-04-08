/*
	Created by Tech_dog (ebontrop@gmail.com) on 2-May-2012 at 9:07:10am, GMT+3, Rostov-on-Don, Wednesday;
	This is PulsePay project COM libraries auto-initializer interface implementation files;
	-----------------------------------------------------------------------------
	Adopted to Platinum project on 19-Mar-2014 at 10:52:48am, GMT+4, Taganrog, Wednesday;
	Adopted to File Guardian project on 11-Jul-2018 at 10:29:17a, UTC+7, Phuket, Rawai, Wednesday;
	Adopted to FakeGPS driver project on 13-Dec-2019 at 10:18:13a, UTC+7, Novosibirsk, Friday;
	Adopted to Geometry Curve project on 18-Feb-2024 at 08:50:46.2229285, UTC+7, Novosibirsk, Sunday;
*/
#include "sys.com.svc.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::sys_core;

namespace shared { namespace sys_core { namespace _impl {

}}} using namespace _impl;

#pragma region cls::c_com_init{}

CString c_com_init::To_str (const e_flags _e_flag) {
	_e_flag;
	CString cs_out;
	switch (_e_flag) {
	case e_flags::e_co_apart  : cs_out = _T("e_co_apart"); break;
	case e_flags::e_co_threads: cs_out = _T("e_co_threads"); break;
	case e_flags::e_co_no_ole1: cs_out = _T("e_co_no_ole1"); break;
	case e_flags::e_co_fast   : cs_out = _T("e_co_fast"); break;
	default: cs_out = _T("#undef");
	}
	return  cs_out;
}

#pragma endregion
#pragma region cls::CCoIniter{}

static _pc_sz p_err_com_not_inited = _T("#__e_state: com-system is not inited yet");

CCoIniter::CCoIniter (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited = p_err_com_not_inited; }

TError&  CCoIniter::Error (void) const { return this->m_error; }

err_code CCoIniter::Init (bool _b_STA) {
	_b_STA;
	this->m_error << __METHOD__ << __s_ok;

	if (false == _b_STA)
	     m_error << ::CoInitializeEx(0, c_com_init::e_co_threads); // https://learn.microsoft.com/en-us/windows/win32/api/objbase/ne-objbase-coinit ;
	else m_error << ::CoInitialize(0); // https://learn.microsoft.com/en-us/windows/win32/api/objbase/nf-objbase-coinitialize ;

	if (false) {}
	else if (__s_false == (err_code) this->Error()) { this->m_error = _T("#__e_state: com-system is already inited in this thread"); __trace_err_ex_2(this->Error()); }
	else if (RPC_E_CHANGED_MODE == (err_code) this->Error()) { this->m_error = _T("#__e_state: com-system is inited by other thread"); __trace_err_ex_2(this->Error()); }
	else {} // the error already is set;

	return this->Error();
}

err_code CCoIniter::Init (const c_com_init::e_flags _e_flag/* = c_com_init::e_co_threads*/) {
	_e_flag;
	this->m_error << __METHOD__ << ::CoInitializeEx(0, _e_flag);
	return this->Error();
}

err_code CCoIniter::Uninit (void) {
	if (this->Error())
		return this->Error(); // not inited yet;

	::CoUninitialize(); // no error is thrown;
	this->m_error << __METHOD__ << __e_not_inited = p_err_com_not_inited;
	return __s_ok;
}

CCoIniter::operator const bool (void) const { return false == this->Error(); }

#pragma endregion
#pragma region cls::CCoIniter_auto{}

CCoIniter_auto:: CCoIniter_auto (const c_com_init::e_flags _e_flag/* = c_com_init::e_co_threads*/) : TBase() { TBase::Init(_e_flag); }
CCoIniter_auto::~CCoIniter_auto (void) { TBase::Uninit(); }

#pragma endregion
#pragma region cls::CCoSecProvider{}

CCoSecProvider::CCoSecProvider (void) { this->m_error >> __CLASS__ << __METHOD__<<__e_not_inited; }

TErrorRef CCoSecProvider::Error (void) const { return this->m_error; }

err_code  CCoSecProvider::Init (const e_co_sec_auth::e_levels _auth_lvl, const e_co_sec_imp::e_levels _imp_lvl) {
	_auth_lvl; _imp_lvl;
	this->m_error << __METHOD__
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-coinitializesecurity ;
	<< ::CoInitializeSecurity(
		NULL     ,                   // security descriptor;
		-1       ,                   // COM negotiates authentication service;
		NULL     ,                   // authentication services;
		NULL     ,                   // reserved;
		_auth_lvl,
		_imp_lvl ,
		NULL     ,
		EOAC_NONE,
		NULL
	);

	if (false) {}
	else if (E_INVALIDARG == (err_code) this->Error()) {}
	else if (RPC_E_TOO_LATE == (err_code) this->Error()) this->m_error = _T("#__e_state: must be inited before iface marshalling");
	else if (RPC_E_NO_GOOD_SECURITY_PACKAGES == (err_code) this->Error()) this->m_error = _T("#__e_state: sec level is not safe");
	else if (E_OUTOFMEMORY ==  (err_code) this->Error()) this->m_error = _T("#__e_fail: generic internal error");

	return this->Error();
}

err_code CCoSecProvider::Default (void) { return this->Init(e_co_sec_auth::e_default, e_co_sec_imp::e_impersonate); }
err_code CCoSecProvider::NoIdentity (void) { return this->Init(e_co_sec_auth::e_none, e_co_sec_imp::e_identity); }

#pragma endregion