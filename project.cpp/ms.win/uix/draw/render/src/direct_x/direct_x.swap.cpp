/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr_2025 at 21:19:33.068, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX swap chain component wrapper interface implementation file;
*/
#include "direct_x.swap.h"

using namespace ex_ui::draw::direct_x;

static CSyncObject g_sync_obj;
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
#if defined(_DEBUG)
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

	CString _buffer_usage_to_str (const CBuff_Usage::e_usage _e_value) {
		CString cs_out;
		switch (_e_value) {
		case CBuff_Usage::e_usage::e_back    : cs_out = _T("back_buffer"); break;
		case CBuff_Usage::e_usage::e_discard : cs_out = _T("discard_int"); break;
		case CBuff_Usage::e_usage::e_read    : cs_out = _T("read_only"); break;
		case CBuff_Usage::e_usage::e_shader  : cs_out = _T("shader_input"); break;
		case CBuff_Usage::e_usage::e_shared  : cs_out = _T("shared_res"); break;
		case CBuff_Usage::e_usage::e_target  : cs_out = _T("render_out"); break;
		case CBuff_Usage::e_usage::e_unorder : cs_out = _T("unorder_access"); break;
		case CBuff_Usage::e_usage::e__unspec : cs_out = _T("#not_accept"); break;
		default:
			cs_out.Format(_T("#inv_arg=%u"), _e_value);
		}
		return  cs_out;
	}

	CString _effect_to_str (const CEffect::e_value _e_value) {
		CString cs_out;
		switch (_e_value) {
		case CEffect::e_value::e_discard : cs_out = _T("eff_discard"); break;
		case CEffect::e_value::e_sequent : cs_out = _T("eff_sequent"); break;
		case CEffect::e_value::e_flp_disc: cs_out = _T("flp_discard"); break;
		case CEffect::e_value::e_flp_seq : cs_out = _T("flp_sequent"); break;
		default:
			cs_out.Format(_T("#inv_arg=%u"), _e_value);
		}
		return  cs_out;
	}

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

	CString _flags_to_str (const uint32_t _n_flags) {
		CString cs_out;
		CString cs_seq;
		CString cs_names;

		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
			cs_names += _T("SWITCH_ALLOWED");
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING);
			cs_names += _T("TEARING_ALLOWED");
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY);
			cs_names += _T("DISPLAY_ONLY");
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER);
			cs_names += _T("FORE_LAYER");
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT);
			cs_names += _T("WAIT_OBJECT");
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO);
			cs_names += _T("FULL_SCREEN");
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE);
			cs_names += _T("GDI_COMPAT");
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED);
			cs_names += _T("HW_PROTECTED");
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_NONPREROTATED) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_NONPREROTATED);
			cs_names += _T("NONPREROTATED");
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT);
			cs_names += _T("RESTRICT_CONTENT");
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER);
			cs_names += _T("RES_DRIVER");
		}
		if (_n_flags & TSwapFlag::DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO) {
			if (cs_seq.IsEmpty() == false) {
				cs_seq += _T("|");
				cs_names += _T("|");
			}
			cs_seq += TStringEx().Dword(TSwapFlag::DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO);
			cs_names += _T("YUV_VIDEO");
		}

		if (cs_seq.IsEmpty()) {
			cs_seq = _T("0");
			cs_names = _T("#not_set");
		}
		cs_out.Format(_T("%s;%s"), (_pc_sz) cs_seq, (_pc_sz) cs_names);
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
#if (0)
CAlphaMode:: CAlphaMode (uint32_t* const _p_sync) : m_n_mode(e_mode::e_straith), m_p_sync(0) { if (_p_sync) *this << _p_sync; }
CAlphaMode:: CAlphaMode (const TUint32Ptr& _p_sync) : CAlphaMode() { *this << _p_sync; }
#else

#endif
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
	SAFE_LOCK(g_sync_obj);
	if (this->m_p_sync) // must be updated always due to sync value may to be different in comparison with this class object field;
		*this->m_p_sync = _n_value;
#else
	if (this->Sync())
		this->Sync()->ref() = _n_value;
#endif
	return b_changed;
}
#if (1)
void CAlphaMode::Sync (uint32_t* const _p_sync) {
	SAFE_LOCK(g_sync_obj);
	this->m_p_sync = _p_sync;
}
#else
const
TUint32Ptr&  CAlphaMode::Sync (void) const { return this->m_p_sync; }
TUint32Ptr&  CAlphaMode::Sync (void)       { return this->m_p_sync; }
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
	SAFE_LOCK(g_sync_obj);
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

CBuffer:: CBuffer (const uint32_t _n_count, const uint32_t _n_usage) : m_count(_n_count), m_usage(_n_usage) {}
CBuffer:: CBuffer (const CBuffer& _src) : CBuffer() { *this = _src; }
CBuffer:: CBuffer (const TDescWrapPtr& _p_desc) : CBuffer() { *this << _p_desc;}
CBuffer::~CBuffer (void) {}

/////////////////////////////////////////////////////////////////////////////

uint32_t  CBuffer::Count (void) const { return this->m_count; }
bool      CBuffer::Count (const uint32_t _n_value) {
	const bool b_changed = (this->Count() != _n_value);
	if (b_changed) {
		this->m_count = _n_value;
	}
	if (this->Sync()) // must be updated always due to sync value may to be different in comparison with this class object field;
		this->Sync()->ref().BufferCount = _n_value;

	return b_changed;
}

uint32_t  CBuffer::Usage (void) const { return this->m_usage; }
bool      CBuffer::Usage (const uint32_t _n_value) {
	const bool b_changed = (this->Usage() != _n_value);
	if (b_changed) {
		this->m_usage = _n_value;
	}
	if (this->Sync()) // must be updated always due to sync value may to be different in comparison with this class object field;
		this->Sync()->ref().BufferUsage = _n_value;
	return b_changed;
}

bool CBuffer::Is_valid (void) const { return (!!this->Count() && !!this->Usage()); }

bool CBuffer::Set (const uint32_t _n_count, const uint32_t _n_usage) {
	bool b_changed = false;

	if (this->Count(_n_count)) b_changed = true;
	if (this->Usage(_n_usage)) b_changed = true;

	return b_changed;
}
#if defined(_DEBUG)
CString   CBuffer::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{count=%u;usage=%d(%s);valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{count=%u;usage=%d(%s);valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{count=%u;usage=%d(%s);valid=%s}");

	CString cs_usage = _buffer_usage_to_str(static_cast<CBuff_Usage::e_usage>(this->Usage()));
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->Count(), this->Usage(), (_pc_sz)cs_usage, (_pc_sz)cs_valid); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->Count(), this->Usage(), (_pc_sz)cs_usage, (_pc_sz)cs_valid); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, this->Count(), this->Usage(), (_pc_sz)cs_usage, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
const
TDescWrapPtr& CBuffer::Sync (void) const { return this->m_p_sync; }
TDescWrapPtr& CBuffer::Sync (void)       { return this->m_p_sync; }

/////////////////////////////////////////////////////////////////////////////

CBuffer&  CBuffer::operator = (const CBuffer& _src) { *this << _src.Count() >> _src.Usage(); return *this; }
CBuffer&  CBuffer::operator <<(const uint32_t _n_count) { this->Count(_n_count); return *this; }
CBuffer&  CBuffer::operator >>(const uint32_t _n_usage) { this->Usage(_n_usage); return *this; }

CBuffer&  CBuffer::operator <<(const TDescWrapPtr& _p_desc) { this->Sync() = _p_desc; return *this; }

/////////////////////////////////////////////////////////////////////////////

CEffect:: CEffect (uint32_t* const _p_sync) : m_value(e_value::e_flp_disc), m_p_sync(0) { if (_p_sync) *this << _p_sync; }
CEffect:: CEffect (const CEffect& _src) : CEffect() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

uint32_t CEffect::Get (void) const { return this->m_value; }
bool     CEffect::Set (const uint32_t _n_value) {
	const bool b_changed = (this->Get() != _n_value);
	if (b_changed) {
		this->m_value = static_cast<e_value>(_n_value);
	}
	SAFE_LOCK(g_sync_obj);
	if (this->m_p_sync) // must be updated always due to sync value may to be different in comparison with this class object field;
		*this->m_p_sync = static_cast<TEffect>(_n_value);
	return b_changed;
}
#if defined(_DEBUG)
CString  CEffect::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{value=%u(%s)}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{value=%u(%s)}");
	static _pc_sz pc_sz_pat_r = _T("{value=%u(%s)}");

	CString cs_value = _effect_to_str(static_cast<CEffect::e_value>(this->Get()));

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->Get(), (_pc_sz)cs_value); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->Get(), (_pc_sz)cs_value); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, this->Get(), (_pc_sz)cs_value); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
TEffect CEffect::Raw (void) const { return static_cast<TEffect>(this->Get()); }

void    CEffect::Sync (uint32_t* const _p_sync) {
	SAFE_LOCK(g_sync_obj);
	this->m_p_sync = _p_sync;
}

/////////////////////////////////////////////////////////////////////////////

CEffect&  CEffect::operator = (const CEffect& _src) { *this << _src.Get() << _src.m_p_sync; return *this; }

CEffect&  CEffect::operator <<(const uint32_t _n_effect) { this->Set(_n_effect); return *this; }
CEffect&  CEffect::operator <<(uint32_t* const _p_sync) { this->Sync(_p_sync); return *this; }

/////////////////////////////////////////////////////////////////////////////

CPxFormat:: CPxFormat (const uint32_t _n_format) : m_clr_bits(static_cast<TClrBits>(_n_format)){}
CPxFormat:: CPxFormat (const CPxFormat& _src) : CPxFormat() { *this = _src; }
CPxFormat:: CPxFormat (const TDescWrapPtr& _p_desc) : CPxFormat() { *this << _p_desc; }

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

CPxFormat&  CPxFormat::operator <<(const TDescWrapPtr& _p_desc) {
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

CSample:: CSample (const uint32_t _n_count, const uint32_t _n_quality) : m_desc{0} { *this << _n_count >>_n_quality; }
CSample:: CSample (const CSample& _src) : CSample() { *this = _src; }
CSample:: CSample (const TDescWrapPtr& _p_desc) : CSample() { *this << _p_desc; }

/////////////////////////////////////////////////////////////////////////////

uint32_t  CSample::Count (void) const { return this->Raw().Count; }
bool      CSample::Count (const uint32_t _n_value) {
	const bool b_changed = (this->Count() != _n_value);
	if (b_changed) {
		this->Raw().Count = _n_value;
	}
	if (this->Sync()) // must be updated always due to sync value may to be different in comparison with this class object field;
		this->Sync()->ref().SampleDesc.Count = _n_value;
	return b_changed;
}
uint32_t  CSample::Quality (void) const { return this->Raw().Quality; }
bool      CSample::Quality (const uint32_t _n_value) {
	const bool b_changed = (this->Quality() != _n_value);
	if (b_changed) {
		this->Raw().Quality = _n_value;
	}
	if (this->Sync()) // must be updated always due to sync value may to be different in comparison with this class object field;
		this->Sync()->ref().SampleDesc.Quality = _n_value;
	return b_changed;
}

bool      CSample::Is_valid (void) const {
	return !!this->Count()/* && !!this->Quality()*/;
}
#if defined(_DEBUG)
CString   CSample::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{count=%d;quality=%d;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{count=%d;quality=%d;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{count=%d;quality=%d;valid=%s}");

	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->Count(), this->Quality(), (_pc_sz)cs_valid); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->Count(), this->Quality(), (_pc_sz)cs_valid); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, this->Count(), this->Quality(), (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
bool CSample::Set (const uint32_t _n_count, const uint32_t _n_quality) {
	bool b_changed = false;

	if (this->Count(_n_count)) b_changed = true;
	if (this->Quality(_n_quality)) b_changed = true;

	return b_changed;
}

const
TSampleDesc& CSample::Raw (void) const { return this->m_desc; }
TSampleDesc& CSample::Raw (void)       { return this->m_desc; }

const
TDescWrapPtr& CSample::Sync (void) const { return this->m_p_sync; }
TDescWrapPtr& CSample::Sync (void)       { return this->m_p_sync; }

/////////////////////////////////////////////////////////////////////////////

CSample&  CSample::operator = (const CSample& _src) { *this << _src.Count() >> _src.Quality() << _src.Sync(); return *this; } // instead of assigning Count() and Quality() it is just enough to set Raw();
CSample&  CSample::operator <<(const uint32_t _n_count) { this->Count(_n_count); return *this; }
CSample&  CSample::operator >>(const uint32_t _n_quality) { this->Quality(_n_quality); return *this; }

CSample&  CSample::operator <<(const TDescWrapPtr& _p_sync) { this->Sync() = _p_sync; return *this; }
CSample::operator const TSampleDesc& (void) const { return this->Raw(); }

/////////////////////////////////////////////////////////////////////////////
#if (0)
err_code  CSample::Get_quality (const TResFormat _n_fmt, const uint32_t _n_smp_count, uint32_t& _levels) {
	_levels = 0;
	return __e_fail;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CSize:: CSize (void) : m_size{0} {}
CSize:: CSize (const CSize& _src) : CSize() { *this = _src; }
CSize:: CSize (const TDescWrapPtr& _p_sync) : CSize() { *this << _p_sync; }

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

CSwapDesc:: CSwapDesc (void) : m_p_desc(new CDesc_Wrap()) {
	if (this->m_p_desc) {
		this->Alpha().Sync((uint32_t* const)&this->m_p_desc->ref().AlphaMode);
		this->Buffer().Sync() = this->m_p_desc;
		this->Effect().Sync((uint32_t* const)&this->m_p_desc->ref().SwapEffect);
	//	this->Pixels().Sync() = this->m_p_desc; // does not set alpha synch pointer;
		this->Pixels() << this->m_p_desc;
		this->Sample() << this->m_p_desc;
		this->Size()   << this->m_p_desc;
	}
}
CSwapDesc:: CSwapDesc (const CSwapDesc& _src) : CSwapDesc() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////
const
TAlpha&     CSwapDesc::Alpha (void) const { return this->m_alpha; }
TAlpha&     CSwapDesc::Alpha (void)       { return this->m_alpha; }
const
CBuffer&    CSwapDesc::Buffer(void) const { return this->m_buffer; }
CBuffer&    CSwapDesc::Buffer(void)       { return this->m_buffer; }
const
CEffect&    CSwapDesc::Effect(void) const { return this->m_effect; }
CEffect&    CSwapDesc::Effect(void)       { return this->m_effect; }

uint32_t    CSwapDesc::Flags (void) const { return (this->m_p_desc ? this->m_p_desc->ref().Flags : 0); }
bool        CSwapDesc::Flags (const uint32_t _n_flags) {
	const bool b_changed = (this->Flags() != _n_flags);

	if (this->m_p_desc && b_changed) {
		this->m_p_desc->ref().Flags = _n_flags;
	}
	return b_changed;
}
const
CPxFormat&  CSwapDesc::Pixels(void) const { return this->m_pixels; }
CPxFormat&  CSwapDesc::Pixels(void)       { return this->m_pixels; }

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
	CString cs_flags = _flags_to_str(this->Flags());
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
CSample&    CSwapDesc::Sample (void) const { return this->m_sample; }
CSample&    CSwapDesc::Sample (void)       { return this->m_sample; }

TScale      CSwapDesc::Scale (void) const  { return (this->m_p_desc ? this->m_p_desc->ref().Scaling : TScale::DXGI_SCALING_NONE); }
bool        CSwapDesc::Scale (const TScale _n_scale) {
	const bool b_changed = (this->Scale() != _n_scale);

	if (this->m_p_desc && b_changed)
		this->m_p_desc->ref().Scaling = _n_scale;

	return b_changed;
}
const
CSize&      CSwapDesc::Size (void) const { return this->m_size; }
CSize&      CSwapDesc::Size (void)       { return this->m_size; }

bool  CSwapDesc::Stereo (void) const { return (this->m_p_desc ? this->m_p_desc->ref().Stereo : 0); }
bool  CSwapDesc::Stereo (const bool _b_value) {
	const bool b_changed = (this->Stereo() != _b_value);
	if (this->m_p_desc && b_changed)
		this->m_p_desc->ref().Stereo = _b_value;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CSwapDesc&  CSwapDesc::operator = (const CSwapDesc& _src) { _src; return *this; }
CSwapDesc&  CSwapDesc::operator <<(const TSwapDesc& _desc) { _desc; return *this; }

#if (0)
/////////////////////////////////////////////////////////////////////////////

CSwapChain:: CSwapChain (void) : m_target(nullptr) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CSwapChain:: CSwapChain (const CSwapChain& _src) : CSwapChain() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

TError&  CSwapChain::Error (void) const { return this->m_error; }
bool     CSwapChain::Is_valid (void) const { return (nullptr != this->Ptr()); }
const
TChainPtr& CSwapChain::Ptr (void) const { return this->m_p_chain; }
TChainPtr& CSwapChain::Ptr (void)       { return this->m_p_chain; }

const
CCmdQueue& CSwapChain::Queue (void) const { return this->m_queue; }
CCmdQueue& CSwapChain::Queue (void)       { return this->m_queue; }

HWND CSwapChain::Target (void) const { return this->m_target; }
bool CSwapChain::Target (const HWND _h_target) {
	if (nullptr == _h_target || !::IsWindow(_h_target))
		return false;
	this->m_target = _h_target;
	return true;
}

/////////////////////////////////////////////////////////////////////////////

CSwapChain&  CSwapChain::operator = (const CSwapChain& _src) { *this << _src.Ptr(); return *this; }
CSwapChain&  CSwapChain::operator <<(const TChainPtr& _p_chain) { this->Ptr() = _p_chain; return *this; }

#endif