/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jul-2025 at 13:15:42.063, UTC+4, Batumi, Friday;
	This is Ebo Pack custom image load and draw helpers' interface implementation file; 
*/
#include "ebo_test_$d$.image.case.h"

using namespace ebo::boo::test::cases;
using namespace ex_ui::draw::images;

using CDataProv = CDataProvider;

/////////////////////////////////////////////////////////////////////////////

CTestCase_01::CTestCase_01 (void) {
	if (false == true) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
	TBase::m_error >>__CLASS__;
}

err_code CTestCase_01::Create_list(const t_size& _size, TImgList& _result) const {
	_size; _result;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (_result.Is_valid())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists;

	if (__failed(_result.Create(_size))) {
		TBase::m_error = _result.Error();
	}

	return TBase::Error();
}

err_code CTestCase_01::Load_image (const e_images _e_image, TResult& _result) const {
	_e_image; _result;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (_result.Is_valid())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists;

	CTestCase_0 case_0;

	_out() += _T("Receiving path to test images...");
	if (__failed(case_0.Set_path())) {
		_out() += case_0.Error().Print(TError::e_print::e_req);
		_out()(); return case_0.Error();
	}

	CString cs_image_0 = case_0.Get_path(CTestCase_0::e_images::e_no_0);

	_out() += TString().Format(_T("The path to the image file: %s%s"), _p_new_line, (_pc_sz) cs_image_0);

	CDataProv provider;

	if (__failed(provider.Load((_pc_sz) cs_image_0)))
		_out() += provider.Error().Print(TError::e_print::e_req);
	else {
		_out() += _T("*result*: the bitmap is created successfully;");
		_out() += provider.Result().Print(e_print::e_all);
	}

	HBitmap bitmap = const_cast<CResult&>(provider.Result()).Detach();

	_result.Attach(bitmap);                      // this not good approach, but it is applicable for now;
	_result.Size() = provider.Result().Size();   // if attaching the bitmap occurs while the size is not passed to the attach method?

	return TBase::Error();
}