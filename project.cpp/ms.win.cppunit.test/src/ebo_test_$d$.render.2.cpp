/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2025 at 03:37:11.884, UTC+4, Batumi, Tuesday;
	This is Ebo Pack DirectX.12 draw renderer lib unit test interface implementation file;
*/
#include "ebo_test_$d$.render.2.h"

using namespace ebo::boo::test::draw::_12;

/////////////////////////////////////////////////////////////////////////////

CAdapter:: CAdapter (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}
CAdapter::~CAdapter(void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CAdapter::_ctor (void) {
//	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TAdapter().Print();
		_out()();
//	}
}

/////////////////////////////////////////////////////////////////////////////

void CAda_enum::Do (void) {
	TAda_enum ada_enum;

	if (__succeeded(ada_enum.Set())) {

		_out() += TLog_Acc::e_new_line;

		const TAdapters& adapters = ada_enum.Get();
		for (size_t i_ = 0; i_ < adapters.size(); i_++) {
			const TAdapter& adapter = adapters.at(i_);
			_out() += adapter.Print();
		}
	}
	else {
		_out() += ada_enum.Error().Print(TError::e_print::e_req);
	}
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CAlphaMode::CAlphaMode (const bool _b_verb) : m_b_verb(_b_verb) {
	this->m_mode << (uint32_t* const)&this->m_sync;
}

/////////////////////////////////////////////////////////////////////////////

bool CAlphaMode::Set (const TAlphaMode::e_mode _e_mode) {
	_e_mode;
#if (0)
	const bool b_changed = (this->m_mode.Get() != _e_mode);
	if (b_changed)
		this->m_mode.Set(_e_mode);
	return b_changed;
#else
	return this->m_mode.Set(_e_mode);
#endif
}

void CAlphaMode::Set(void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("alpha value sync before: %d"), this->m_sync);

	this->m_mode.Set(TAlphaMode::e_mode::e_premulti);

	_out() += this->m_mode.Print(e_print::e_all);
	_out() += TStringEx().Format(_T("alpha value sync after: %d"), this->m_sync);
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CFac_6:: CFac_6 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb){
	}
}

/////////////////////////////////////////////////////////////////////////////

void CFac_6::Create (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	this->m_fac_6.Create();
	if (this->m_fac_6.Error())
		_out() += this->m_fac_6.Error().Print(TError::e_print::e_req);
	else
		_out() += this->m_fac_6.Print(e_print::e_all);
	_out()();
}

void CFac_6::Enum_Hi_perf (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}

	this->m_fac_6.Create();
	if (this->m_fac_6.Error()) {
		_out() += this->m_fac_6.Error().Print(TError::e_print::e_req);
		_out()();
		return ;
	}
//	if (this->m_fac_6.Is_valid()) {
		if (__succeeded(this->m_fac_6.Get_Hi_Perf())) {
			const TAdapters& a_set = this->m_fac_6.Cached();
			if (a_set.size()) { // expected to be not 0;
				const TAdapter& a_hi_perf = a_set.at(0); // the best is the first one;
				_out() += a_hi_perf.Print();
			}
		}
//	}
	if (this->m_fac_6.Error())
		_out() += this->m_fac_6.Error().Print(TError::e_print::e_req);
	_out()();
}

void CFac_6::Enum_Lo_power (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	this->m_fac_6.Create();
	if (this->m_fac_6.Error()) {
		_out() += this->m_fac_6.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
//	if (this->m_fac_6.Is_valid()) {
		if (__succeeded(this->m_fac_6.Get_Lo_Power())) {
			const TAdapters& a_set = this->m_fac_6.Cached();
			if (a_set.size()) { // expected to be not 0;
				const TAdapter& a_lo_pow = a_set.at(0); // the best is the first one;
				_out() += a_lo_pow.Print();
			}
		}
//	}
	if (this->m_fac_6.Error())
		_out() += this->m_fac_6.Error().Print(TError::e_print::e_req);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CDev_warp:: CDev_warp (const bool _b_verb) : m_b_verb(_b_verb){
	if (this->m_b_verb){}
}

/////////////////////////////////////////////////////////////////////////////

void  CDev_warp::Create (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	// it is expected to receive the error: 'No such interface supported';
	// in case when this project is tested on virtual remote machine;
	TWarp_Enum warp_enum;
	warp_enum.Set();
	if (warp_enum.Error()) {
		_out() += warp_enum.Error().Print(TError::e_print::e_req);
	}
	else {
		const TWarp_ada& warp_ada = warp_enum.Get();
		this->m_device.Create(warp_ada);

		if (this->m_device.Error())
			_out() += this->m_device.Error().Print(TError::e_print::e_req);
		else
			_out() += _T("The device is created successfully;");
	}
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CPxFormat:: CPxFormat (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	TWrapPtr wrp_ptr(new TWrapper);
	this->m_px_fmt << wrp_ptr;
}

/////////////////////////////////////////////////////////////////////////////

void CPxFormat::Set (void) {
	_out() += TLog_Acc::e_new_line;
	if (nullptr == this->m_px_fmt.Sync()) {
		_out() += _T("Px-format sync wrapper is not set;");
		_out()();
		return;
	}

	_out() += TStringEx().Format(_T("px-format sync values before: alpha=%d;format=%d"),
		this->m_px_fmt.Sync()->ref().AlphaMode, this->m_px_fmt.Sync()->ref().Format
	);

	this->m_px_fmt.Alpha() << TAlphaMode::e_mode::e_straith;
	this->m_px_fmt << TClrBits::DXGI_FORMAT_B8G8R8A8_UNORM;

	_out() += this->m_px_fmt.Print(e_print::e_all);
	_out() += TStringEx().Format(_T("px-format sync values after: alpha=%d;format=%d"),
		this->m_px_fmt.Sync()->ref().AlphaMode, this->m_px_fmt.Sync()->ref().Format
	);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CSize::CSize (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb){
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	TWrapPtr wrp_ptr(new TWrapper);
	this->m_size << wrp_ptr;
}

/////////////////////////////////////////////////////////////////////////////

void CSize::Set (void) {
	_out() += TLog_Acc::e_new_line;
	if (nullptr == this->m_size.Sync()) {
		_out() += _T("surface size sync wrapper is not set;");
		_out()();
		return;
	}

	_out() += TStringEx().Format(_T("surface size sync values before: height=%d;width=%d"),
		this->m_size.Sync()->ref().Height, this->m_size.Sync()->ref().Width
	);

	this->m_size.Set(800, 600);

	_out() += this->m_size.Print(e_print::e_all);
	_out() += TStringEx().Format(_T("surface size sync values after: height=%d;width=%d"),
		this->m_size.Sync()->ref().Height, this->m_size.Sync()->ref().Width
	);
	_out()();
}