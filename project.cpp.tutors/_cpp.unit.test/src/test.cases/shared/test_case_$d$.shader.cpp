/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:51:44.122, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL shaders' wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.shader.h"

#include "shader\gl_compiler.h"
#include "shader\gl_shd_status.h"
#include "shader\gl_shd_type.h"

#include "sys.registry.h"

using namespace ebo::boo::test::open_gl::draw;

using CCompiler = ex_ui::draw::open_gl::shader::CCompiler;
using CStatus = ex_ui::draw::open_gl::shader::CStatus;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace _impl {

	class CReg_helper {
	        CReg_helper (const CReg_helper&) = delete; CReg_helper (CReg_helper&&) = delete;
	public: CReg_helper (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; } ~CReg_helper (void) = default;

		TError& Error (void) const { return this->m_error; }
		CString Path (const $Type _type) {
			_type;
			this->m_error <<__METHOD__<<__s_ok;

			using e_types = shared::sys_core::storage::route::CShaders::e_types;
			e_types e_shader = e_types::e__undef;

			switch (_type) {
			case $Type::e_fragment: e_shader = e_types::e_fragment; break;
			case $Type::e_vertex  : e_shader = e_types::e_vertex; break;
			default:
				this->m_error <<__e_inv_arg = TString().Format(_T("Unsupported shader type '%s'"), (_pc_sz) shader::CType::To_str((uint32_t)_type));
			}

			CString $_path;
			CString $_name = ::Get_reg_router().Shaders().Name(e_shader);

			TRegKeyEx reg_key;
			$_path = reg_key.Value().GetString((_pc_sz) TReg_test_case::Key_path(0), (_pc_sz) $_name);
			if (reg_key.Error())
				this->m_error = reg_key.Error();

			return $_path;
		}

	private:
		CReg_helper& operator = (const CReg_helper&) = delete; CReg_helper& operator = (CReg_helper&&) = delete;
		CError m_error;
	};

}}}}}

#pragma region cls::C$Base{}

C$Base::C$Base (const e_object _target) : TPipe(_target) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code C$Base::Compile(void) {
	this->m_error <<__METHOD__<<__s_ok; return C$Base::Compile(this->Ref(), TPipe::Target(), this->m_error);
}

//#pragma warning (disable: 4706) // assignment within conditional expression;
// https://stackoverflow.com/questions/6986018/visual-studio-2010-c-suppress-c4706-warning-temporarily >> parentheses ;)
err_code C$Base::Compile (CShader& _shader, const e_object _target, CError& _err) {
	_shader; _target; _err;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s() <static>:"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCompiler compiler;
	CShader& $base = _shader;

	static _pc_sz pc_sz_pat_not_supp = _T("Shader compiler support is: '%s';");

	bool b_supported = compiler.Is_supported();
	if (compiler.Error()) {
		_err = compiler.Error();
		_out()(_err); return _err;
	}
	else if (false == b_supported) {
		_err << (err_code)TErrCodes::eExecute::eEnviron = TString().Format(pc_sz_pat_not_supp, _T("false")); return _err;
	}
#if (0) // this is not suitable for test cases, because it is required to load shader source code file independently from the target object type;
	else if (__failed($base.Src().Cfg().Path(TPipe::To_str(_target), $base.Type().Get()))) { // sets source code file path that is read from the registry;
		_err = $base.Src().Cfg().Error();
		_out()(_err); return _err;
	}
#else
	else if (__failed($base.Src().Cfg().Path(_impl::CReg_helper().Path(_shader.Type().Get())))) {
		_err = $base.Src().Cfg().Error();
		_out()(_err); return _err;
	}
#endif
	else if (__failed($base.Src().Set())) { // loads the source code file to the shader code buffer;
		_err = $base.Src().Error();
		_out()(_err); return _err;
	}
	else {}

	_out() += TString().Format(pc_sz_pat_not_supp, _T("true"));

	compiler << $base.Id();
	if (false) {}
	else if (__failed(compiler.Compile())) { _err = compiler.Error(); _out()(_err); }
	else {
		CStatus $_status($base.Id());

		const bool b_compiled = $_status.Is_compiled();

		if ($_status.Error()) { _out() += $_status.Error().Print(TError::e_print::e_req); }
		else {
			static _pc_sz pc_sz_pat_stat = _T("Shader '%s' (id = 0x%04x) compiled status: '%s';");
			_out() += TString().Format(pc_sz_pat_stat, (_pc_sz) procs::$_type_to_str((uint32_t)$base.Type()), $base.Id(), TString().Bool(b_compiled));
			_out() += _T("Shader compiler log:");
			_out() += compiler.Log().Get();
		}
		if (__failed(compiler.Release())) { _out()(compiler.Error()); } // this error is not traced;
	}

	return _err;
}
//#pragma warning (default: 4706)

err_code C$Base::Create (const $Type _type) {
	this->m_error <<__METHOD__<<__s_ok; return C$Base::Create(this->Ref(), _type, this->m_error);
}
err_code C$Base::Create (CShader& _shader, const $Type _type, CError& _err) {
	_shader; _type; _err;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
#if (0) // must be created outside of this procedure;
	CDevCtx dev_ctx;

	if (__failed(dev_ctx.Create())) {
		_out()(dev_ctx.Error());
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
		_err = _shader.Error(); _out()(_err);
	}

	return _err;
}

TError&  C$Base::Error (void) const { return this->m_error; }

const
CShader& C$Base::Ref (void) const { return this->m_shader; }
CShader& C$Base::Ref (void)       { return this->m_shader; }

const
TPipe& C$Base::operator ()(void) const { return (TPipe&)*this; }
TPipe& C$Base::operator ()(void)       { return (TPipe&)*this; }

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
#pragma region cls::C$_enum{}

C$_enum::C$_enum (const e_object _target) : TPipe(_target) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code  C$_enum::Compile(void) {
	this->m_error <<__METHOD__<<__s_ok;

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TPipe::Target());

	shader::CFragment& $frag = prog.Shaders().Fragment();
	shader::CVertex& $vert = prog.Shaders().Vertex();

	if (__failed(C$Base::Compile($frag, TPipe::Target(), this->m_error)) ||
	    __failed(C$Base::Compile($vert, TPipe::Target(), this->m_error))) { _out()(this->Error()); }

	return this->Error();
}

err_code  C$_enum::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TPipe::Target());

#if (0) // the shaders for test cases are loaded independently from target object type;
	if (__failed(prog.Shaders().Create()))
		this->m_error = prog.Shaders().Error();
#else
	shader::CFragment& $frag = prog.Shaders().Fragment();
	shader::CVertex& $vert = prog.Shaders().Vertex();
	// the sequence of shader creation is not good approach: if the first shader creation fails the error will be overwritten by the creation of the next shader;
	if (__failed(C$Base::Create($frag, $frag.Type().Get(), this->m_error))) { _out()(this->Error()); }
	if (__failed(C$Base::Create($vert, $vert.Type().Get(), this->m_error))) { _out()(this->Error()); }
#endif
	return this->Error();
}

err_code  C$_enum::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TPipe::Target());

	shader::CFragment& $frag = prog.Shaders().Fragment();
	shader::CVertex& $vert = prog.Shaders().Vertex();

	C$Base::Delete($frag, this->m_error); // if the error occurs, shader base class makes the error trace;
	C$Base::Delete($vert, this->m_error); // if the error occurs, shader base class makes the error trace;

	return this->Error();
}

const
$Fragment& C$_enum::Fragment (void) const { return ::Get_renderer().Scene().Progs().Get(TPipe::Target()).Shaders().Fragment(); }
$Fragment& C$_enum::Fragment (void)       { return ::Get_renderer().Scene().Progs().Get(TPipe::Target()).Shaders().Fragment(); }

TError& C$_enum::Error (void) const { return this->m_error; }
const
$Vertex& C$_enum::Vertex (void) const { return ::Get_renderer().Scene().Progs().Get(TPipe::Target()).Shaders().Vertex(); }
$Vertex& C$_enum::Vertex (void)       { return ::Get_renderer().Scene().Progs().Get(TPipe::Target()).Shaders().Vertex(); }

#pragma endregion