/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 11-Jan-2026 at 16:13:37.087, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' shader wrapper unit test adapter interface implementation file.
*/
#include "ebo_test_$d$.shader.h"

#include "gl_procs_shader.h"
#include "shader\gl_compiler.h"
#include "shader\gl_shd_status.h"

using namespace ebo::boo::test::open_gl::draw;

using CCompiler = ex_ui::draw::open_gl::shader::CCompiler;
using CStatus = ex_ui::draw::open_gl::shader::CStatus;

#pragma region cls::c_shaders{}

c_shaders::c_shaders (const e_object _target, const bool _b_verb) : m_target(_target), m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_shaders::Create (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out()();
}

#pragma warning (disable: 4706) // assignment within conditional expression;
// or this one is also good: https://stackoverflow.com/questions/6986018/visual-studio-2010-c-suppress-c4706-warning-temporarily >> parentheses;
void c_shaders::Get_frag (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CDevCtx dev_ctx;
	CShaders shaders;

	CCompiler compiler;

	bool b_supported = false; // the flag of compiler support;

	if (__failed(dev_ctx.Create())) { _out()(); return; }

	$Fragment& $_frag = shaders.Fragment();

	if (false){}
	else if (__failed($_frag.Create())) {/*nothig for test*/}
	else if (__failed($_frag.Src().Cfg().Path(TPipe::To_str(this->Target()), $_frag.Type().Get()))) {/*nothig for test*/}
	else if (__failed($_frag.Src().Set())) {/*nothig for test*/}
	else {
		if (false) {}
		else if (b_supported = compiler.Is_supported()) { _out() += _T("shader compiler support is: 'true';"); }
		else if (compiler.Error()) { _out() += compiler.Error().Print(TError::e_print::e_req); }
	}

	if (b_supported) {
		compiler << $_frag.Id();
		if (false) {}
		else if (__failed(compiler.Compile())) { _out() += compiler.Error().Print(TError::e_print::e_req); }
		else {
			CStatus $_status;
			$_status << $_frag.Id();
			const bool b_compiled = $_status.Is_compiled();
			if ($_status.Error()) { _out() += $_status.Error().Print(TError::e_print::e_req); }
			else _out() += TString().Format(
				_T("shader '%s' (id = %u) compiled status: '%s';"), (_pc_sz) procs::$_type_to_str($_frag.Type().Get()), $_frag.Id(), TString().Bool(b_compiled)
			);

			if (__failed(compiler.Release())) { _out() += compiler.Error().Print(TError::e_print::e_req); }
		}
	}

	$_frag.Delete(); // deletes the shader in any case;

	dev_ctx.Delete();

	_out()();
}
#pragma warning (default: 4706)

void c_shaders::Get_vert (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();
}

e_object c_shaders::Target (void) const { return this->m_target; }

#pragma endregion