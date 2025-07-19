/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Jul-2025 at 21:58:47.468, UTC+4, Batumi, Thursday;
	This is Ebo Pack image stream wrapper unit test interface implementation file; 
*/
#include "ebo_test_$d$.img.stream.h"
#if (0)
#include "uix.theme.named.h"
#include "uix.theme.reg.h"
#else
#include "ebo_test_$d$.theme.case.h"
#endif
using namespace ebo::boo::test::images;
#if (0)
using namespace ex_ui::theme;
using namespace ex_ui::theme::storage;
#else
using namespace ebo::boo::test::cases;
#endif
/////////////////////////////////////////////////////////////////////////////

CStream:: CStream (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CStream::_ctor (void) {

	_out() += TLog_Acc::e_emp_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_stream.Print(e_print::e_all));
	_out()();

}

void CStream::Load_image (void) {

	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) this->m_stream.Print(e_print::e_all));
	
	CTestCase_0 case_0;
	if (__failed(case_0.Set_path())) {
		_out() += case_0.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}

	CString cs_image_0 = case_0.Get_path(CTestCase_0::e_images::e_no_0);

	if (cs_image_0.IsEmpty()) {
		_out() += case_0.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}

	_out() += _T("Creating the stream from the file...");
	_out() += TString().Format(_T("The path to image file: %s%s"), _p_new_line, (_pc_sz) cs_image_0);

	if (__failed(this->m_stream.Create((_pc_sz) cs_image_0))) {
		_out() += this->m_stream.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}
	
	_out() += this->m_stream.Print(e_print::e_all);

	_out() += _T("Destroying the stream...");
	if (__failed(this->m_stream.Destroy()))
		_out() += this->m_stream.Error().Print(TError::e_print::e_req);
	else
		_out() += _T("The stream has been destroyed successfully;");
	
	_out()();
}

/////////////////////////////////////////////////////////////////////////////