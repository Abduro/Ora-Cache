/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Apr-2025 at 17:05:05.447, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX 12 swap chain wrapper interface implementation file;
*/
#include "direct_x.swap.2.h"

using namespace ex_ui::draw::direct_x::_12;

static CSyncObject g_sync_obj;
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
#if defined(_DEBUG)
	using CAlphaMode = ex_ui::draw::direct_x::_12::CAlphaMode;

	CString _alpha_mode_to_str (const uint32_t _e_value) {
		CString cs_out;
		switch (_e_value) {
		case CAlphaMode::e_mode::e_ignore  : cs_out = _T("e_ignore"); break;
		case CAlphaMode::e_mode::e_premulti: cs_out = _T("premultiplied"); break;
		case CAlphaMode::e_mode::e_straith : cs_out = _T("straith"); break;
		case CAlphaMode::e_mode::e_unspec  : cs_out = _T("unspecified"); break;
		default:
			cs_out.Format(_T("#inv_arg=%u"), _e_value);
		}
		return  cs_out;
	}

	using CPxFormat = ex_ui::draw::direct_x::_12::CPxFormat;

	CString _clr_bits_to_str (const CPxFormat::e_clr_bits _e_value) {
		CString cs_out;
		switch (_e_value) {
		case CPxFormat::e_clr_bits::e__unknown : cs_out = _T("bits_unknown"); break;
		case CPxFormat::e_clr_bits::e_rgba_norm: cs_out = _T("b8g8r8a8_unorm"); break;
		default:
			cs_out.Format(_T("#no_desc=%u"), _e_value);
		}
		return  cs_out;
	}

	CString _scale_to_str (const TScale _e_value) {
		CString cs_out;
		switch (_e_value) {
		case TScale::DXGI_SCALING_ASPECT_RATIO_STRETCH: cs_out = _T("ratio"); break;
		case TScale::DXGI_SCALING_NONE   : cs_out = _T("none"); break;
		case TScale::DXGI_SCALING_STRETCH: cs_out = _T("stretch"); break;
		default:
			cs_out.Format(_T("#no_desc=%u"), _e_value);
		}
		return  cs_out;
	}
#endif
}}}}
using namespace ex_ui::draw::direct_x::_impl;

/////////////////////////////////////////////////////////////////////////////

CAlphaMode:: CAlphaMode (const uint32_t _n_mode) : m_n_mode(_n_mode), m_p_sync(0) {}
CAlphaMode:: CAlphaMode (const CAlphaMode& _src) : CAlphaMode() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

uint32_t  CAlphaMode::Get (void) const { return this->m_n_mode; }
bool      CAlphaMode::Set (const uint32_t _n_value) {
	const bool b_changed = (this->Get() != _n_value);
	if (b_changed) {
		this->m_n_mode = _n_value;
	}
#if (1)
	Safe_Lock(g_sync_obj);
	if (this->m_p_sync) // must be updated always due to sync value may to be different in comparison with this class object field;
		*this->m_p_sync = _n_value;
#else
	if (this->Sync())
		this->Sync()->ref() = _n_value;
#endif
	return b_changed;
}

#if (1)
void      CAlphaMode::Sync (uint32_t* const _p_sync) {
	Safe_Lock(g_sync_obj);
	this->m_p_sync = _p_sync;
}
#else
const
TUint32Ptr&  CAlphaMode::Sync (void) const { return this->m_p_sync; }
TUint32Ptr&  CAlphaMode::Sync (void) { return this->m_p_sync; }
#endif

#if defined(_DEBUG)
CString   CAlphaMode::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{mode=%d(%s)}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{mode=%d(%s)}");
	static _pc_sz pc_sz_pat_r = _T("{mode=%d(%s)}");

	CString cs_mode = _alpha_mode_to_str(this->Get());
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->Get(), (_pc_sz) cs_mode); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->Get(), (_pc_sz) cs_mode); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, this->Get(), (_pc_sz) cs_mode); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

using e_mode = CAlphaMode::e_mode;

TAlphaMode   CAlphaMode::Raw (void) const { return static_cast<TAlphaMode>(this->Get()); }

/////////////////////////////////////////////////////////////////////////////

CAlphaMode&  CAlphaMode::operator = (const CAlphaMode& _src) { *this << _src.Get()/* << _src.Sync()*/; return *this; }
CAlphaMode&  CAlphaMode::operator <<(uint32_t _n_mode) { this->Set(_n_mode); return *this; }
#if (1)
CAlphaMode&  CAlphaMode::operator <<(uint32_t* const _p_sync) {
	this->Sync(_p_sync);
	Safe_Lock(g_sync_obj);
	if (this->m_p_sync) {
		*this->m_p_sync = this->Get();
	}
	return *this;
}
#else
CAlphaMode&  CAlphaMode::operator <<(const TUint32Ptr& _p_sync) {
	this->Sync() = _p_sync;
	if (this->Sync())
		this->Sync()->ref() = this->Get(); // updates the synch value;
	return *this;
}
#endif
CAlphaMode::operator TAlphaMode (void) const { return static_cast<TAlphaMode>(this->Get()); }

/////////////////////////////////////////////////////////////////////////////

CPxFormat:: CPxFormat (const uint32_t _n_format) : m_clr_bits(static_cast<TClrBits>(_n_format)){}
CPxFormat:: CPxFormat (const CPxFormat& _src) : CPxFormat() { *this = _src; }
CPxFormat:: CPxFormat (const _12::TDescWrapPtr& _p_desc) : CPxFormat() { *this << _p_desc; }

/////////////////////////////////////////////////////////////////////////////
const
CAlphaMode& CPxFormat::Alpha (void) const { return this->m_alpha; }
CAlphaMode& CPxFormat::Alpha (void)       { return this->m_alpha; }

uint32_t    CPxFormat::Bits  (void) const { return this->m_clr_bits; }
bool        CPxFormat::Bits  (const TClrBits _n_value) {
	const bool b_changed = (this->Bits() != static_cast<uint32_t>(_n_value));
	if (b_changed) {
		this->m_clr_bits = _n_value;
	}
	if (this->Sync()) // must be updated always due to sync value may to be different in comparison with this class object field;
		this->Sync()->ref().Format = _n_value;
	return b_changed;
}

bool        CPxFormat::Is_valid (void) const { return (!!this->Bits() && !!this->Alpha()); }
#if defined(_DEBUG)
CString     CPxFormat::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{px_bits=%d(%s);alpha=%d(%s);valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{px_bits=%d(%s);alpha=%d(%s);valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{px_bits=%d(%s);alpha=%d(%s);valid=%s}");

	CString cs_alpha = this->Alpha().Print(e_print::e_req);
	CString cs_bits  = _clr_bits_to_str(static_cast<CPxFormat::e_clr_bits>(this->Bits()));
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a,
		(_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->Bits(), (_pc_sz)cs_bits, this->Alpha().Get(), (_pc_sz)cs_alpha, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n,
		(_pc_sz)__CLASS__, this->Bits(), (_pc_sz)cs_bits, this->Alpha().Get(), (_pc_sz)cs_alpha, (_pc_sz)cs_valid);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r,
		this->Bits(), (_pc_sz)cs_bits, this->Alpha().Get(), (_pc_sz)cs_alpha, (_pc_sz)cs_valid);
	}

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
TPxFormat   CPxFormat::Raw (void) const {
	TPxFormat raw_ = { (TClrBits) this->Bits(), (TAlphaMode_2) this->Alpha().Get() };
	return raw_;
}
const
TDescWrapPtr& CPxFormat::Sync (void) const { return this->m_desc; }
TDescWrapPtr& CPxFormat::Sync (void)       { return this->m_desc; }

/////////////////////////////////////////////////////////////////////////////

CPxFormat&  CPxFormat::operator = (const CPxFormat& _src) { *this << _src.Alpha() << (TClrBits)_src.Bits() << _src.Sync(); return *this; }
CPxFormat&  CPxFormat::operator <<(const CAlphaMode& _alpha) { this->Alpha() = _alpha; return *this; }
CPxFormat&  CPxFormat::operator <<(const TClrBits _value) { this->Bits(_value); return *this; }

CPxFormat&  CPxFormat::operator <<(const _12::TDescWrapPtr& _p_desc) {
	this->Sync() = _p_desc;
#if (1)
	if (_p_desc)
		this->Alpha().Sync((uint32_t*)&_p_desc->ref().AlphaMode);
	else
		this->Alpha().Sync(nullptr);
#else
#endif
	return *this;
}

CPxFormat::operator TPxFormat (void) const { return this->Raw(); }

/////////////////////////////////////////////////////////////////////////////

CSize:: CSize (void) : m_size{0} {}
CSize:: CSize (const CSize& _src) : CSize() { *this = _src; }
CSize:: CSize (const _12::TDescWrapPtr& _p_sync) : CSize() { *this << _p_sync; }

/////////////////////////////////////////////////////////////////////////////

uint32_t CSize::Height (void) const { return this->H(); }
bool     CSize::Height (const uint32_t _n_value) { return this->H(_n_value); }

uint32_t CSize::H (void) const { return this->Raw().height; }
bool     CSize::H (const uint32_t _n_value) {
	const bool b_changed = (this->H() != _n_value);
	if (b_changed) {
		this->Raw().height = _n_value;
	}
	if (this->Sync()) // must be updated always due to sync value may to be different in comparison with this class object field;
		this->Sync()->ref().Height = _n_value;
	return b_changed;
}

#if defined(_DEBUG)
CString  CSize::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{height=%dpx;width=%dpx}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{height=%dpx;width=%dpx}");
	static _pc_sz pc_sz_pat_r = _T("{height=%dpx;width=%dpx}");

	CString cs_out;
	if (e_print::e_all == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->H(), this->W()); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->H(), this->W()); }
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, this->H(), this->W()); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

uint32_t CSize::Width (void) const { return this->W(); }
bool     CSize::Width (const uint32_t _n_value) { return this->W(_n_value); }

uint32_t CSize::W (void) const { return this->Raw().width; }
bool     CSize::W (const uint32_t _n_value) {
	const bool b_changed = (this->W() != _n_value);
	if (b_changed) {
		this->Raw().width = _n_value;
	}
	if (this->Sync()) // must be updated always due to sync value may to be different in comparison with this class object field;
		this->Sync()->ref().Width = _n_value;
	return b_changed;
}

bool     CSize::Set (const uint32_t _n_width, const uint32_t _n_height) {
	bool b_changed = false;
	if (this->H(_n_height)) b_changed = true;
	if (this->W(_n_width)) b_changed = true;
	return b_changed;
}

const
TSize_U& CSize::Raw (void) const { return this->m_size; }
TSize_U& CSize::Raw (void)       { return this->m_size; }

const
TDescWrapPtr& CSize::Sync (void) const { return this->m_p_sync; }
TDescWrapPtr& CSize::Sync (void)       { return this->m_p_sync; }

/////////////////////////////////////////////////////////////////////////////

CSize&  CSize::operator = (const CSize& _src) { *this << _src.Raw() << _src.Sync(); return *this; }
CSize&  CSize::operator <<(const uint32_t _n_width) { this->W(_n_width); return *this; }
CSize&  CSize::operator >>(const uint32_t _n_height) { this->H(_n_height); return *this; }

CSize&  CSize::operator <<(const TSize_U& _size) { this->Raw() = _size; return *this; }
CSize&  CSize::operator <<(const TDescWrapPtr& _p_sync) { this->Sync() = _p_sync; return *this; }

/////////////////////////////////////////////////////////////////////////////

CSwapDesc:: CSwapDesc (void) : m_p_desc(new _12::CDesc_Wrap()), m_buffer(this), m_sample(this) {
	if (this->m_p_desc) {
		this->Alpha().Sync((uint32_t* const)&this->m_p_desc->ref().AlphaMode);
		this->Effect().Sync((uint32_t* const)&this->m_p_desc->ref().SwapEffect);
		this->Pixels() << this->m_p_desc;
		this->Size()   << this->m_p_desc;
	}
}
CSwapDesc:: CSwapDesc (const CSwapDesc& _src) : CSwapDesc() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

bool CSwapDesc::IBuffer_OnCount (const uint32_t _n_value) {
	_n_value;
	if (nullptr == this->m_p_desc)
		return false;

	const
	bool b_changed = (this->m_p_desc->ref().BufferCount != _n_value);
	if (b_changed)
		this->m_p_desc->ref().BufferCount = _n_value;

	return b_changed;
}

bool CSwapDesc::IBuffer_OnUsage (const uint32_t _n_value) {
	_n_value;
	if (nullptr == this->m_p_desc)
		return false;

	const
	bool b_changed = (this->m_p_desc->ref().BufferUsage != _n_value);
	if (b_changed)
		this->m_p_desc->ref().BufferUsage = _n_value;

	return b_changed;
}

bool CSwapDesc::ISample_OnCount (const uint32_t _n_value) {
	_n_value;
	if (nullptr == this->m_p_desc)
		return false;

	const
	bool b_changed = (this->m_p_desc->ref().SampleDesc.Count != _n_value);
	if (b_changed)
		this->m_p_desc->ref().SampleDesc.Count = _n_value;

	return b_changed;
}

bool CSwapDesc::ISample_OnQuality (const uint32_t _n_value) {
	_n_value;
	if (nullptr == this->m_p_desc)
		return false;

	const
	bool b_changed = (this->m_p_desc->ref().SampleDesc.Quality != _n_value);
	if (b_changed)
		this->m_p_desc->ref().SampleDesc.Quality = _n_value;

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////
const
TAlpha&  CSwapDesc::Alpha (void) const { return this->m_alpha; }
TAlpha&  CSwapDesc::Alpha (void)       { return this->m_alpha; }
const
CBuffer& CSwapDesc::Buffer(void) const { return this->m_buffer; }
CBuffer& CSwapDesc::Buffer(void)       { return this->m_buffer; }
const
CEffect& CSwapDesc::Effect(void) const { return this->m_effect; }
CEffect& CSwapDesc::Effect(void)       { return this->m_effect; }

uint32_t CSwapDesc::Flags (void) const { return (this->m_p_desc ? this->m_p_desc->ref().Flags : 0); }
bool     CSwapDesc::Flags (const uint32_t _n_flags) {
	_n_flags;
	const bool b_changed = (this->Flags() != _n_flags);

	if (this->m_p_desc && b_changed) {
		this->m_p_desc->ref().Flags = _n_flags;
	}
	return b_changed;
}

const
CPxFormat&  CSwapDesc::Pixels(void) const { return this->m_pixels; }
CPxFormat&  CSwapDesc::Pixels(void)       { return this->m_pixels; }

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString     CSwapDesc::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{"
		"%s%salpha=%s;"
		"%s%sbuffer=%s;"
		"%s%seffect=%s;"
		"%s%sflags=%s;"
		"%s%spixels=%s;"
		"%s%ssample=%s;"
		"%s%ssize=%s;"
		"%s%sscale=%s;stereo=%s}"
	);
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{"
		"%s%salpha=%s;"
		"%s%sbuffer=%s;"
		"%s%seffect=%s;"
		"%s%sflags=%s;"
		"%s%spixels=%s;"
		"%s%ssample=%s;"
		"%s%ssize=%s;"
		"%s%sscale=%s;stereo=%s}"
	);
	static _pc_sz pc_sz_pat_r = _T("{alpha=%s;buffer=%s;effect=%s;flags=%s;pixels=%s;sample=%s;scale=%s;size=%s;stereo=%s}");

	CString cs_alpha  = this->Alpha().Print(e_print::e_req);
	CString cs_buffer = this->Buffer().Print(e_print::e_req);
	CString cs_effect = this->Effect().Print(e_print::e_req);
	CString cs_flags  = CSwapFlags().Print(this->Flags());
	CString cs_pixels = this->Pixels().Print(e_print::e_req);
	CString cs_sample = this->Sample().Print(e_print::e_req);
	CString cs_size   = this->Size().Print(e_print::e_req);
	CString cs_stereo = TStringEx().Bool(this->Stereo());
	CString cs_scale  = TStringEx().Format(_T("%d(%s)"), this->Scale(), (_pc_sz)_scale_to_str(this->Scale()));
	CString cs_out;

	if (e_print::e_all == _e_opt) { cs_out.Format(pc_sz_pat_a,
		(_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz)cs_alpha ,
		_p_sfx, _p_pfx, (_pc_sz)cs_buffer,
		_p_sfx, _p_pfx, (_pc_sz)cs_effect,
		_p_sfx, _p_pfx, (_pc_sz)cs_flags ,
		_p_sfx, _p_pfx, (_pc_sz)cs_pixels,
		_p_sfx, _p_pfx, (_pc_sz)cs_sample,
		_p_sfx, _p_pfx, (_pc_sz)cs_size  ,
		_p_sfx, _p_pfx, (_pc_sz)cs_scale , (_pc_sz)cs_stereo);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n,
		(_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz)cs_alpha ,
		_p_sfx, _p_pfx, (_pc_sz)cs_buffer,
		_p_sfx, _p_pfx, (_pc_sz)cs_effect,
		_p_sfx, _p_pfx, (_pc_sz)cs_flags ,
		_p_sfx, _p_pfx, (_pc_sz)cs_pixels,
		_p_sfx, _p_pfx, (_pc_sz)cs_sample,
		_p_sfx, _p_pfx, (_pc_sz)cs_size  ,
		_p_sfx, _p_pfx, (_pc_sz)cs_scale , (_pc_sz)cs_stereo);
	}
	if (e_print::e_req == _e_opt) {
		cs_out.Format(pc_sz_pat_r,
			(_pc_sz)cs_alpha, (_pc_sz)cs_buffer, (_pc_sz)cs_effect, (_pc_sz)cs_flags, (_pc_sz)cs_pixels, (_pc_sz)cs_sample, (_pc_sz)cs_scale,
			(_pc_sz)cs_size , (_pc_sz)cs_stereo);
	}

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
const
TSwapDesc&  CSwapDesc::Raw (void) const {
	if (nullptr == this->m_p_desc) {
		static TSwapDesc inv_desc{0};
		return inv_desc;
	}
	else
		return this->m_p_desc->ref();
}

TSwapDesc&  CSwapDesc::Raw (void)  {
	if (nullptr == this->m_p_desc) {
		static TSwapDesc inv_desc{0};
		return inv_desc;
	}
	else
		return this->m_p_desc->ref();
}

const
CSample& CSwapDesc::Sample (void) const { return this->m_sample; }
CSample& CSwapDesc::Sample (void)       { return this->m_sample; }

TScale   CSwapDesc::Scale (void) const  { return (this->m_p_desc ? this->m_p_desc->ref().Scaling : TScale::DXGI_SCALING_NONE); }
bool     CSwapDesc::Scale (const TScale _n_scale) {
	const bool b_changed = (this->Scale() != _n_scale);

	if (this->m_p_desc && b_changed)
		this->m_p_desc->ref().Scaling = _n_scale;

	return b_changed;
}

const
CSize&   CSwapDesc::Size (void) const { return this->m_size; }
CSize&   CSwapDesc::Size (void) { return this->m_size; }

bool  CSwapDesc::Stereo (void) const { return (this->m_p_desc ? this->m_p_desc->ref().Stereo : 0); }
bool  CSwapDesc::Stereo (const bool _b_value) {
	_b_value;
	const bool b_changed = (this->Stereo() != _b_value);
	if (this->m_p_desc && b_changed)
		this->m_p_desc->ref().Stereo = _b_value;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CSwapDesc&  CSwapDesc::operator = (const CSwapDesc& _src ) { _src; return *this; }
CSwapDesc&  CSwapDesc::operator <<(const TSwapDesc& _desc) { _desc; return *this; }

/////////////////////////////////////////////////////////////////////////////

CSwapChain:: CSwapChain (void) : m_target(nullptr) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CSwapChain:: CSwapChain (const CSwapChain& _src) : CSwapChain() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////
const
CSwapDesc&   CSwapChain::Desc (void) const { return this->m_desc; }
CSwapDesc&   CSwapChain::Desc (void)       { return this->m_desc; }

TError&      CSwapChain::Error (void) const { return this->m_error; }
bool         CSwapChain::Is_valid (void) const { return (nullptr != this->Ptr()); }
const
TChainPtr&   CSwapChain::Ptr (void) const { return this->m_p_chain; }
TChainPtr&   CSwapChain::Ptr (void)       { return this->m_p_chain; }

const
CCmdQueue&   CSwapChain::Queue (void) const { return this->m_queue; }
CCmdQueue&   CSwapChain::Queue (void)       { return this->m_queue; }

HWND CSwapChain::Target (void) const { return this->m_target; }
bool CSwapChain::Target (const HWND _h_target) {
	_h_target;
	if (nullptr == _h_target || !::IsWindow(_h_target))
		return false;
	this->m_target = _h_target;
	return true;
}

/////////////////////////////////////////////////////////////////////////////

CSwapChain&  CSwapChain::operator = (const CSwapChain& _src) { *this << _src.Ptr(); return *this; }
CSwapChain&  CSwapChain::operator <<(const TChainPtr& _p_chain) { this->Ptr() = _p_chain; return *this; }