/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr-2025 at 21:19:33.068, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX swap chain component wrapper interface implementation file;
*/
#include "direct_x.swap.h"

using namespace ex_ui::draw::direct_x;

static CSyncObject g_sync_obj;
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
#if defined(_DEBUG)

	CString _buffer_usage_to_str (const /*CBuff_Usage::e_usage*/uint32_t _e_value) {
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

	CString _effect_to_str (const /*CEffect::e_value*/uint32_t _e_value) {
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

#endif
}}}}
using namespace ex_ui::draw::direct_x::_impl;

#define Safe_Lock_This() Safe_Lock(g_sync_obj)
/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString CBuff_Usage::Print(const uint32_t _n_usage) {
	return _buffer_usage_to_str(_n_usage);
}
#endif
/////////////////////////////////////////////////////////////////////////////

CBuffer:: CBuffer (IBuffer_Sync* const _p_sync) : CBuffer() { *this << _p_sync; }
CBuffer:: CBuffer (const uint32_t _n_count, const uint32_t _n_usage) : m_p_sync(0), m_count(_n_count), m_usage(_n_usage) {}
CBuffer:: CBuffer (const CBuffer& _src) : CBuffer() { *this = _src; }
CBuffer::~CBuffer (void) {}

/////////////////////////////////////////////////////////////////////////////

uint32_t  CBuffer::Count (void) const { return this->m_count; }
bool      CBuffer::Count (const uint32_t _n_value) {
	const bool b_changed = (this->Count() != _n_value);
	if (b_changed) {
		this->m_count = _n_value;
	}
	Safe_Lock_This();
	if (this->m_p_sync) // must be updated always due to sync value may to be different in comparison with this class object field;
		this->m_p_sync->IBuffer_OnCount(_n_value);

	return b_changed;
}

uint32_t  CBuffer::Usage (void) const { return this->m_usage; }
bool      CBuffer::Usage (const uint32_t _n_value) {
	const bool b_changed = (this->Usage() != _n_value);
	if (b_changed) {
		this->m_usage = _n_value;
	}
	Safe_Lock_This();
	if (this->m_p_sync) // must be updated always due to sync value may to be different in comparison with this class object field;
		this->m_p_sync->IBuffer_OnUsage(_n_value);
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
err_code  CBuffer::Sync (IBuffer_Sync* const _p_sync) {
	Safe_Lock_This();
	this->m_p_sync = _p_sync;
	return __s_ok;
}

/////////////////////////////////////////////////////////////////////////////

CBuffer&  CBuffer::operator = (const CBuffer& _src) { *this << _src.Count() >> _src.Usage(); return *this; }
CBuffer&  CBuffer::operator <<(const uint32_t _n_count) { this->Count(_n_count); return *this; }
CBuffer&  CBuffer::operator >>(const uint32_t _n_usage) { this->Usage(_n_usage); return *this; }

CBuffer&  CBuffer::operator <<(IBuffer_Sync* const _p_desc) { this->Sync(_p_desc); return *this; }

/////////////////////////////////////////////////////////////////////////////

CEffect:: CEffect (uint32_t* const _p_sync) : m_value(e_value::e_flp_disc), m_p_sync(0) { if (_p_sync) *this << _p_sync; }
CEffect:: CEffect (const CEffect& _src) : CEffect() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

uint32_t  CEffect::Get (void) const { return this->m_value; }
bool      CEffect::Set (const uint32_t _n_value) {
	const bool b_changed = (this->Get() != _n_value);
	if (b_changed) {
		this->m_value = static_cast<e_value>(_n_value);
	}
	Safe_Lock(g_sync_obj);
	if (this->m_p_sync) // must be updated always due to sync value may to be different in comparison with this class object field;
		*this->m_p_sync = static_cast<TEffect>(_n_value);
	return b_changed;
}
#if defined(_DEBUG)
CString   CEffect::Print (const uint32_t _n_effect) {
	return _effect_to_str(_n_effect);
}
CString   CEffect::Print (const e_print _e_opt) const {
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
TEffect   CEffect::Raw (void) const { return static_cast<TEffect>(this->Get()); }

void      CEffect::Sync (uint32_t* const _p_sync) {
	Safe_Lock(g_sync_obj);
	this->m_p_sync = _p_sync;
}

/////////////////////////////////////////////////////////////////////////////

CEffect&  CEffect::operator = (const CEffect& _src) { *this << _src.Get() << _src.m_p_sync; return *this; }

CEffect&  CEffect::operator <<(const uint32_t _n_effect) { this->Set(_n_effect); return *this; }
CEffect&  CEffect::operator <<(uint32_t* const _p_sync) { this->Sync(_p_sync); return *this; }

/////////////////////////////////////////////////////////////////////////////

CSample:: CSample (ISample_Sync* const _p_sync) : CSample() { *this << _p_sync; }
CSample:: CSample (const uint32_t _n_count, const uint32_t _n_quality) : m_desc{0} { *this << _n_count >>_n_quality; }
CSample:: CSample (const CSample& _src) : CSample() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

uint32_t  CSample::Count (void) const { return this->Raw().Count; }
bool      CSample::Count (const uint32_t _n_value) {
	const bool b_changed = (this->Count() != _n_value);
	if (b_changed) {
		this->Raw().Count = _n_value;
	}
	Safe_Lock_This();
	if (this->m_p_sync) // must be updated always due to sync value may to be different in comparison with this class object field;
		this->m_p_sync->ISample_OnCount(_n_value);
	return b_changed;
}

uint32_t  CSample::Quality (void) const { return this->Raw().Quality; }
bool      CSample::Quality (const uint32_t _n_value) {
	const bool b_changed = (this->Quality() != _n_value);
	if (b_changed) {
		this->Raw().Quality = _n_value;
	}
	Safe_Lock_This();
	if (this->m_p_sync) // must be updated always due to sync value may to be different in comparison with this class object field;
		this->m_p_sync->ISample_OnQuality(_n_value);
	return b_changed;
}

bool      CSample::Is_valid (void) const {
	return !!this->Count()/* && !!this->Quality()*/;
}
#if defined(_DEBUG)
CString   CSample::Print (const TSampleDesc& _desc) {
	CString cs_out; cs_out.Format(_T("{count=%d;quality=%d}"), _desc.Count, _desc.Quality);
	return  cs_out;
}
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

err_code CSample::Sync (ISample_Sync* const _p_sync) {
	_p_sync;
	Safe_Lock_This();
	this->m_p_sync = _p_sync;
	return __s_ok;
}

/////////////////////////////////////////////////////////////////////////////

CSample&  CSample::operator = (const CSample& _src) { *this << _src.Count() >> _src.Quality(); return *this; } // instead of assigning Count() and Quality() it is just enough to set Raw();
CSample&  CSample::operator <<(const uint32_t _n_count) { this->Count(_n_count); return *this; }
CSample&  CSample::operator >>(const uint32_t _n_quality) { this->Quality(_n_quality); return *this; }

CSample&  CSample::operator <<(ISample_Sync* const _p_sync) { this->Sync(_p_sync); return *this; }
CSample::operator const TSampleDesc& (void) const { return this->Raw(); }

/////////////////////////////////////////////////////////////////////////////
#if (0)
err_code  CSample::Get_quality (const TResFormat _n_fmt, const uint32_t _n_smp_count, uint32_t& _levels) {
	_levels = 0;
	return __e_fail;
}
#endif
/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString CSwapFlags::Print (const uint32_t _n_flags) const {
	return _flags_to_str(_n_flags);
}
#endif