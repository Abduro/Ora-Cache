/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2025 at 03:01:10.215, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shader window interface implementation file;
*/
#include "open_gl_tutor.2.wnd.h"
#include "open_gl_tutor.2.res.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

#include "shader\gl_compiler.h"
#include "gl_program.h"
#include "program\gl_prog_linker.h"
#include "program\gl_prog_status.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

shader::CWnd:: CWnd (void) : TBase(), m_ctx_dev(m_fak_wnd) { TBase::m_error >>__CLASS__;

	if (m_fak_wnd.Is_valid() == false) {
		TBase::m_error = m_fak_wnd.Error();
		__trace_err_2(_T("%s\n"), (_pc_sz)TBase::m_error.Print(TError::e_req));
		__trace::Out_2(__trace::e_err, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _T("%s\n"), (_pc_sz)TBase::m_error.Print(TError::e_req));
	}

	if (m_ctx_dev.Error()) {
		TBase::m_error = m_ctx_dev.Error();
		__trace_err_2(_T("%s\n"), (_pc_sz)TBase::m_error.Print(TError::e_req));
	}

	if (__failed(CShader::Cache().Get_all())) {
		TBase::m_error = CShader::Cache().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz)TBase::m_error.Print(TError::e_req));
	}
}
shader::CWnd::~CWnd (void) { // parent class object will destroy window created automatically on its (parent) destruction;
	if (true == this->Shader_frag().Is_valid()) this->Shader_frag().Destroy();
	if (true == this->Shader_vert().Is_valid()) this->Shader_vert().Destroy();

	m_ctx_dev.Destroy();
}

err_code shader::CWnd::Create (const HWND _h_parent, const t_rect& _rc_wnd_pos, const bool _b_visible) {
	_h_parent; _rc_wnd_pos; _b_visible;
	TBase::m_error << __METHOD__ << __s_ok;

	if (TBase::Is_valid())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists;

	static _pc_sz p_cls_name = _T("__open_gl_shader_wnd");

	CWndCls wnd_cls;

	if (__failed(wnd_cls.Register(p_cls_name))) {
		__trace_err_2(_T("%s\n"), (_pc_sz) wnd_cls.Error().Print(TError::e_req));
		return TBase::m_error = wnd_cls.Error();
	}

	TBase::Styles().Default_for_kid();

	if (__failed((*this)().Create(
		p_cls_name, TString().Format(_T("cls::[%s:%s]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), _rc_wnd_pos, _b_visible, _h_parent
	))) {
	}/* else if (__failed(TBase::Ctx().Create(*this, 4, 6))) {
		__trace_err_2(_T("%s\n"), (_pc_sz) TBase::Ctx().Error()().Print(TError::e_req));
	}*/

	return (*this)().Error();
}

const
shader::CFragment& shader::CWnd::Shader_frag (void) const { return this->m_frag_shader; }
shader::CFragment& shader::CWnd::Shader_frag (void)       { return this->m_frag_shader; }

const
shader::CVertex& shader::CWnd::Shader_vert (void) const { return this->m_vert_shader; }
shader::CVertex& shader::CWnd::Shader_vert (void)       { return this->m_vert_shader; }

err_code shader::CWnd::PostCreate (void) {
	TBase::m_error << __METHOD__ << __s_ok;
#if (0)
	if (__failed(TBase::PostCreate()))
		return TBase::Error();
#else
	TFakeWnd wnd; // message-only window (aka fake) is created in its constructor;
	if (wnd.Is_valid() == false) {
		return this->m_error = wnd.Error();
	}

	context::CDevice ctx_dev(wnd);
	if (ctx_dev.Error()) {
		return this->m_error = ctx_dev.Error();
	}
#endif
	shader::CCompiler cmpl;
	shader::CStatus $_status;

	if (false == cmpl.Is_supported()) {
		return TBase::m_error = cmpl.Error()();
	}
	else
		__trace_warn_2(_T("%s\n"), _T("Shader compiler is supported;"));

	if (false == this->Shader_frag().Is_valid()) {
		if (__failed(this->Shader_frag().Create()))
			return TBase::m_error = this->Shader_frag().Error();
	}

	if (false == this->Shader_vert().Is_valid()) {
		if (__failed(this->Shader_vert().Create()))
			return TBase::m_error = this->Shader_vert().Error();
	}

	static _pc_sz pc_sz_pat_src = _T("Load source code to '%s' shader succeeded;\n");

	if (__failed(this->Shader_frag().Src().Set(IDS_TUTOR_2_SHADER_FRAG_0, this->Shader_frag().Id()))) {
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Shader_frag().Src().Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_info_2(pc_sz_pat_src, (_pc_sz) CType::To_str (this->Shader_frag().Type()));
	}

	if (__failed(this->Shader_vert().Src().Set(IDS_TUTOR_2_SHADER_VERT_0, this->Shader_vert().Id()))) {
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Shader_vert().Src().Error().Print(TError::e_print::e_req));
	}else {
		__trace_info_2(pc_sz_pat_src, (_pc_sz) CType::To_str (this->Shader_vert().Type()));
	}

	static _pc_sz pc_sz_pat_cmpl = _T("Source code of '%s' shader is compiled;\n");
	static _pc_sz pc_sz_pat_stat = _T("Shader '%s' compiled status: '%s';\n");

	if (false == this->Shader_frag().Error()().Is()) {
		cmpl << this->Shader_frag().Id();
		if ( __failed(cmpl.Compile())) {
		     __trace_err_2(_T("%s\n"), (_pc_sz)cmpl.Error().Print(TError::e_print::e_req)); }
		else __trace_info_2(pc_sz_pat_cmpl, (_pc_sz) CType::To_str (this->Shader_frag().Type()));
		// checks the compile status of the shader;
		$_status << this->Shader_frag().Id();
		const bool b_compiled = $_status.Is_compiled();
		if ($_status.Error() ) {
			__trace_err_2(_T("%s\n"), (_pc_sz) $_status.Error().Print(TError::e_print::e_req)); }
		else {
			__trace_info_2(pc_sz_pat_stat,  (_pc_sz) CType::To_str (this->Shader_frag().Type()), TString().Bool(b_compiled));
			if (false == b_compiled) {
				shader::CLog log;
				if (__failed(log.Set(this->Shader_frag().Id()))) {
				    __trace_err_2(_T("%s\n"), (_pc_sz) log.Error().Print(TError::e_print::e_req)); }
				else {
					__trace_warn_2(_T("%s\n"), _T("Compile log:"));
				    __trace_err(_T("%s"), log.Get());
				}
			}
		}
	}

	if (false == this->Shader_vert().Error()().Is()) {
		cmpl << this->Shader_vert().Id();
		if ( __failed(cmpl.Compile())) {
		     __trace_err_2(_T("%s\n"), (_pc_sz)cmpl.Error().Print(TError::e_print::e_req)); }
		else __trace_info_2(pc_sz_pat_cmpl, (_pc_sz) CType::To_str (this->Shader_vert().Type()));
		// checks the compile status of the shader;
		$_status << this->Shader_vert().Id();
		const bool b_compiled = $_status.Is_compiled();
		if ($_status.Error() ) {
			__trace_err_2(_T("%s\n"), (_pc_sz) $_status.Error().Print(TError::e_print::e_req)); }
		else {
			__trace_info_2(pc_sz_pat_stat,  (_pc_sz) CType::To_str (this->Shader_vert().Type()), TString().Bool(b_compiled));
			if (false == b_compiled) {
				shader::CLog log;
				if (__failed(log.Set(this->Shader_vert().Id()))) {
				    __trace_err_2(_T("%s\n"), (_pc_sz) log.Error().Print(TError::e_print::e_req)); }
				else {
					__trace_warn_2(_T("%s\n"), _T("Compile log:"));
				    __trace_err(_T("%s"), log.Get());
				}
			}
		}
	}

	CProgram prog;
	if (__failed(prog.Create())) {
		__trace_err_2(_T("%s\n"), (_pc_sz) prog.Error().Print(TError::e_print::e_req));
		return TBase::m_error = prog.Error();
	}
	else
		__trace_impt_2(_T("Program object (id=%u) is created;\n"), prog.Id().Get());

	program::CLinker linker(prog.Id());

	static _pc_sz pc_sz_pat_att = _T("Program attaches '%s' shader successfully;\n");

	if ( __failed(prog.Shaders().Attach(this->Shader_frag().Id())) ) {
	     __trace_err_2(_T("%s\n"), (_pc_sz) prog.Shaders().Error().Print(TError::e_print::e_req)); }
	else __trace_info_2(pc_sz_pat_att, (_pc_sz) CType::To_str (this->Shader_frag().Type()));

	if ( __failed(prog.Shaders().Attach(this->Shader_vert().Id())) ) {
	     __trace_err_2(_T("%s\n"), (_pc_sz) prog.Shaders().Error().Print(TError::e_print::e_req)); }
	else __trace_info_2(pc_sz_pat_att, (_pc_sz) CType::To_str (this->Shader_vert().Type()));

	static _pc_sz pc_sz_pat_lnk = _T("The program (id=%u) is linked;\n");

	program::CStatus prog_status(prog.Id());

	if (false == linker.Error()) {
		if ( __failed(linker.Link()) ) {
		     __trace_err_2(_T("%s\n"), (_pc_sz) linker.Error().Print(TError::e_print::e_req)); }
		else __trace_impt_2(pc_sz_pat_lnk, linker.ProgId());
		// just checks the program link status;
		const bool b_linked = prog_status.Is_linked();
		if ( prog_status.Error() ) {
			__trace_err_2(_T("%s\n"), (_pc_sz) prog_status.Error().Print(TError::e_print::e_req)); }
		else {
			__trace_info_2(_T("Program (id=%u) link status is '%s';\n"), linker.ProgId(), TString().Bool(b_linked));
			if (false == b_linked) {
				program::CLog log;
				if (__failed( log.Set(prog.Id()))) {
				    __trace_err_2(_T("%s\n"), (_pc_sz) log.Error().Print(TError::e_print::e_req)); }
				else {
					__trace_warn_2(_T("%s\n"), _T("Link log:"));
				    __trace_err(_T("%s"), log.Get());
				}
			}
		}
	}

	if ( __failed(prog.Validate())) {
	     __trace_err_2(_T("%s\n"), (_pc_sz) prog.Error().Print(TError::e_print::e_req)); }
	else __trace_info_2(_T("Program (id=%u) is validated;\n"), linker.ProgId());

	// just for testing purpose;
	if ( __failed(prog.Shaders().Detach_all())) {
	     __trace_err_2(_T("%s\n"), (_pc_sz) linker.Error().Print(TError::e_print::e_req)); }
	else __trace_warn_2(_T("All shaders are detached;\n"));

	return (*this)().Error();
}

}}}}