/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface implementation file; 
*/
#include "ebo_test_$m$.matrix.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

c_mat2x2:: c_mat2x2 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_mat2x2::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();

}