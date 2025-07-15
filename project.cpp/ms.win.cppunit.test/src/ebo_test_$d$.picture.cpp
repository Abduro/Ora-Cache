/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Jul-2025 at 14:44:36.220, UTC+4, Batumi, Thursday;
	This is Ebo Pack component object picture wrapper unit test definition file; 
*/
#include "ebo_test_$d$.picture.h"

using namespace ebo::boo::test::images;

/////////////////////////////////////////////////////////////////////////////

CPicture:: CPicture (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CPicture::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_picture.Print(e_print::e_all));
	_out()();

}

void CPicture::Load_file (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) this->m_picture.Print(e_print::e_all));

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

	_out() += TStringEx().Format(_T("The path to image file: %s%s"), _p_new_line, (_pc_sz) cs_image_0);

	if (__failed(this->m_picture.Load((_pc_sz) cs_image_0)))
		_out() += this->m_picture.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*after *: %s"), (_pc_sz) this->m_picture.Print(e_print::e_all));

	_out()();
}