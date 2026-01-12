/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:51:44.122, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL shaders' wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.shader.h"

#include "shader\gl_compiler.h"
#include "shader\gl_shd_status.h"

using namespace ebo::boo::test::open_gl::draw;

using CCompiler = ex_ui::draw::open_gl::shader::CCompiler;
using CStatus = ex_ui::draw::open_gl::shader::CStatus;

#pragma region cls::C$Base{}

C$Base::C$Base (const e_object _target) : TPipe(_target) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code C$Base::Compile(void) {
	this->m_error <<__METHOD__<<__s_ok; return C$Base::Compile(this->Ref(), TPipe::Target(), this->m_error);
}

err_code C$Base::Create (const $Type _type) {
	this->m_error <<__METHOD__<<__s_ok; return C$Base::Create(this->Ref(), _type, this->m_error);
}

//#pragma warning (disable: 4706) // assignment within conditional expression;
// https://stackoverflow.com/questions/6986018/visual-studio-2010-c-suppress-c4706-warning-temporarily >> parentheses ;)
err_code C$Base::Compile (CShader& _shader, const e_object _target, CError& _err) {
	_shader; _target; _err;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCompiler compiler;
	CShader& $base = _shader;

	static _pc_sz pc_sz_pat = _T("Shader compiler support is: '%s';");

	bool b_supported = compiler.Is_supported();
	if (compiler.Error()) {
		_err = compiler.Error();
		_out() += _err.Print(TError::e_print::e_req); return _err;
	}
	else if (false == b_supported) {
		_err << (err_code)TErrCodes::eExecute::eEnviron = TString().Format(pc_sz_pat, _T("false")); return _err;
	}
	else if (__failed($base.Src().Cfg().Path(TPipe::To_str(_target), $base.Type().Get()))) {
		_err = $base.Src().Cfg().Error();
		_out() += _err.Print(TError::e_print::e_req); return _err;
	}
	else {}

	_out() += TString().Format(pc_sz_pat, _T("true"));
	compiler << $base.Id();
	if (false) {}
	else if (__failed(compiler.Compile())) { _err = compiler.Error(); _out() += _err.Print(TError::e_print::e_req); }
	else {
		CStatus $_status($base.Id());

		const bool b_compiled = $_status.Is_compiled();

		if ($_status.Error()) { _out() += $_status.Error().Print(TError::e_print::e_req); }
		else _out() += TString().Format(
			_T("Shader '%s' (id = %u) compiled status: '%s';"), (_pc_sz) procs::$_type_to_str((uint32_t)$base.Type()), $base.Id(), TString().Bool(b_compiled)
		);

		if (__failed(compiler.Release())) { _out() += compiler.Error().Print(TError::e_print::e_req); } // this error is not traced;
	}

	return _err;
}
//#pragma warning (default: 4706)
err_code C$Base::Create (CShader& _shader, const $Type _type, CError& _err) {
	_shader; _type; _err;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
#if (0) // must be created outside of this procedure;
	CDevCtx dev_ctx;

	if (__failed(dev_ctx.Create())) {
		_out() += dev_ctx.Error().Print(TError::e_print::e_req);
		return _err = dev_ctx.Error();
	}
#endif
	CShader& $base = _shader;

	if (false){}
	else if (__failed($base.Create(_type))) {/*nothig for test*/}
#if (0)
	dev_ctx.Delete(); // the error code of this operation is not interested in this procedure context;
#endif
	return _err;
}

err_code C$Base::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok; return C$Base::Delete(this->Ref(), this->m_error);
}

err_code C$Base::Delete (CShader& _shader, CError& _err) {
	_shader; _err;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed(_shader.Delete())) {
		_err = _shader.Error(); _out() += _err.Print(TError::e_print::e_req);
	}

	return _err;
}

TError&  C$Base::Error (void) const { return this->m_error; }

const
CShader& C$Base::Ref (void) const { return this->m_shader; }
CShader& C$Base::Ref (void)       { return this->m_shader; }

#pragma endregion
#pragma region cls::C$Frag{}

C$Frag::C$Frag (const e_object _target) : C$Base(_target) { C$Base::m_error >>__CLASS__; C$Base::Ref().Type().Set($Type::e_fragment); }

err_code C$Frag::Create (void) {
	C$Base::m_error <<__METHOD__<<__s_ok;
	return C$Base::Create(C$Base::Ref(), C$Base::Ref().Type().Get(), C$Base::m_error);
}

#pragma endregion
#pragma region cls::C$Vert{}

C$Vert::C$Vert (const e_object _target) : C$Base(_target) { C$Base::m_error >>__CLASS__; C$Base::Ref().Type().Set($Type::e_vertex); }

err_code C$Vert::Create (void) {
	C$Base::m_error <<__METHOD__<<__s_ok;
	return C$Base::Create(C$Base::Ref(), C$Base::Ref().Type().Get(), C$Base::m_error);
}

#pragma endregion
#pragma region cls::CShaders{}

CShaders::CShaders (const e_object _target) : TBase(_target) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code  CShaders::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TBase::Target());

	if (__failed(prog.Shaders().Create()))
		this->m_error = prog.Shaders().Error();

	return this->Error();
}

const
$Fragment& CShaders::Fragment (void) const { return ::Get_renderer().Scene().Progs().Get(TBase::Target()).Shaders().Fragment(); }
$Fragment& CShaders::Fragment (void)       { return ::Get_renderer().Scene().Progs().Get(TBase::Target()).Shaders().Fragment(); }

TError& CShaders::Error (void) const { return this->m_error; }
const
$Vertex& CShaders::Vertex (void) const { return ::Get_renderer().Scene().Progs().Get(TBase::Target()).Shaders().Vertex(); }
$Vertex& CShaders::Vertex (void)       { return ::Get_renderer().Scene().Progs().Get(TBase::Target()).Shaders().Vertex(); }

#pragma endregion