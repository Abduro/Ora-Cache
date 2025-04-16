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
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz)TAdapter().Print());
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

CFac_4:: CFac_4 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	this->Create();
	if (this->m_b_verb) {
		_out()();
	}
}

CFac_4::~CFac_4 (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CFac_4::Create (void) {
	if (this->m_fac_4.Is_valid())
		return;

	this->m_fac_4.Create();
	if (this->m_fac_4.Error())
		_out() += this->m_fac_4.Error().Print(TError::e_print::e_req);
	else
		_out() += _T("The factory#4 is created successfully;");

	_out()();
}

void CFac_4::GetAdapter (void) {
	_out() += TLog_Acc::e_new_line;

	if (false  == this->m_fac_4.Is_valid()) {
		_out() += this->m_fac_4.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	TAdapter adapter;
	this->m_fac_4.Get(adapter);

	if (this->m_fac_4.Error())
		_out() += this->m_fac_4.Error().Print(TError::e_print::e_req);
	else {
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) adapter.Print());
	}
	_out()();
}

void CFac_4::GetSwapChain (void) {
	_out() += TLog_Acc::e_new_line;
	// (1) checks the factory object first;
	if (false == this->m_fac_4.Is_valid()) {
		_out() += this->m_fac_4.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
#if (0)
	// doesn't work and leads to the error: 'E_NOINTERFACE No such interface supported.';
	// (2) creates warp-adapter object;
	TWarp_enum warp_enum;

	warp_enum.Set(); // tries to enumerate all available warp adapters;
	if (warp_enum.Error()) {
		_out() += warp_enum.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
	TAda_Warp ada_warp = warp_enum.Get();
	if (false == ada_warp.Is()) {
		_out() += _T("#error: Cannot create warp-adapter;");
		_out()();
		return;
	}

	// (3) creates warp-device from warp-adapter;
	TDev_Warp device;
	device.Create(ada_warp);
	if (device.Error()) {
		_out() += device.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
#else

	TAdapter adapter; // this adapter may be not suitable for the device creating, due to this adapter cannot be used for output of graphics;
	this->m_fac_4.Get(adapter);
	if (this->m_fac_4.Error()) {
		_out() += this->m_fac_4.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	// (2) creates a default device object;
	TDevice_HW device;
	device.Create(adapter);

	if (device.Error()) {
		_out() += device.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
#endif
	// (3) creates a command queue;
	TCmdQueue  cmd_que;
	device.Get(cmd_que);
	if (device.Error()) {
		_out() += device.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	this->m_fac_4 << device;

	this->m_fac_4.Get(this->m_swap_chain);
	if (this->m_fac_4.Error()) {
		_out() += this->m_fac_4.Error().Print(TError::e_print::e_req);
	}
	else
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz)this->m_swap_chain.Print(e_print::e_all));
}

/////////////////////////////////////////////////////////////////////////////

CFac_6:: CFac_6 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
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

CPxFormat:: CPxFormat (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
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
		_out()();
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

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { namespace _impl {

	class CDesc_Fmt {
	public:
		 CDesc_Fmt (void) = default; CDesc_Fmt (const CDesc_Fmt&) = delete; CDesc_Fmt (CDesc_Fmt&&) = delete;
		~CDesc_Fmt (void) =  default;
	public:
		CString Do (const TSwapDesc& _desc, const bool _b_after) {
			_desc; _b_after;
			_pc_sz pc_sz_pat = _T("swap desc value sync %s: "
				"\n\t\talpha=%d;"
				"\n\t\tbuffer=%s;"
				"\n\t\teffect=%s;"
				"\n\t\tflags=%s;"
				"\n\t\tpixels=%s;"
				"\n\t\tsample=%s;"
				"\n\t\tsize=%s;"
				"\n\t\tscale=%d;stereo=%s");

			CString cs_out = TStringEx().Format(pc_sz_pat, _b_after ? _T("after") :_T("before"),
				_desc.Alpha().Get(),
				(_pc_sz)_desc.Buffer().Print(e_print::e_req),
				(_pc_sz)_desc.Effect().Print(e_print::e_req), TStringEx().Dword(_desc.Flags()),
				(_pc_sz)_desc.Pixels().Print(e_print::e_req),
				(_pc_sz)_desc.Sample().Print(e_print::e_req),
				(_pc_sz)_desc.Size().Print(e_print::e_req), _desc.Scale(),
				(_pc_sz)TStringEx().Bool(_desc.Stereo())
			);

			return  cs_out;
		}
	private:
		CDesc_Fmt&  operator = (const CDesc_Fmt&) = delete;
		CDesc_Fmt&  operator = (CDesc_Fmt&&) = delete;
	};

}}}}

/////////////////////////////////////////////////////////////////////////////

CSwapDesc:: CSwapDesc (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CSwapDesc::Set (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	_out() += CDesc_Fmt().Do(this->m_desc, false);

	this->m_desc.Alpha() << TAlphaMode::e_mode::e_ignore;
	this->m_desc.Buffer().Set(3, TUsage::e_shader);

	this->m_desc.Effect().Set(TEffect::e_value::e_discard);
	this->m_desc.Flags(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE | TSwapFlag::DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY);

	this->m_desc.Pixels().Alpha() << TAlphaMode::e_unspec;
	this->m_desc.Pixels() << TClrBits::DXGI_FORMAT_UNKNOWN;

	this->m_desc.Sample().Set(1, 1);
	this->m_desc.Size().Set(555, 333);
	this->m_desc.Stereo(true);
	this->m_desc.Scale(TScale::DXGI_SCALING_ASPECT_RATIO_STRETCH);

	_out() += this->m_desc.Print(e_print::e_all);
	_out() += CDesc_Fmt().Do(this->m_desc, true);
	_out()();
}