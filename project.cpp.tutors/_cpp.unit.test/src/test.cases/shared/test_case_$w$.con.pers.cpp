/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2026 at 20:17:22.515, UTC+4, Batumi, Wednesday;
	This is Ebo Pack console persistent test case interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.con.pers.h"

using namespace test::win_api::console;

#pragma region cls::CTstPers{}

err_code  CTstPers::Load (const bool _b_cls_out/* = true*/) {
	_b_cls_out;
	if (_b_cls_out)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Load())) _out() += (*this)().Error();
	else
		_out() += TString().Format(_T("[impt] *result*: %s; %s;"),
			(_pc_sz)(*this)().Pin().To_str(e_print::e_req), (_pc_sz)(*this)().Pos().To_str(e_print::e_req)
		);
	return (*this)().Error();
}

err_code  CTstPers::Save (const bool _b_cls_out/* = true*/) {
	_b_cls_out;
	if (_b_cls_out)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Input data: %s; %s"),
		(_pc_sz)(*this)().Pin().To_str(e_print::e_req), (_pc_sz)(*this)().Pos().To_str(e_print::e_req)
	);
	if (__failed((*this)().Save())) _out() += (*this)().Error();

	return (*this)().Error();
}

const
TConPers& CTstPers::operator ()(void) const { return ::Get_ConPers(); }
TConPers& CTstPers::operator ()(void)       { return ::Get_ConPers(); }

#pragma endregion