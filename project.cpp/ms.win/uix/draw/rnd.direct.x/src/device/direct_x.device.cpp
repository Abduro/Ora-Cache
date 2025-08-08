/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Apr-2025 at 16:31:42.013, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX device base wrapper interface implementation file;
*/
#include "direct_x.device.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
	void __warning_lnk_4221 (const bool _b_dummy) { _b_dummy; }
}}}}

#if defined(_DEBUG)
CString  CDrv_Type::Print (const uint32_t _n_type) {
	_n_type;
	CString cs_out;
	switch (_n_type) {
	case CDrv_Type::e__unk : cs_out = _T("drv:e__unk"); break;
	case CDrv_Type::e_hard : cs_out = _T("drv:e_hard"); break;
	case CDrv_Type::e_null : cs_out = _T("drv:e_null"); break;
	case CDrv_Type::e_ref  : cs_out = _T("drv:e_ref" ); break;
	case CDrv_Type::e_soft : cs_out = _T("drv:e_soft"); break;
	case CDrv_Type::e_warp : cs_out = _T("drv:e_warp"); break;
	default:
		cs_out.Format(_T("#undef:%d"), _n_type);
	}
	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

using namespace ex_ui::draw::direct_x::_11;

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
#if defined(_DEBUG)
	using namespace _11;
	class CDev_fmt {
	public:
		 CDev_fmt (void) = default; CDev_fmt (const CDev_fmt&) = delete; CDev_fmt (CDev_fmt&&) = delete;
		~CDev_fmt (void) = default;

	public:
		_pc_sz  ToDbg (uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CDev_Flags::ToDbg enum_;
			TStringEx cs_fmt;
			if (_n_flags & enum_::e_device) { _n_flags &= ~enum_::e_device; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_device, _T("dbg::e_device"));}
			if (_n_flags & enum_::e_shader) { _n_flags &= ~enum_::e_shader; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_shader, _T("dbg::e_shader"));}
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToNot (uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CDev_Flags::ToNot enum_;
			TStringEx cs_fmt;
			if (_n_flags & enum_::e_opt ) { _n_flags &= ~enum_::e_opt ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_opt , _T("no::e_opt" ));}
			if (_n_flags & enum_::e_reg ) { _n_flags &= ~enum_::e_reg ; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_reg , _T("no::e_reg" ));}
			if (_n_flags & enum_::e_time) { _n_flags &= ~enum_::e_time; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_time, _T("no::e_time"));}
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToPerf (uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CDev_Flags::ToPerf enum_;
			TStringEx cs_fmt;
			if (_n_flags & enum_::e_ref) { _n_flags &= ~enum_::e_ref; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_ref, _T("run::e_ref"));}
			if (_n_flags & enum_::e_one) { _n_flags &= ~enum_::e_one; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_one, _T("run::e_one"));}
			return (_pc_sz)this->m_cs_out;
		}

		_pc_sz  ToSup (uint32_t& _n_flags) {
			_n_flags;
			if (m_cs_out.IsEmpty() == false)
				m_cs_out.Empty();

			if (0 == _n_flags)
				return (_pc_sz)this->m_cs_out;

			typedef CDev_Flags::ToSup enum_;
			TStringEx cs_fmt;
			if (_n_flags & enum_::e_bgra) { _n_flags &= ~enum_::e_bgra; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_bgra, _T("sup::e_bgra"));}
			if (_n_flags & enum_::e_wddm) { _n_flags &= ~enum_::e_wddm; if (_T("") != m_cs_out) { m_cs_out += _T("|");} m_cs_out += cs_fmt.Format(_T("0x%08x(%s)"),enum_::e_wddm, _T("sup::e_wddm"));}
			return (_pc_sz)this->m_cs_out;
		}
	private:
		CDev_fmt& operator = (const CDev_fmt&) = delete;
		CDev_fmt& operator = (CDev_fmt&&) = delete;
	private:
		CString  m_cs_out;  // the format result cache;
	};
#endif
}}}}
using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString CDev_Flags::Print (const uint32_t _n_flags, _pc_sz _p_pfx, _pc_sz _p_sfx) {
	_n_flags, _p_pfx; _p_sfx;
	uint32_t n_flags = _n_flags;
	CString cs_out ;

	if (0 == n_flags) {
		cs_out = _T("0;#unset");
		return cs_out;
	}
	CString cs_temp;
	cs_temp = CDev_fmt().ToDbg (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CDev_fmt().ToNot (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CDev_fmt().ToPerf (n_flags); if (cs_temp.IsEmpty() == false) {
		if (cs_out.IsEmpty() == false) {
			cs_out += _p_sfx;
		}
		cs_out += _p_pfx;
		cs_out += cs_temp;
	}
	cs_temp = CDev_fmt().ToSup (n_flags); if (cs_temp.IsEmpty() == false) {
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