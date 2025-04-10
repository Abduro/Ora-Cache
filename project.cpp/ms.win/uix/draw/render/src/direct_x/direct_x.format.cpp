/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Apr-2025 at 15:59:06.100, UTC+4, Batumi, Tuesday;
	This is Ebo pack DirectX data format base interface implementation file;
*/
#include "direct_x.format.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////

CClrBits:: CClrBits (void) {}

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString    CClrBits::Print (const uint32_t _n_format) const {

	static _pc_sz pc_sz_pat = _T("%d(%s)");

	CString cs_out;
	switch (_n_format) {
	case TClrBits::DXGI_FORMAT_UNKNOWN       : cs_out.Format(pc_sz_pat, _n_format, _T("unknown")); break;
	case TClrBits::DXGI_FORMAT_B8G8R8A8_UNORM: cs_out.Format(pc_sz_pat, _n_format, _T("b8g8r8a8_unorm")); break;
//	case TClrBits::DXGI_FORMAT_XXXXXXX: cs_out.Format(pc_sz_pat, _n_format, _T("")); break;
	default:
		cs_out.Format(pc_sz_pat, _n_format, _T("#unspec"));
	}

	return cs_out; 
}
#endif

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
#if defined(_DEBUG)
	using namespace _11;
	class CRes_fmt {
	public:
		 CRes_fmt (void) = default; CRes_fmt (const CRes_fmt&) = delete; CRes_fmt (CRes_fmt&&) = delete;
		~CRes_fmt (void) = default;

	public:
		_pc_sz  Buffer(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CResFormat::e_buffer enum_;
			TStringEx cs_fmt;
			if (_n_flags & enum_::e_back_cast) { _n_flags &= ~enum_::e_back_cast; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_back_cast, _T("bf::e_back_cast"));}
			if (_n_flags & enum_::e_buffer_nm) { _n_flags &= ~enum_::e_buffer_nm; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_buffer_nm, _T("bf::e_buffer_nm"));}
			if (_n_flags & enum_::e_buffer_so) { _n_flags &= ~enum_::e_buffer_so; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_buffer_so, _T("bf::e_buffer_so"));}
			if (_n_flags & enum_::e_ia_index ) { _n_flags &= ~enum_::e_ia_index ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_ia_index , _T("bf::e_ia_index")) ;}
			if (_n_flags & enum_::e_ia_vertex) { _n_flags &= ~enum_::e_ia_vertex; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_ia_vertex, _T("bf::e_ia_vertex"));}
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  Mips(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CResFormat::e_mip enum_;
			TStringEx cs_fmt;

			if (_n_flags & enum_::e_auto) { _n_flags &= ~enum_::e_auto; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_auto, _T("mp::e_auto")); }
			if (_n_flags & enum_::e_maps) { _n_flags &= ~enum_::e_maps; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_maps, _T("mp::e_maps")); }
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  Sample(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CResFormat::e_multismp enum_;
			TStringEx cs_fmt;

			if (_n_flags & enum_::e_loaded ) { _n_flags &= ~enum_::e_loaded ; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_loaded , _T("sm::e_loaded")) ;}
			if (_n_flags & enum_::e_render ) { _n_flags &= ~enum_::e_render ; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_render , _T("sm::e_render")) ;}
			if (_n_flags & enum_::e_resolve) { _n_flags &= ~enum_::e_resolve; if (_T("") != m_cs_out) { m_cs_out += _T("|"); } m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"), enum_::e_resolve, _T("sm::e_resolve"));}
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  Shader(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CResFormat::e_shader enum_;
			TStringEx cs_fmt;

			if (_n_flags & enum_::e_gather    ) { _n_flags &= ~enum_::e_gather    ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_gather    , _T("sh::e_gather"))    ;}
			if (_n_flags & enum_::e_gather_cmp) { _n_flags &= ~enum_::e_gather_cmp; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_gather_cmp, _T("sh::e_gather_cmp"));}
			if (_n_flags & enum_::e_load      ) { _n_flags &= ~enum_::e_load      ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_load      , _T("sh::e_load"))      ;}
			if (_n_flags & enum_::e_sample    ) { _n_flags &= ~enum_::e_sample    ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_sample    , _T("sh::e_sample"))    ;}
			if (_n_flags & enum_::e_sample_cmp) { _n_flags &= ~enum_::e_sample_cmp; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_sample_cmp, _T("sh::e_sample_cmp"));}
			if (_n_flags & enum_::e_mono_rext ) { _n_flags &= ~enum_::e_mono_rext ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_mono_rext , _T("sh::e_mono_rext")) ;}
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  Texture(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CResFormat::e_texture enum_;
			TStringEx cs_fmt;

			if (_n_flags & enum_::e_1d  ) { _n_flags &= ~enum_::e_1d  ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_1d  , _T("tx::e_1d"))  ;}
			if (_n_flags & enum_::e_2d  ) { _n_flags &= ~enum_::e_2d  ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_2d  , _T("tx::e_2d"))  ;}
			if (_n_flags & enum_::e_3d  ) { _n_flags &= ~enum_::e_3d  ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_3d  , _T("tx::e_3d"))  ;}
			if (_n_flags & enum_::e_cube) { _n_flags &= ~enum_::e_cube; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_cube, _T("tx::e_cube"));}
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  Video(uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CResFormat::e_video enum_;
			TStringEx cs_fmt;

			if (_n_flags & enum_::e_encoder ) { _n_flags &= ~enum_::e_encoder ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_encoder , _T("vd::e_encoder")) ;}
			if (_n_flags & enum_::e_proc_in ) { _n_flags &= ~enum_::e_proc_in ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_proc_in , _T("vd::e_proc_in")) ;}
			if (_n_flags & enum_::e_proc_out) { _n_flags &= ~enum_::e_proc_out; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_proc_out, _T("vd::e_proc_out"));}
			return (_pc_sz)this->m_cs_out;
		}
	private:
		CRes_fmt& operator = (const CRes_fmt&) = delete;
		CRes_fmt& operator = (CRes_fmt&&) = delete;
	private:
		CString  m_cs_out;  // the format result cache;
	};
#endif
}}}}
using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {

CResFormat:: CResFormat (void) {}

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString      CResFormat::Print (const uint32_t _n_flags, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_n_flags, _p_pfx; _p_sfx;
	uint32_t n_flags = _n_flags;
	CString cs_out ;
	
	if (0 == n_flags) {
		cs_out = _T("0;#undef");
		return cs_out;
	}
	CString cs_temp;
	cs_temp = CRes_fmt().Buffer (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CRes_fmt().Mips (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CRes_fmt().Sample (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CRes_fmt().Shader (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CRes_fmt().Texture(n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CRes_fmt().Video  (n_flags); if (cs_temp.IsEmpty() == false) {
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
}}}}