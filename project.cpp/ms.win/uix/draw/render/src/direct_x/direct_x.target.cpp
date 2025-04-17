/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Apr-2025 at 18:30:30.820, UTC+4, Batumi, Saturday;
	This is Ebo Pack DirectX renderer target view wrapper interface implementation file; 
*/
#include "direct_x.target.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x {

namespace _11 {

/////////////////////////////////////////////////////////////////////////////

CTarget:: CTarget (void) { this->m_error >>__CLASS__ << __METHOD__ << __e_not_inited; }

err_code  CTarget::Create(void) {
	this->m_error << __METHOD__ << __s_ok;

	if (false == this->m_device.Is_valid())
		return  (this->m_error << (err_code)TErrCodes::eExecute::eParamerer) = _T("The device is invalid");

	if (false == this->m_swap.Is_valid())
		return  (this->m_error << (err_code)TErrCodes::eExecute::eParamerer) = _T("The swap chain is invalid");

	return this->Error();
}

TError&   CTarget::Error (void) const { return this->m_error; }
bool      CTarget::Is_valid (void) const { return false; }

#if defined(_DEBUG)
CString   CTarget::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{;valid=%s}");

	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

err_code  CTarget::Set (const CDevice& _device) {
	_device;
	this->m_error << __METHOD__ << __s_ok;

	if (false == _device.Is_valid())
		return this->m_error << __e_invalid_arg;

	if (this->m_device.Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	this->m_device.Ptr(_device.Ptr());

	return this->Error();
}
err_code  CTarget::Set (const CSwapChain& _chain) {
	_chain;
	this->m_error << __METHOD__ << __s_ok;

	if (false == _chain.Is_valid())
		return this->m_error << __e_invalid_arg;

	if (this->m_swap.Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	this->m_swap.Ptr(_chain.Ptr());

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CTarget&  CTarget::operator <<(const CDevice& _device) { this->Set(_device); return *this; }
CTarget&  CTarget::operator <<(const CSwapChain& _chain) { this->Set(_chain); return *this; }

}

namespace _12 {
}

}}}