/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2026 at 20:27:37.278, UTC+4, Batumi, Wednesday;
	This is Ebo Pack console persistency unit test adapter interface implementation file.
*/
#include "test_adap_$w$.con.pers.h"

using namespace test::win_api::console;

void c_pers::Load (void) {

	CTstPers().Load(); _out()();
}

void c_pers::Save (void) {

	CTstPers pers;

	pers.Load(false);
	const bool b_pinned_set = !pers().Pin().Is_pinned(); // inverts the pin state;
	_out() += TString().Format(_T("*before* save: pinned = '%s'"), TString().Bool(b_pinned_set));

	pers.Save(false);
	pers.Load(false);
	const bool b_pinned_get =  pers().Pin().Is_pinned();
	_out() += TString().Format(_T("*after* load: pinned = '%s'"), TString().Bool(b_pinned_get));

	_out()();
}