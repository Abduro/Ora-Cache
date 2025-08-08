/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Apr-2025 at 11:39:59.352, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX resource flag enums wrapper interface implementation file;
*/
#include "direct_x.res.flag.h"

using namespace ex_ui::draw::direct_x;
using namespace ex_ui::draw::direct_x::_11;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
#if defined(_DEBUG)

	using CBind = ex_ui::draw::direct_x::_11::CBind;

	class CBind_Fmt {
	public:
		 CBind_Fmt (void) = default; CBind_Fmt (const CBind_Fmt&) = delete; CBind_Fmt (CBind_Fmt&&) = delete;
		~CBind_Fmt (void) = default;

	public:
		_pc_sz  ToCoders (uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CBind::ToCoders enum_;
			TStringEx cs_fmt;
			if (_n_flags & enum_::e_decoder) { _n_flags &= ~enum_::e_decoder; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_decoder, _T("enc::e_decoder"));}
			if (_n_flags & enum_::e_encoder) { _n_flags &= ~enum_::e_encoder; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_encoder, _T("enc::e_encoder"));}
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToBuffer (uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CBind::ToBuffer enum_;
			TStringEx cs_fmt;
			if (_n_flags & enum_::e_const ) { _n_flags &= ~enum_::e_const ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_const , _T("buf::e_const"));}
			if (_n_flags & enum_::e_index ) { _n_flags &= ~enum_::e_index ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_index , _T("buf::e_index"));}
			if (_n_flags & enum_::e_vertex) { _n_flags &= ~enum_::e_vertex; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_vertex, _T("buf::e_vertex"));}
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToMerger (uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CBind::ToMerger enum_;
			TStringEx cs_fmt;
			if (_n_flags & enum_::e_stencil) { _n_flags &= ~enum_::e_stencil; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_stencil, _T("mgr::e_stencil"));}
			if (_n_flags & enum_::e_target ) { _n_flags &= ~enum_::e_target ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_target , _T("mgr::e_target"));}
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToStage  (uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CBind::ToStage enum_;
			TStringEx cs_fmt;
			if (_n_flags & enum_::e_shader) { _n_flags &= ~enum_::e_shader; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_shader, _T("stg::e_shader"));}
			if (_n_flags & enum_::e_stream) { _n_flags &= ~enum_::e_stream; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_stream, _T("stg::e_stream"));}
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToOther  (uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CBind::e_flag enum_;
			TStringEx cs_fmt;
			if (_n_flags & enum_::e_access) { _n_flags &= ~enum_::e_access; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_access, _T("oth::e_access"));}
			return (_pc_sz)this->m_cs_out;
		}

	private:
		CBind_Fmt&  operator = (const CBind_Fmt&) = delete;
		CBind_Fmt&  operator = (CBind_Fmt&&) = delete;
	private:
		CString  m_cs_out;  // the format result cache;
	};

	using CMiscFlags = ex_ui::draw::direct_x::_11::CMiscFlags;
	class CMisc_Fmt {
	public:
		 CMisc_Fmt (void) = default; CMisc_Fmt (const CMisc_Fmt&) = delete; CMisc_Fmt (CMisc_Fmt&&) = delete;
		~CMisc_Fmt (void) = default;
	public:
		_pc_sz  ToAccess(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CMiscFlags::ToAccess enum_;
			TStringEx cs_fmt;

			if (_n_flags & enum_::e_guarded) { _n_flags &= ~enum_::e_guarded; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_guarded, _T("acc::e_guarded")); }
			if (_n_flags & enum_::e_protect) { _n_flags &= ~enum_::e_protect; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_protect, _T("acc::e_protect")); }
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToBuffer(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CMiscFlags::ToBuffer enum_;
			TStringEx cs_fmt;

			if (_n_flags & enum_::e_view  ) { _n_flags &= ~enum_::e_view  ; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_view  , _T("buf::e_view")); }
			if (_n_flags & enum_::e_struct) { _n_flags &= ~enum_::e_struct; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_struct, _T("buf::e_struct")); }
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToDraw(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CMiscFlags::ToDraw enum_;
			TStringEx cs_fmt;

			if (_n_flags & enum_::e_inderect ) { _n_flags &= ~enum_::e_inderect ; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_inderect , _T("drw::e_inderect")); }
			if (_n_flags & enum_::e_gdi_comp ) { _n_flags &= ~enum_::e_gdi_comp ; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_gdi_comp , _T("drw::e_gdi_comp")); }
			if (_n_flags & enum_::e_gen_mips ) { _n_flags &= ~enum_::e_gen_mips ; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_gen_mips , _T("drw::e_gen_mips")); }
			if (_n_flags & enum_::e_res_clamp) { _n_flags &= ~enum_::e_res_clamp; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_res_clamp, _T("drw::e_res_clamp")); }
			if (_n_flags & enum_::e_tex_cude ) { _n_flags &= ~enum_::e_tex_cude ; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_tex_cude , _T("drw::e_tex_cude")); }

			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToRestrict(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CMiscFlags::ToRestrict enum_;
			TStringEx cs_fmt;

			if (_n_flags & enum_::e_content ) { _n_flags &= ~enum_::e_content ; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_content , _T("rst::e_content")); }
			if (_n_flags & enum_::e_driver  ) { _n_flags &= ~enum_::e_driver  ; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_driver  , _T("rst::e_driver")); }
			if (_n_flags & enum_::e_resource) { _n_flags &= ~enum_::e_resource; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_resource, _T("rst::e_resource")); }
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToShare(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CMiscFlags::ToShare enum_;
			TStringEx cs_fmt;

			if (_n_flags & enum_::e_device) { _n_flags &= ~enum_::e_device; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_device, _T("sha::e_device")); }
			if (_n_flags & enum_::e_mutex ) { _n_flags &= ~enum_::e_mutex ; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_mutex , _T("sha::e_mutex")); }
			if (_n_flags & enum_::e_handle) { _n_flags &= ~enum_::e_handle; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_handle, _T("sha::e_handle")); }
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToTile(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CMiscFlags::ToTile enum_;
			TStringEx cs_fmt;

			if (_n_flags & enum_::e_pool) { _n_flags &= ~enum_::e_pool; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_pool, _T("til::e_pool")); }
			if (_n_flags & enum_::e_made) { _n_flags &= ~enum_::e_made; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_made, _T("til::e_made")); }
			return (_pc_sz)this->m_cs_out;
		}

	private:
		CMisc_Fmt& operator = (const CMisc_Fmt&) = delete;
		CMisc_Fmt& operator = (CMisc_Fmt&&) = delete;
	private:
		CString  m_cs_out;  // the format result cache;
	};
#endif
}}}}
using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString CBind::Print (const uint32_t _n_flags, _pc_sz _p_pfx, _pc_sz _p_sfx) {
	_n_flags, _p_pfx; _p_sfx;
	uint32_t n_flags = _n_flags;
	CString cs_out ;

	if (0 == n_flags) {
		cs_out = _T("0;#unset");
		return cs_out;
	}
	CString cs_temp;
	cs_temp = CBind_Fmt().ToCoders (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CBind_Fmt().ToBuffer (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CBind_Fmt().ToMerger (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CBind_Fmt().ToStage  (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CBind_Fmt().ToOther  (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}

	if (!!n_flags) { // some flag(s) are not captured;
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += TStringEx().Format(_T("0x%08x(%s)"), n_flags, _T("#undef"));
	}

	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString CMiscFlags::Print (const uint32_t _n_flags, _pc_sz _p_pfx, _pc_sz _p_sfx) /*const*/ {
	_n_flags, _p_pfx; _p_sfx;
	uint32_t n_flags = _n_flags;
	CString cs_out ;
	
	if (0 == n_flags) {
		cs_out = _T("0;#unset");
		return cs_out;
	}
	CString cs_temp;
	cs_temp = CMisc_Fmt().ToAccess (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CMisc_Fmt().ToBuffer (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CMisc_Fmt().ToDraw (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CMisc_Fmt().ToRestrict (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CMisc_Fmt().ToShare(n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CMisc_Fmt().ToTile (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}

	if (!!n_flags) { // some flag(s) are not captured;
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += TStringEx().Format(_T("0x%08x(%s)"), n_flags, _T("#undef"));
	}
	
	return cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString  CResUsage::Print (const uint32_t _n_usage) {
	_n_usage;
	CString cs_out;
	switch (_n_usage) {
	case TResUsage::D3D11_USAGE_DEFAULT  : cs_out = _T("default"); break;
	case TResUsage::D3D11_USAGE_DYNAMIC  : cs_out = _T("dynamic"); break;
	case TResUsage::D3D11_USAGE_IMMUTABLE: cs_out = _T("immutable"); break;
	case TResUsage::D3D11_USAGE_STAGING  : cs_out = _T("staging"); break;
	default:
		cs_out.Format(_T("#inv_arg:%d"), _n_usage);
	}
	return  cs_out;
}
#endif