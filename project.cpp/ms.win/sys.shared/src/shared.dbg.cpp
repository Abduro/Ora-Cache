/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Aug-2025 at 10:50:23.166, UTC+4, Batumi, Saturday;
	This is Ebo Pack shared project debug config implementation file;
*/
#include "shared.dbg.h"
#include "shared.str.ext.h"

#if defined(_DEBUG)
namespace shared { namespace dbg {

namespace _impl {
	CString TraceCatToStr (const CTrace::e_category _e_cat) {
		_e_cat;
		switch (_e_cat) {
		case CTrace::e_category::e_warn: return CString(_T("[warn]"));
		case CTrace::e_category::e_err : return CString(_T("[error]"));
		default:
			return CString(_T("[info]"));
		}
	}
}
using namespace _impl;
using namespace shared::types;

void CTrace::Out (const TCHAR* _lp_sz_fmt, ...) {

	va_list  args_;
	va_start(args_, _lp_sz_fmt);

	CString cs_fmt = TStringEx().Format(_T("%s\n"), _lp_sz_fmt);

	// https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-outputdebugstringw ;
	::OutputDebugString(TStringEx().Format((_pc_sz) cs_fmt, args_));

	va_end  (args_);
}

void CTrace::Out (const e_category _e_cat, const TCHAR* _lp_sz_fmt, ...) { // perhaps __VA_ARGS__ would be useful, but for this time is not used;
	va_list  args_;
	va_start(args_, _lp_sz_fmt);

	CString cs_out = TraceCatToStr(_e_cat);
	cs_out += _T(" ");
	cs_out += TStringEx().Format(_lp_sz_fmt, args_);

	::OutputDebugString(cs_out.GetString());

	va_end  (args_);
}

}}
#else
namespace shared { namespace dbg { namespace _impl { void __warning_lnk_4221 (void) {}}}}
#endif