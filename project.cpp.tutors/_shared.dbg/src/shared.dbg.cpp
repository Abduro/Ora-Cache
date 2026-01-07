/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Aug-2025 at 10:50:23.166, UTC+4, Batumi, Saturday;
	This is Ebo Pack shared project debug config implementation file;
	-----------------------------------------------------------------------------
	Adopted to tutorials solution on 19-Aug-2025 at 11:33:11.427, UTC+4, Batumi, Tuesday;
*/
#include "shared.dbg.h"
#if (0)
#include "shared.str.ext.h" // not applicable in this solution(s) of the tutorials;
#endif
#include "console.out.h"

using namespace shared::console;

#if defined(_DEBUG)
namespace shared { namespace dbg {

namespace _impl {
	CString CatToStr (const CTrace::e_category _e_cat) {
		_e_cat;
		switch (_e_cat) {
		case CTrace::e_category::e_warn: return CString(_T("[warn]"));
		case CTrace::e_category::e_err : return CString(_T("[error]"));
		case CTrace::e_category::e_impt: return CString(_T("[impt]"));
		default:
			return CString(_T("[info]"));
		}
	}

	ITestOutput* m_test_out = 0;
}
using namespace _impl;
using namespace shared::defs;

void CTrace::Empty_ln (void) {
	::OutputDebugString(_T("\n"));
}

void CTrace::OnTime (_pc_sz _p_text) {
	_p_text;
	// https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getlocaltime ;
	SYSTEMTIME sys_time = {0};
	::GetLocalTime(&sys_time); // returns no error;

	static _pc_sz pc_sz_pat = _T("%04u-%02u-%02u %02u:%02u:%02u.%03u");

	CString cs_format;
	if (0 == _p_text) {
		cs_format = TString().Format(_T("Logged at: %s\n"), pc_sz_pat);
	}
	else { // the 'else' is not expected but nevertheless; it will look like: [timestamp] the input text;
		cs_format = TString().Format(_T("[%s] %s"), pc_sz_pat, _p_text);
	}
	__trace_warn((_pc_sz) cs_format,
		sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds);
}

static bool b_use_con = true;

void CTrace::Use_con (const bool _b_use) {
	b_use_con = _b_use;
}

bool CTrace::Use_con  (void) {
	return b_use_con;
}

void CTrace::Out_0 (_pc_sz _lp_sz_fmt, ...) {

	va_list  args_;
	va_start(args_, _lp_sz_fmt);

	CString cs_out; cs_out.FormatV(_lp_sz_fmt, args_);

	// https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-outputdebugstringw ;
	::OutputDebugString((_pc_sz) cs_out);

	TSafe_Lock();
	if (_impl::m_test_out)
		_impl::m_test_out->Write((_pc_sz) cs_out);

	va_end  (args_);
}

void CTrace::Out_0 (const e_category _e_cat, _pc_sz _lp_sz_fmt, ...) { // perhaps __VA_ARGS__ would be useful, but for this time is not used;
	_e_cat; _lp_sz_fmt;
	va_list  args_;
	va_start(args_, _lp_sz_fmt);

	CString cs_in ; cs_in.FormatV(_lp_sz_fmt, args_);
	CString cs_out; cs_out.Format(_T("%s %s"), (_pc_sz) CatToStr(_e_cat), (_pc_sz) cs_in);

	if (CTrace::Use_con()) {
		if (e_category::e_err  == _e_cat) { COut::Error((_pc_sz)cs_out); }
		if (e_category::e_impt == _e_cat) { COut::Impt ((_pc_sz)cs_out); }
		if (e_category::e_info == _e_cat) { COut::Info ((_pc_sz)cs_out); }
		if (e_category::e_warn == _e_cat) { COut::Warn ((_pc_sz)cs_out); }
	}
//	else
	::OutputDebugString((_pc_sz) cs_out);

	TSafe_Lock();
	if (_impl::m_test_out)
		_impl::m_test_out->Write((_pc_sz) cs_out);

	va_end  (args_);
}

void CTrace::Out_2 (const e_category _e_cat, _pc_sz _p_cls, _pc_sz _p_method, _pc_sz _p_sz_format, ...) {
	_e_cat; _p_cls; _p_method; _p_sz_format;
	va_list  args_;
	va_start(args_, _p_sz_format);

	CString cs_in ; cs_in.FormatV(_p_sz_format, args_);
	CString cs_out; cs_out.Format(_T("%s cls::[%s].%s()>>%s"), (_pc_sz) CatToStr(_e_cat), _p_cls, _p_method, (_pc_sz) cs_in);

	if (CTrace::Use_con()) {
		if (e_category::e_err  == _e_cat) { COut::Error((_pc_sz)cs_out); }
		if (e_category::e_impt == _e_cat) { COut::Impt ((_pc_sz)cs_out); }
		if (e_category::e_info == _e_cat) { COut::Info ((_pc_sz)cs_out); }
		if (e_category::e_warn == _e_cat) { COut::Warn ((_pc_sz)cs_out); }
	}
//	else
	::OutputDebugString((_pc_sz) cs_out);

	TSafe_Lock();
	if (_impl::m_test_out)
		_impl::m_test_out->Write((_pc_sz) cs_out);

	va_end  (args_);
}

void CTrace::Out_3 (const e_category _e_cat, _pc_sz _p_nm_space, _pc_sz _p_cls, _pc_sz _p_method, _pc_sz _p_sz_format, ...) {
	_e_cat; _p_nm_space; _p_cls; _p_method; _p_sz_format;
	va_list  args_;
	va_start(args_, _p_sz_format);

	CString cs_in ; cs_in.FormatV(_p_sz_format, args_);
	CString cs_out; cs_out.Format(_T("%s cls::[%s::%s].%s()>>%s"), (_pc_sz) CatToStr(_e_cat), _p_nm_space, _p_cls, _p_method, (_pc_sz) cs_in);

	if (CTrace::Use_con()) {
		if (e_category::e_err  == _e_cat) { COut::Error((_pc_sz)cs_out); }
		if (e_category::e_impt == _e_cat) { COut::Impt ((_pc_sz)cs_out); }
		if (e_category::e_info == _e_cat) { COut::Info ((_pc_sz)cs_out); }
		if (e_category::e_warn == _e_cat) { COut::Warn ((_pc_sz)cs_out); }
	}
//	else
	::OutputDebugString((_pc_sz) cs_out);

	TSafe_Lock();
	if (_impl::m_test_out)
		_impl::m_test_out->Write((_pc_sz) cs_out);

	va_end  (args_);
}

void CTrace::SetTestOut (ITestOutput* _p_out) {

	TSafe_Lock();
	_impl::m_test_out = _p_out;
}

}}
#else
namespace shared { namespace dbg { namespace _impl { void __warning_lnk_4221 (void) {}}}}
#endif