/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 11-Jan-2026 at 16:13:37.087, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' shader wrapper unit test adapter interface implementation file.
*/
#include "ebo_test_$d$.shader.h"

using namespace ebo::boo::test::open_gl::draw;

using COpts = c_shaders::COpts;

#pragma region cls::COpts{}

COpts::COpts (void) : m_b_cmpl(true) {}

bool COpts::Compile (void) const { return this->m_b_cmpl; }
bool COpts::Compile (const bool _opt) {
	_opt;
	const bool b_changed = this->Compile() != _opt; if (b_changed) this->m_b_cmpl = _opt; 
	return b_changed;
}

#pragma endregion
#pragma region cls::c_shaders{}

c_shaders::c_shaders (const e_object _target, const bool _b_verb) : m_target(_target), m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_shaders::Get_frag (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CDevCtx dev_ctx;

	if (__failed(dev_ctx.Create())) {
		_out() += dev_ctx.Error().Print(TError::e_print::e_req); _out()(); return;
	}

	C$Frag $_frag;

	$_frag.Create(); if (this->Opts().Compile()) $_frag.Compile();
	$_frag.Delete();

	dev_ctx.Delete(); // the error code of this operation is not interested in this procedure context;

	_out()();
}

void c_shaders::Get_vert (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CDevCtx dev_ctx;

	if (__failed(dev_ctx.Create())) {
		_out() += dev_ctx.Error().Print(TError::e_print::e_req); _out()(); return;
	}

	C$Vert $_vert;

	$_vert.Create(); if (this->Opts().Compile()) $_vert.Compile();
	$_vert.Delete();

	dev_ctx.Delete(); // the error code of this operation is not interested in this procedure context;

	_out()();
}
const
COpts&   c_shaders::Opts (void) const { return this->m_opts; }
COpts&   c_shaders::Opts (void)       { return this->m_opts; }

e_object c_shaders::Target (void) const { return this->m_target; }

#pragma endregion