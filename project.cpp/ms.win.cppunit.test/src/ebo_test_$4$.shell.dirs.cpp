/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jul-2025 at 17:21:58.828, UTC+4, Batumi, Friday;
	This is Ebo pack system shell generic folder wrapper library unit test implementation file; 
*/
#include "ebo_test_$4$.shell.dirs.h"

using namespace ebo::boo::test::shell;

#include "uix.theme.named.h"
#include "uix.theme.reg.h"

using namespace ex_ui::theme;
using namespace ex_ui::theme::storage;

/////////////////////////////////////////////////////////////////////////////

CFolder:: CFolder (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CFolder::_ctor (void) {

	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_folder.Print(e_print::e_all));
	_out()();

}

void CFolder::EnumItems (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_folder.Print(e_print::e_all));
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CTestCase:: CTestCase (void) {
	this->m_error >> __CLASS__ << __METHOD__ << __s_ok;
	// current theme *must* be loaded first; otherwise the theme related registry keys are not available;
	ex_ui::theme::Get_current().Load();
}
CTestCase::~CTestCase (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  CTestCase::Error (void) const { return this->m_error; }

bool     CTestCase::Is_valid (void) const { return nullptr != this->m_root; }

_pc_sz   CTestCase::Get_path (void) const { return this->m_path; }

CString  CTestCase::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {path=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> path=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("path=%s;valid=%s");

	CString cs_path  = nullptr == this->Get_path() || 0 == ::_tcslen(this->Get_path()) ? _T("#n/a") : this->Get_path();
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_path, (_pc_sz) cs_valid); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_path, (_pc_sz) cs_valid); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_path, (_pc_sz) cs_valid); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}

err_code CTestCase::Set_path (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false)
		return this->m_error = __e_not_inited;

	t_char  sz_buffer[512] = {0}; unsigned long u_count = _countof(sz_buffer);

	unsigned long n_chars = u_count;

	LSTATUS n_result = this->m_root.QueryStringValue(_T("path"), sz_buffer, &n_chars);
	if (!!n_result)
		(this->m_error = dword(n_result)) = _T("Path to test cases is not specified;");
	else
		this->m_path = sz_buffer;

	return this->Error();
}

err_code CTestCase::Open (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid())    // the root key is already open;
		return this->m_error;

	CString cs_root  = this->Root();
	LSTATUS n_result = this->m_root.Open(Get_router().Root(), (_pc_sz) cs_root);
	if (!!n_result)
		this->m_error = dword(n_result);

	return this->Error();
}

CString  CTestCase::Root  (void) const {
	CString cs_root = Get_router().TestCase().Root();
	return  cs_root;
}

CString  CTestCase::Value (_pc_sz _p_name) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false) {
		this->m_error << __e_not_inited; return CString();
	}
	if (nullptr == _p_name || 0 == ::_tcslen(_p_name)) {
		this->m_error << __e_inv_arg; return CString();
	}
	t_char  sz_buffer[512] = {0}; unsigned long u_count = _countof(sz_buffer);

	unsigned long n_chars = u_count;
	LSTATUS n_result = m_root.QueryStringValue((_pc_sz) _p_name, sz_buffer, &n_chars);
	if (!!n_result) {
		(this->m_error = dword(n_result)) = TStringEx().Format(_T("The value of name '%s' is not defined;"), _p_name);
		return CString();
	}

	return CString(sz_buffer);
}

/////////////////////////////////////////////////////////////////////////////

CTestCase_0::CTestCase_0 (void) {
	if (false == true) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

TError&  CTestCase_0::Error (void) const { return this->m_error; }

CString  CTestCase_0::Get_path (const e_images _e_image) const {
	_e_image;
	
	CString cs_root  = Get_router().TestCase().Root(); cs_root += _T("\\control_0");

	CRegKey_Ex the_key;
	CString cs_image_file = the_key.Value().GetString((_pc_sz) cs_root, TStringEx().Format(_T("image_%u"), _e_image));

	if (cs_image_file.IsEmpty()) {
		this->m_error = the_key.Error();
	}
	CString cs_image_path = TStringEx().Format(_T("%s%s"), (_pc_sz) this->m_folder, (_pc_sz) cs_image_file);
	return  cs_image_path;
}

err_code CTestCase_0::Set_path (void) {

	CTestCase t_case;

	if (__failed(t_case.Open()) || __failed(t_case.Set_path())) // ToDo: it is need to be reviewed;
		return this->m_error = t_case.Error();

	this->m_folder = t_case.Get_path();
	this->m_folder += _T("sta-bar\\");

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("The path to image folder: %s%s"), _p_new_line, (_pc_sz) this->m_folder);

	_out()();

	return __s_ok;
}