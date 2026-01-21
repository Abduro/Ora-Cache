/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 19-Jan-2026 at 23:24:33.762, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL 2d shape wrapper unit test adapter interface implementation file.
*/
#include "ebo_test_$d$.shape.2d.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::c_tria_2d{}

c_tria_2d::c_tria_2d (void) : m_pipe(e_object::e_tria) {

	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");
	_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str((*this)()));
}

void c_tria_2d::Create_n_Delete (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	C3angle tria;

	tria.Create(); // required error trace is made by the method being called itself;
	tria.Delete(); // required error trace is made by the method being called itself;

	_out()();
}

void c_tria_2d::Draw (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	C3angle tria;

	tria.Draw();
	tria.Delete();

	_out()();
}

const
TPipe& c_tria_2d::operator ()(void) const { return this->m_pipe; }
TPipe& c_tria_2d::operator ()(void)       { return this->m_pipe; }

#pragma endregion