/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jul-2025 at 10:51:48.442, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI in-memory image cache unit test interface declaration file;
*/
#include "ebo_test_$d$.zbuf.cache.h"
#include "uix.theme.named.h"
#include "uix.theme.reg.h"

using namespace ebo::boo::test::cache;

using namespace ex_ui::theme;
using namespace ex_ui::theme::storage;

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { namespace cache { namespace _impl {

	class CTestCase {
	public:
		 CTestCase (void) { this->m_error >> __CLASS__ << __METHOD__ << __s_ok; }
		 CTestCase (const CTestCase&) = delete; CTestCase (CTestCase&&) = delete;
		~CTestCase (void) {}

	public:
		_pc_sz   GetApp_ready (void) const { return this->m_app_ready.GetString(); }
		err_code SetApp_ready (void) {
			this->m_error << __METHOD__ << __s_ok;

			if (this->m_path.IsEmpty() || nullptr == this->m_sta_bar.m_hKey) {
				return this->m_error << __e_not_inited = _T("The test path is not set");
			}

			CString cs_file;
			t_char  sz_buffer[512] = {0}; unsigned long u_count = _countof(sz_buffer);

			unsigned long n_chars = u_count;

			LSTATUS n_result = this->m_sta_bar.QueryStringValue(_T("app-ready"), sz_buffer, &n_chars);
			if (!!n_result)
				(this->m_error = dword(n_result)) = _T("The test image file name is not specified;");
			else {
				cs_file = sz_buffer;
				this->m_app_ready = TStringEx().Format (_T("%s\\%s"), this->Get_path(), (_pc_sz) cs_file);
			}
			return this->Error();
		}

		TError&  Error (void) const { return this->m_error; }

		_pc_sz   Get_path (void) const { return this->m_path; }
		err_code Set_path (void) {
			this->m_error << __METHOD__ << __s_ok;

			if (nullptr == this->m_sta_bar.m_hKey) { // tries to open required registry key;

				CString cs_key = this->Root(); cs_key += _T("\\sta-bar"); // it is supposed the path value does not end up with the backslash;
				LSTATUS n_result = this->m_sta_bar.Open(Get_router().Root(), (_pc_sz) cs_key);
				if (!!n_result)
					return this->m_error = dword(n_result);
			}

			t_char  sz_buffer[512] = {0}; unsigned long u_count = _countof(sz_buffer);

			unsigned long n_chars = u_count;

			LSTATUS n_result = this->m_sta_bar.QueryStringValue(_T("path"), sz_buffer, &n_chars);
			if (!!n_result)
				(this->m_error = dword(n_result)) = _T("Path to test images is not specified;");
			else
				this->m_path = sz_buffer;

			return this->Error();
		}

		CString  Root  (void) const {
			CString cs_root = Get_router().TestCase().Root();
			return  cs_root;
		}

	private:
		CTestCase& operator = (const CTestCase&) = delete; CTestCase& operator = (CTestCase&&) = delete;
		CRegKey  m_sta_bar;
		mutable
		CError   m_error;
		CString  m_path ;      // the path to test image location for the currently selected theme;
		CString  m_app_ready;
	};

}}}}}
using namespace ebo::boo::test::cache::_impl;
/////////////////////////////////////////////////////////////////////////////

CCacheList:: CCacheList (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CCacheList::_ctor (void) {

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_list.Print(e_print::e_all));
	_out()();
}

void CCacheList::Create (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) this->m_list.Print(e_print::e_all));

	const t_size size{16,16};
	const uint16_t n_count = 2;
	const uint16_t n_delta = 2;

	_out() += TStringEx().Format (
		_T("Input args:%ssize=[w:%u|h:%u](px)%scount=%d%sdelta=%d"), _p_new, size.cx, size.cy, _p_new, n_count, _p_new, n_delta
	);

	if (__failed(this->m_list.Create(size, n_count, n_delta)))
		_out() += this->m_list.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*after* : %s"), (_pc_sz) this->m_list.Print(e_print::e_all));

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CDataProvider:: CDataProvider (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
	ex_ui::theme::Get_current().Load(); // this is required for setting the current theme;
}

void CDataProvider::LoadFile (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CTestCase test_case;

	_out() += _T("Receiving path to test images...");
	if (__failed(test_case.Set_path())) {
		_out() += test_case.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}
	else {
		_out() += TStringEx().Format (_T("The path is set to:%s%s"), _p_new, test_case.Get_path());
	}

	_out() += _T("Receiving path to app-ready image...");
	if (__failed(test_case.SetApp_ready())) {
		_out() += test_case.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}
	else {
		_out() += TStringEx().Format (_T("The path is set to:%s%s"), _p_new, test_case.GetApp_ready());
	}

	if (__failed(this->m_prov.Load(test_case.GetApp_ready())))
		_out() += this->m_prov.Error().Print(TError::e_print::e_req);
	else
		_out() += _T("*result*: the image loaded successfully;");

	_out()();
}