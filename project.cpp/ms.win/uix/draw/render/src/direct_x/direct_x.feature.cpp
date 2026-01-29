/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Apr-2025 at 19:48:31.943, UTC+4, Batumi, Thursday;
	This is Ebo pack DirectX data feature support interface implementation file;
*/
#include "direct_x.feature.h"

using namespace ex_ui::draw::direct_x;

using CDefault = CFeature_Lvl::CDefault;
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
	static D3D_FEATURE_LEVEL levels[] = {
	       D3D_FEATURE_LEVEL_11_1,
	       D3D_FEATURE_LEVEL_11_0,
	       D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
	       D3D_FEATURE_LEVEL_9_3 , D3D_FEATURE_LEVEL_9_2 , D3D_FEATURE_LEVEL_9_1,
	};
}}}}
using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////

uint32_t CDefault::Count (void) const { return _countof(levels); }
EFeatureLvl* const CDefault::Levels (void) const {
	return levels;
}

/////////////////////////////////////////////////////////////////////////////
const
CDefault& CFeature_Lvl::Default (void) const { return this->m_def_set; }
CString   CFeature_Lvl::Print (const uint32_t _n_level) const {
	_n_level;
	static _pc_sz pc_sz_pat = _T("%d(%s)");

	CString cs_out;
	switch (_n_level) {
	case EFeatureLvl::D3D_FEATURE_LEVEL_10_0    : cs_out.Format(pc_sz_pat, _n_level, _T("level_10_0")); break;
	case EFeatureLvl::D3D_FEATURE_LEVEL_10_1    : cs_out.Format(pc_sz_pat, _n_level, _T("level_10_1")); break;
	case EFeatureLvl::D3D_FEATURE_LEVEL_11_0    : cs_out.Format(pc_sz_pat, _n_level, _T("level_11_0")); break;
	case EFeatureLvl::D3D_FEATURE_LEVEL_11_1    : cs_out.Format(pc_sz_pat, _n_level, _T("level_11_1")); break;
	case EFeatureLvl::D3D_FEATURE_LEVEL_12_0    : cs_out.Format(pc_sz_pat, _n_level, _T("level_12_0")); break;
	case EFeatureLvl::D3D_FEATURE_LEVEL_12_1    : cs_out.Format(pc_sz_pat, _n_level, _T("level_12_1")); break;
	case EFeatureLvl::D3D_FEATURE_LEVEL_1_0_CORE: cs_out.Format(pc_sz_pat, _n_level, _T("level_core")); break;
	case EFeatureLvl::D3D_FEATURE_LEVEL_9_1     : cs_out.Format(pc_sz_pat, _n_level, _T("level_09_1")); break;
	case EFeatureLvl::D3D_FEATURE_LEVEL_9_2     : cs_out.Format(pc_sz_pat, _n_level, _T("level_09_2")); break;
	case EFeatureLvl::D3D_FEATURE_LEVEL_9_3     : cs_out.Format(pc_sz_pat, _n_level, _T("level_09_3")); break;
	default:
		cs_out.Format(pc_sz_pat, _n_level, _T("#unknown"));
	}
	return  cs_out;
}

/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {

CFeature:: CFeature (void) : m_p_data(nullptr), m_size (0), m_type(EFeature::D3D11_FEATURE_THREADING) {}
#if (0)
CFeature:: CFeature (const CFeature& _src) : CFeature() { *this = _src; }
#endif
/////////////////////////////////////////////////////////////////////////////

err_code   CFeature::Clear (void) {
	err_code n_result = __s_ok;

	if (false == this->Is_valid())
		return (n_result = TErrCodes::eData::eInvalid);
	try {
		::memset(this->Data(), 0, this->Size());
	}
	catch (...) {
		n_result = TErrCodes::eAccess::eDenied;
	}
	return n_result;
}
const
void* const CFeature::Data (void) const { return this->m_p_data; }
void* const CFeature::Data (void)       { return this->m_p_data; }

bool  CFeature::Is_valid (void) const { return (nullptr != this->Data() && !!this->Size()); }

uint32_t  CFeature::Size (void) const { return this->m_size; }
bool      CFeature::Size (const uint32_t _n_size) {
	const bool b_changed = (this->Size() != _n_size);
	if (b_changed)
		this->m_size = _n_size;
	return b_changed;
}

EFeature  CFeature::Type (void) const { return this->m_type; }
bool      CFeature::Type (const EFeature _e_type) {
	const bool b_changed = (this->Type() != _e_type);
	if (b_changed)
		this->m_type = _e_type;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////
#if (0)
CFeature& CFeature::operator = (const CFeature& _src) { *this << _src.Data() << _src.Size() << _src.Type(); return *this; }
#endif
CFeature& CFeature::operator <<(const EFeature _e_type) { this->Type(_e_type); return *this; }
CFeature& CFeature::operator <<(const uint32_t _n_size) { this->Size(_n_size); return *this; }

/////////////////////////////////////////////////////////////////////////////

CFeature_Thread::CFeature_Thread (void) : TBase() {
	TBase::m_p_data = &this->m_data;
	TBase::m_size   = sizeof(this->m_data);
	TBase::m_type   = EFeature::D3D11_FEATURE_THREADING;
}

/////////////////////////////////////////////////////////////////////////////
const
TDataThread& CFeature_Thread::Ref (void) const { return this->m_data; }
TDataThread& CFeature_Thread::Ref (void)       { return this->m_data; }
#if defined(_DEBUG)
CString      CFeature_Thread::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{concurrent=%s;commands=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{concurrent=%s;commands=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{concurrent=%s;commands=%s;valid=%s}");

	CString cs_concurrent = TStringEx().Bool(this->Ref().DriverConcurrentCreates);
	CString cs_commands = TStringEx().Bool(this->Ref().DriverCommandLists);
	CString cs_valid = TStringEx().Bool(TBase::Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_concurrent, (_pc_sz)cs_commands, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_concurrent, (_pc_sz)cs_commands, (_pc_sz)cs_valid);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_concurrent, (_pc_sz)cs_commands, (_pc_sz)cs_valid); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CFeature_Format:: CFeature_Format (void) : TBase() {
	TBase::m_p_data = &this->m_data;
	TBase::m_size   = sizeof(this->m_data);
	TBase::m_type   = EFeature::D3D11_FEATURE_FORMAT_SUPPORT;
}

/////////////////////////////////////////////////////////////////////////////
const
TDataFromat& CFeature_Format::Ref (void) const { return this->m_data; }
TDataFromat& CFeature_Format::Ref (void)       { return this->m_data; }
#if defined(_DEBUG)
CString      CFeature_Format::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s%sfeature=%s;%s%ssupported=formats{%s%s}%s%svalid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{fmt_in=%s;supported=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{fmt_in=%s;supported=%s;valid=%s}");

	CString cs_fmt_in  = CClrBits().Print(this->Ref().InFormat);
	CString cs_fmt_out = CResFormat().Print(this->Ref().OutFormatSupport, _p_pfx, _p_sfx);
	CString cs_valid   = TStringEx().Bool(TBase::Is_valid());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
			_p_sfx, _p_pfx, (_pc_sz)cs_fmt_in ,
			_p_sfx, _p_pfx, _p_sfx, (_pc_sz)cs_fmt_out,
			_p_sfx, _p_pfx, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_fmt_in, (_pc_sz)cs_fmt_out, (_pc_sz)cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_fmt_in, (_pc_sz)cs_fmt_out, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
}}}}

namespace ex_ui { namespace draw { namespace direct_x { namespace _12 {

}}}}

