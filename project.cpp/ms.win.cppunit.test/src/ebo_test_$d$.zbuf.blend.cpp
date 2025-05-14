/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-May-2025 at 17:48:37.252, UTC+4, Batumi, Tuesday;
	This is Ebo Pack WinAPI GDI in-memory draw blend renderer lib unit test interface implementation file; 
*/
#include "ebo_test_$d$.zbuf.blend.h"

using namespace ebo::boo::test::draw;

CBlend_Wrap:: CBlend_Wrap (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CBlend_Wrap::_ctor (void) {

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_bl_wrap.Print(e_print::e_all));
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CIn_Out:: CIn_Out (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CIn_Out::_ctor (void) {

	if (this->m_in_out.Is_valid())
	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_in_out.Print(e_print::e_all));
	else
	_out() += this->m_in_out.Error().Print(TError::e_print::e_req);
	_out()();
}

void CIn_Out::Set (void) {

	CFake_Wnd fake_wnd;
	if (fake_wnd.Error()) {
		_out() += fake_wnd.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	this->m_in_out.Ctx(fake_wnd);
	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_in_out.Print(e_print::e_all));

	if (this->m_in_out.Is_valid() == false)
		_out() += this->m_in_out.Error().Print(TError::e_print::e_req);

	this->m_in_out.Position().Size().Set(256, 256);

	if (this->m_in_out.Is_valid() == false)
		_out() += this->m_in_out.Error().Print(TError::e_print::e_req);

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CIn_Src:: CIn_Src (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CIn_Src::_ctor (void) {
	static bool b_is_called = false;

	if (this->m_b_verb || b_is_called) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
	else 
		b_is_called = true;

	if (this->m_in_src.Is_valid())
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_in_src.Print(e_print::e_all));
	else
		_out() += this->m_in_src.Error().Print(TError::e_print::e_all);
	_out()();
}