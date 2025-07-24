/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jul-2025 at 12:18:03.786, UTC+4, Batumi, Thursday;
	This is Ebo Pack user control base image list  unit test interface implementation file;
*/
#include "ebo_test_$u$.ctl.image.h"
#include "ebo_test_$d$.theme.case.h"

using namespace ebo::boo::test::ctl;
using namespace ebo::boo::test::cases;

using TResult   = ex_ui::draw::images::CResult;
using TDataProv = ex_ui::draw::images::CDataProvider;

/////////////////////////////////////////////////////////////////////////////

CImages:: CImages (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CImages::Set (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("*before*: %s"), (_pc_sz) this->m_images.List().Print(e_print::e_all));

	CTestCase_0 case_0;

	_out() += _T("Receiving path to test images...");
	if (__failed(case_0.Set_path())) {
		_out() += case_0.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}

	CString cs_image_0 = case_0.Get_path(CTestCase_0::e_images::e_no_0);

	_out() += TString().Format(_T("The path to the image file: %s%s"), _p_new_line, (_pc_sz) cs_image_0);

	TDataProv provider;

	if (__failed(provider.Load((_pc_sz) cs_image_0))) {
		_out() += provider.Error().Print(TError::e_print::e_req); _out()(); return;
	}
	
	_out() += _T("*result*: the bitmap is created successfully;");
	_out() += provider.Result().Print(e_print::e_all);

	const t_size& size_ = provider.Result().Size();

	_out() += TString().Format(_T("Creating the image list of frame size: cx:%d|cy:%d (px):"), size_.cx, size_.cy);

	if (__failed(this->m_images.List().Create(size_))) {
		_out() += this->m_images.List().Error().Print(TError::e_print::e_req); _out()(); return;
	}
	_out() +=  this->m_images.List().Print(e_print::e_all);
	_out() +=  _T("Adding the bitmap to control image list:");

	if (__failed(this->m_images.List().Append(provider.Result().Handle()))) {
		_out() += m_images.List().Error().Print(TError::e_print::e_req);
	}
	else {
		_out() += TString().Format(_T("*after *: %s"), (_pc_sz) this->m_images.List().Print(e_print::e_all));
	}
	
	_out()();

}