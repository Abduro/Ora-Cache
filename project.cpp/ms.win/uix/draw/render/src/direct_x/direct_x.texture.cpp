/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Apr-2025 at 02:19:11.186, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX texture wrapper interface implementation file;
*/
#include "direct_x.texture.h"

using namespace ex_ui::draw::direct_x;

using namespace ex_ui::draw::direct_x::_11::_2D;
using namespace ex_ui::draw::direct_x::_12;

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
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_cpu_access_flag ;
	using ECpu_Access = D3D11_CPU_ACCESS_FLAG;
	class CCpu_Access {
	public:
		 CCpu_Access (void) = default; CCpu_Access (const CCpu_Access&) = delete; CCpu_Access (CCpu_Access&&) = delete;
		~CCpu_Access (void) = default;

	public:
		static
		CString  Print (uint32_t _n_access) {
			_n_access;
			CString cs_out;
			switch (_n_access) {
			case ECpu_Access::D3D11_CPU_ACCESS_WRITE: cs_out = _T("write"); break;
			case ECpu_Access::D3D11_CPU_ACCESS_READ : cs_out = _T("read"); break;
			default:
				cs_out.Format(_T("%d(#undef)"));
			}
			return  cs_out;
		}

	private:
		CCpu_Access& operator = (const CCpu_Access&) = delete;
		CCpu_Access& operator = (CCpu_Access&&) = delete;
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

	using TTex_srv  = D3D11_TEX1D_SRV;
	using TTex_cube = D3D11_TEXCUBE_ARRAY_SRV;

	class CTex_Array {   // https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_texture2d_desc ;
	public:
		 CTex_Array (const uint32_t _n_mips = 0, const uint32_t _n_size = 0) : m_mips(_n_mips), m_size(_n_size) {}
		 CTex_Array (const CTex_Array&) = delete; CTex_Array (CTex_Array&&) = delete;
		~CTex_Array (void) = default;

	public:
		uint32_t  Mips (void) const { return this->m_mips; }
		bool      Mips (const uint32_t _n_value) {
			_n_value;
			const bool b_changed = (this->Mips() != _n_value);
			if (b_changed)
				this->m_mips = _n_value;

			return b_changed;
		}

#if defined(_DEBUG)
		CString  Print (const e_print _e_opt = e_print::e_all) const {
			_e_opt;
			static _pc_sz pc_sz_pat = _T("tex={mips:%d;count:%d}");
			CString cs_out; cs_out.Format(pc_sz_pat, this->Mips(), this->Size());
			return  cs_out;
		}
#endif
		uint32_t  Size (void) const { return this->m_size; }
		bool      Size (const uint32_t _n_value) {
			_n_value;
			const bool b_changed = (this->Size() != _n_value);
			if (b_changed)
				this->m_size = _n_value;

			return b_changed;
		}
#if defined(_DEBUG)
		public:
		operator CString (void) const { return this->Print(e_print::e_req); }
#endif
	private:
		uint32_t m_mips ; // the maximum number of mipmap levels in the texture;
		uint32_t m_size ; // the number of textures in the texture array;
	};

	class CTexDesc_Fmt {
	public:
		 CTexDesc_Fmt (void) = default; CTexDesc_Fmt (const CTexDesc_Fmt&) = delete; CTexDesc_Fmt (CTexDesc_Fmt&&) = delete;
		~CTexDesc_Fmt (void) = default;

	public:
		CString  Format (const TTex_cube& _cube) const {
			/*
				https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_texcube_array_srv ;
				{TTex_srv}
				UINT First2DArrayFace :: the index of the first 2D texture to use;
				UINT NumCubes         :: the number of cube textures in the array;
			*/
			_cube;
			TTex_srv srv = { _cube.MostDetailedMip, _cube.MipLevels };
			static _pc_sz pc_sz_pat = _T("mips:{%s};2d:{index=%d;cubes=%d}");
			CString cs_srv = this->Format(srv);
			CString cs_out;  cs_out.Format(pc_sz_pat, (_pc_sz)cs_srv,  _cube.First2DArrayFace, _cube.MipLevels);
			return  cs_out;
		}

		CString  Format (const TTex_srv& _mips) const {
			/*
				https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_tex1d_srv ;
				UINT MostDetailedMip :: the index of the most detailed mipmap level to use; the value is within [0..MipLevels];
				UINT MipLevels       :: the maximum number of mipmap levels for the view of the texture; -1 is acceptable;
			*/
			_mips;
			static _pc_sz pc_sz_pat = _T("index=%d;levels=%d");
			CString cs_out;  cs_out.Format(pc_sz_pat, _mips.MostDetailedMip, _mips.MipLevels);
			return  cs_out;
		}

	public:
		CString  operator << (const TTex_cube& _cube) const { return this->Format(_cube); }
		CString  operator << (const TTex_srv& _mips) const { return this->Format(_mips); }

	private:
		CTexDesc_Fmt& operator = (const CTexDesc_Fmt&) = delete;
		CTexDesc_Fmt& operator = (CTexDesc_Fmt&&) = delete;
	};
#endif
}}}}
using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString CMiscFlags::Print (const uint32_t _n_flags, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
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
CString  CTexUsage::Print (const uint32_t _n_usage) {
	_n_usage;
	CString cs_out;
	switch (_n_usage) {
	case TTexUsage::D3D11_USAGE_DEFAULT  : cs_out = _T("default"); break;
	case TTexUsage::D3D11_USAGE_DYNAMIC  : cs_out = _T("dynamic"); break;
	case TTexUsage::D3D11_USAGE_IMMUTABLE: cs_out = _T("immutable"); break;
	case TTexUsage::D3D11_USAGE_STAGING  : cs_out = _T("staging"); break;
	default:
		cs_out.Format(_T("#inv_arg:%d"), _n_usage);
	}
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CTexDesc:: CTexDesc (void) : m_desc{0} {}

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
void CTexDesc::Fake (void) {
	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-resources-textures-create ;
	TTexDesc& desc = this->Raw();
	desc.Width     = 256;
	desc.Height    = 256;
	desc.MipLevels = desc.ArraySize = 1;
	desc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage     = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
}

CString CTexDesc::Print (const TTexDesc& _raw) {
	_raw;
	/*
	size = {u_width;u_height};    :: texture size in pixels;
	array = {u_mips;m_size};      :: CTex_Array();
	the format of the color bits; :: CClrBits();           
	the sample description;       :: CSample();
	the texture usage;            :: CTexUsage();
	UINT BindFlags;               :: CBind();
	UINT CPUAccessFlags;          :: CCpu_Access();
	UINT MiscFlags;               :: CMiscFlags() ;
	*/
	static _pc_sz pc_sz_pat = _T("size:{%s};array:{%s};fmt=%s;smp=%s;use=%s;bind=%s;acc=%s;misc={%s}");

	CString cs_acc   = CCpu_Access::Print(_raw.CPUAccessFlags); 
	CString cs_array = CTex_Array(_raw.MipLevels, _raw.ArraySize);
	CString cs_bind  = CBind::Print(_raw.BindFlags, _T(""), _T(""));
	CString cs_clr   = CClrBits().Print(_raw.Format);
	CString cs_misc  = CMiscFlags().Print(_raw.MiscFlags);
	CString cs_smp   = CSample::Print(_raw.SampleDesc);
	CString cs_size  = TStringEx().Format(_T("w=%dpx;h=%dpx"), _raw.Width, _raw.Height);
	CString cs_use   = CTexUsage::Print(_raw.Usage);

	CString cs_out;
	        cs_out.Format(pc_sz_pat,
	         (_pc_sz)cs_size, (_pc_sz)cs_array, (_pc_sz)cs_clr, (_pc_sz)cs_smp,(_pc_sz)cs_use,
	         (_pc_sz)cs_bind, (_pc_sz)cs_acc  , (_pc_sz)cs_misc);
	return  cs_out;
}

#endif
const
TTexDesc& CTexDesc::Raw (void) const { return this->m_desc; }
TTexDesc& CTexDesc::Raw (void)       { return this->m_desc; }

/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {
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
}}}}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CTexture:: CTexture (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////
const
CTexDesc&  CTexture::Desc (void) const { return this->m_desc; }
CTexDesc&  CTexture::Desc (void)       { return this->m_desc; }

TError&    CTexture::Error (void) const { return this->m_error; }
bool       CTexture::Is_valid (void) const { return nullptr != this->Ptr(); }

#if defined(_DEBUG)
CString    CTexture::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{valid=%s}");

//	CString cs_desc  = this->Desc().Print();
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

const
TTexPtr&   CTexture::Ptr (void) const { return this->m_p_tex; }
err_code   CTexture::Ptr (const TTexPtr& _p_tex) {
	_p_tex;
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	if (nullptr == _p_tex)
		return this->m_error << __e_pointer;

	this->m_p_tex = _p_tex;
	this->Ptr()->GetDesc(&this->Desc().Raw());

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////