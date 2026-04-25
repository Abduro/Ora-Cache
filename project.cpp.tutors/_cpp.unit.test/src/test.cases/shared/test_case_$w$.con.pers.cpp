/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2026 at 20:17:22.515, UTC+4, Batumi, Wednesday;
	This is Ebo Pack console persistent test case interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.con.pers.h"

using namespace test::win_api;
using namespace test::win_api::console;

#pragma region cls::CTstPers{}

static _pc_sz p_pers_load_pat = _T("[impt] *result*: %s; %s; visible: '%s';");
static _pc_sz p_pers_save_pat = _T("Input data: %s; %s; visible: '%s';");

err_code  CTstPers::Load (const bool _b_cls_out/* = true*/) {
	_b_cls_out;
	if (_b_cls_out)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Load())) _out() += (*this)().Error();
	else
		_out() += TString().Format(p_pers_load_pat,
			(_pc_sz)(*this)().Pin().To_str(e_print::e_req), (_pc_sz)(*this)().Pos().To_str(e_print::e_req), TString().Bool((*this)().Show().Is_visible())
		);
	return (*this)().Error();
}

err_code  CTstPers::Save (const bool _b_cls_out/* = true*/) {
	_b_cls_out;
	if (_b_cls_out)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(p_pers_save_pat,
		(_pc_sz)(*this)().Pin().To_str(e_print::e_req), (_pc_sz)(*this)().Pos().To_str(e_print::e_req), TString().Bool((*this)().Show().Is_visible())
	);
	if (__failed((*this)().Save())) _out() += (*this)().Error();

	return (*this)().Error();
}

const
TConPers& CTstPers::operator ()(void) const { return ::Get_ConPers(); }
TConPers& CTstPers::operator ()(void)       { return ::Get_ConPers(); }

#pragma endregion