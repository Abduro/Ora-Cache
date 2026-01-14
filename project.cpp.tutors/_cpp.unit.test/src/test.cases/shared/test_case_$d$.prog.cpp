/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:39:16.076, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL shader program wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.prog.h"

using namespace ebo::boo::test::open_gl::draw;

using COpts = CProg::COpts;

#pragma region cls::COpts{}

COpts::COpts (void) : m_b_opts{false} {}

bool COpts::Link (void) const { return this->m_b_opts[e_opts::e_link]; }
bool COpts::Link (const bool _opt) {
	_opt;
	const bool b_changed = this->Link() != _opt; if (b_changed) this->m_b_opts[e_opts::e_link] = _opt; 
	return b_changed;
}
bool COpts::UseShaders (void) const { return this->m_b_opts[e_opts::e_use_$]; }
bool COpts::UseShaders (const bool _opt) {
	_opt;
	const bool b_changed = this->UseShaders() != _opt; if (b_changed) this->m_b_opts[e_opts::e_use_$] = _opt; 
	return b_changed;
}

#pragma endregion
#pragma region cls::CProg{}

CProg::CProg (const e_object _target) : TPipe(_target) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code CProg::Attach (const CShader& _shader) {
	_shader;
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TPipe::Target());

	// for test purposes the static shader attachment procedure is used; it is assumed that shaders and program belong to global renderer;
	if (__failed(T$Cache::Attach(_shader.Id(), prog.Id(), this->m_error))) {
		_out() += this->Error().Print(TError::e_print::e_req);
	}

	return this->Error();
}

err_code CProg::Detach (const CShader& _shader) {
	_shader;
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TPipe::Target());

	// for test purposes the static shader detachment procedure is used; it is assumed that shaders and program belong to global renderer;
	if (__failed(T$Cache::Detach(_shader.Id(), prog.Id(), this->m_error))) {
		_out() += this->Error().Print(TError::e_print::e_req);
	}

	return this->Error();
}

err_code CProg::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TPipe::Target());

	if (false){}
	else if (__failed(prog.Create())) {
		_out() += prog.Error().Print(TError::e_print::e_req); return this->m_error = prog.Error(); }
	else if (this->Opts().UseShaders() == false)
		return this->Error();
	else {}
#if (0)
	shader::CFragment& $frag = prog.Shaders().Fragment();
	shader::CVertex& $vert = prog.Shaders().Vertex();

	// it is expected the 'compile' option is on;
	if (__failed(C$Base::Create($frag, $frag.Type().Get(), this->m_error))) { _out() +=this->Error().Print(TError::e_print::e_req); }
	if (__failed(C$Base::Create($vert, $vert.Type().Get(), this->m_error))) { _out() +=this->Error().Print(TError::e_print::e_req); }
#else
	if ((this->m_error = C$_enum().Create())) return this->Error(); 
#endif
	if (false == this->Opts().Link())
		return this->Error();

	this->Link();

	return this->Error();
}

err_code CProg::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TPipe::Target());

	if (true == this->Opts().UseShaders()) {

		shader::CFragment& $frag = prog.Shaders().Fragment();
		shader::CVertex& $vert = prog.Shaders().Vertex();

		this->Detach($frag);
		this->Detach($vert);
#if (0)
		C$Base::Delete($frag, this->m_error); // if the error occurs, shader base class makes the error trace;
		C$Base::Delete($vert, this->m_error); // if the error occurs, shader base class makes the error trace;
#else
		C$_enum().Delete(); // if the error occurs, shader enumerator class makes the error trace;
#endif
	}

	if (__failed(prog.Delete())) {
		this->m_error = prog.Error();
		_out() += prog.Error().Print(TError::e_print::e_req);
	}
	return this->Error();
}

TError&  CProg::Error (void) const { return this->m_error; }

uint32_t CProg::GetId (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("cls::[%s::%s].%s();"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TPipe::Target());

	if (prog.Error()) this->m_error = prog.Error();

	return prog.Id().Get();
}

err_code CProg::Link (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TPipe::Target());
	// tries to attach the required shaders for linking this program; it is assumed the shaders are created;
	// to-do: working with shaders must be moved to separate class/procedure;
	if (this->Opts().UseShaders()) {

		shader::CFragment& $frag = prog.Shaders().Fragment();
		shader::CVertex& $vert = prog.Shaders().Vertex();

		if (__failed(this->Attach($frag)) || 
		    __failed(this->Attach($vert))) { _out() +=this->Error().Print(TError::e_print::e_req); }

		if (this->Error()) return this->Error(); // there is no sense to link the program because one of the shaders is not attached successfully;
#if (0)
		if (__failed(C$Base::Compile($frag, TPipe::Target(), this->m_error)) ||
		    __failed(C$Base::Compile($vert, TPipe::Target(), this->m_error))) { _out() +=this->Error().Print(TError::e_print::e_req); }
#else
		this->m_error = C$_enum().Compile();
#endif
		if (this->Error()) return this->Error(); // there is no		sense to link the program because one of the shaders is not compiled;
	}

	if (__failed(CProgram::Link(prog.Id(), this->m_error))) { _out() += this->Error().Print(TError::e_print::e_req); }

	return this->Error();
}

const
COpts&   CProg::Opts (void) const { return this->m_opts; }
COpts&   CProg::Opts (void)       { return this->m_opts; }

#pragma endregion