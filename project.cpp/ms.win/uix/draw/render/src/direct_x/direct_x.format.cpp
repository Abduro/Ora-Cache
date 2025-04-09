/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Apt-2025 at 15:59:06.100, UTC+4, Batumi, Tuesday;
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

CResFormat:: CResFormat (void) {}

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString      CResFormat::Print (const uint32_t _n_flags) const {

	static _pc_sz pc_sz_pat = _T("%s;%s");

	uint32_t n_flags = _n_flags;

	CString cs_out ;
	CString cs_code;
	CString cs_name;

	if (0 == n_flags) {
		cs_out = _T("0;#undef");
		return cs_out;
	}
	
	if (n_flags & CResFormat::e_normal   ) { n_flags &=~CResFormat::e_normal   ; if (!cs_code.IsEmpty()){ cs_code += _T("|"); cs_name += _T("|"); }}
	if (n_flags & CResFormat::e_buffer_so) { n_flags &=~CResFormat::e_buffer_so; if (!cs_code.IsEmpty()){ cs_code += _T("|"); cs_name += _T("|"); }}
	if (n_flags & CResFormat::e_ia_index ) { n_flags &=~CResFormat::e_ia_index ; if (!cs_code.IsEmpty()){ cs_code += _T("|"); cs_name += _T("|"); }}
	if (n_flags & CResFormat::e_ia_vertex) { n_flags &=~CResFormat::e_ia_vertex; if (!cs_code.IsEmpty()){ cs_code += _T("|"); cs_name += _T("|"); }}

	if (!!n_flags) { // missed capturing flag(s)
		if (!cs_code.IsEmpty()) { cs_code += _T("|");  cs_out.Format(_T("%d"), n_flags); cs_code += cs_out; }
		if (!cs_name.IsEmpty()) { cs_name += _T("|");  cs_out.Format(_T("%d"), n_flags); cs_name += cs_out; }
	}

	cs_out.Format(pc_sz_pat, (_pc_sz)cs_code, (_pc_sz)cs_name);

	return cs_out;
}
#endif