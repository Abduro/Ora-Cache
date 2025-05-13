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