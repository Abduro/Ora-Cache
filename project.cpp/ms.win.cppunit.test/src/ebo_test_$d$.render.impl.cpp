/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Apr-2025 at 18:52:18.176, UTC+4, Batumi, Sunday;
	This is Ebo Pack 2D/3D draw renderer lib unit test helper interface implementation file; 
*/
#include "ebo_test_$d$.render.impl.h"

using namespace ebo::boo::test::_impl;

/////////////////////////////////////////////////////////////////////////////

bool CBuff_Sync::IBuffer_OnCount (const uint32_t _n_value) {
	_n_value;
	_out() += TStringEx().Format(
		_T("cls::[%s::%s].%s(count=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _n_value
	);
	return true;
}

bool CBuff_Sync::IBuffer_OnUsage (const uint32_t _n_value) {
	_n_value;
	_out() += TStringEx().Format(
		_T("cls::[%s::%s].%s(usage=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _n_value
	);
	return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CSample_Sync::ISample_OnCount (const uint32_t _n_value) {
	_n_value;
	_out() += TStringEx().Format(
		_T("cls::[%s::%s].%s(count=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _n_value
	);
	return true;
}

bool CSample_Sync::ISample_OnQuality (const uint32_t _n_value) {
	_n_value;
	_out() += TStringEx().Format(
		_T("cls::[%s::%s].%s(quality=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _n_value
	);
	return true;
}

/////////////////////////////////////////////////////////////////////////////

CFake_Wnd:: CFake_Wnd (const bool _b_verb) : m_verb(_b_verb) {
	if (this->m_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;
	TBase::Create(HWND_MESSAGE);

	if (false == TBase::IsWindow())
		this->m_error.Last();
	else
		this->m_error << __s_ok;
	if (this->Error())
		_out() += this->Error().Print(TError::e_print::e_req);
	_out()();
}

CFake_Wnd::~CFake_Wnd (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	if (TBase::IsWindow())
		TBase::DestroyWindow();
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

TError&  CFake_Wnd::Error (void) const { return this->m_error; }

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { namespace _impl { namespace _11 {

CFake_Desc:: CFake_Desc (const bool _b_verb) : m_verb(_b_verb) {
	if (this->m_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;

	this->Trick();
	if (this->Error())
		_out() += this->Error().Print(TError::e_print::e_req);
	if (this->m_verb)
	_out()();
}

CFake_Desc::~CFake_Desc (void) {
	if (this->m_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

TError&  CFake_Desc::Error (void) const { return this->m_error; }

err_code CFake_Desc::Trick (void) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->m_wnd.Error())
		return (this->m_error = this->m_wnd.Error());

	this->m_desc.Fake();
	this->m_desc.Target(m_wnd);

	if (false == this->m_desc.Is_valid())
		this->m_error = this->m_desc.Error();

	return this->Error();
}

const
TSwapDesc&  CFake_Desc::Ref (void) const { return this->m_desc; }
TSwapDesc&  CFake_Desc::Ref (void)       { return this->m_desc; }

/////////////////////////////////////////////////////////////////////////////

CFake_Swap:: CFake_Swap (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;

	_out()();
}

CFake_Swap::~CFake_Swap (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

err_code CFake_Swap::Create (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	this->m_error << __METHOD__ << __s_ok;

	if (this->m_chain.Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	CFac_2 fac_2;
	fac_2.Ptr(this->m_fac_2.Ptr());
	if (false == fac_2.Is_valid())
		fac_2.Create();
	if (fac_2.Error())
		return this->m_error = fac_2.Error();

	CDev_HW device;
	device.Create();
	if (device.Error())
		return this->m_error = device.Error();

	CFake_Desc desc; desc.Trick();
	if (desc.Error())
		return this->m_error = desc.Error();

	fac_2.Get(device, desc.Ref(), this->m_chain);
	if (fac_2.Error())
			this->m_error = fac_2.Error();

	return this->Error();
}

TError&  CFake_Swap::Error (void) const { return this->m_error; }
const
TSwap&   CFake_Swap::Ref (void) const { return this->m_chain; }

err_code CFake_Swap::Set (const CFac_2& _fac_2) {
	this->m_error << __METHOD__ << __s_ok;

	if (false == _fac_2.Is_valid())
		this->m_error = _fac_2.Error();
	else
		this->m_fac_2.Ptr(_fac_2.Ptr());

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

}}}}}