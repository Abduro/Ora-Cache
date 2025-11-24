/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Sep-2025 at 17:48:34.237, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' shader program base interface implementation file;
*/
#include "gl_program.h"
#include "program\gl_prog_linker.h"
#include "program\gl_prog_status.h"
#include "procs\gl_procs_prog.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;

/////////////////////////////////////////////////////////////////////////////

#define __gl_curr_prog 0x8B8D // GL_CURRENT_PROGRAM ;

CProgram:: CProgram (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CProgram::~CProgram (void) { this->Delete(); }

const
CBuffer_4_vert&  CProgram::Buffer (void) const { return this->m_buffer; }
CBuffer_4_vert&  CProgram::Buffer (void)       { return this->m_buffer; }

CString   CProgram::Class (void) { return __CLASS__; }

TError&   CProgram::Error (void) const { return this->m_error; }

err_code  CProgram::Create (void) {
	this->m_error<<__METHOD__<<__s_ok;

	if (!!this->Id())
		return this->m_error <<(err_code)TErrCodes::eObject::eExists = TString().Format(_T("Program object (id = %u) already exists"), this->Id().Get());

	this->Id() << __get_prog_procs().Create();
	if (0 == this->Id()) {
		if (__get_prog_procs().Error().Is())
			this->m_error = __get_prog_procs().Error();
		program::CLog log;
		if (__failed(log.Set(0))) {} // if the program identifier equals to zero, there is no way to get the creation error details;
	}
	else {
		this->Shaders() << this->Id(); // this is very *important*, otherwise no shader attachment will succeed;
		this->Status() << this->Id();
	}
	if (this->Error()) {
	      __trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); }
	else {__trace_impt_2(_T("The program (id = %u) is created;\n"), this->Id().Get()); }

	return this->Error();
 }

err_code  CProgram::Delete (void) {
	this->m_error<<__METHOD__<<__s_ok;

	if (false == !!this->Id())
		return this->Error();  // returns __s_ok; there is nothing to destroy;
#if (0)
	CCache(this->Id()).Detach_all(); // it is supposed the shader(s) will be destroyed later than this program, so shader(s) must be detached first;
#endif

	if (__failed(__get_prog_procs().Delete(this->Id()))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) __get_prog_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = __get_prog_procs().Error();
	}
	else
		__trace_warn_2(_T("The program (id = %u) is deleted;\n"), this->Id().Get());

	this->Id().Reset();

	this->Shaders().ProgId().Reset();
	this->Status().ProgId().Reset();

	return this->Error();
}

const
CProgId& CProgram::Id (void) const { return this->m_prog_id; }
CProgId& CProgram::Id (void)       { return this->m_prog_id; }

bool CProgram::Is_valid (void) const {
	return CProgram::Is_valid(this->Id(), this->m_error<<__METHOD__<<__s_ok);
}

bool CProgram::Is_valid (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
#if (0)
	static _pc_sz p_sz_pat_err = _T("'_u_prog_id' (%u) is invalid");

	if (0 == _u_prog_id) {
		return false == (_err << __e_inv_arg = TString().Format(p_sz_pat_err, _u_prog_id)).Is();
	}
	procs::CParam param;

	const uint32_t n_curr_prog = param.GetInt(__gl_curr_prog); // if a negative result is returned, the input '_u_prog_id' will still be different;

	if (0 == n_curr_prog) {
		if (param.Error())
			return false == (_err = param.Error()).Is(); // Error.Is() returns 'true' in such case, thus 'false == true' is valid return result;
	}
	else if (_u_prog_id != n_curr_prog) {
		_err << __e_inv_arg = TString().Format(p_sz_pat_err, _u_prog_id);
	}
	return false == _err.Is();
#else
	return CProgId::Is_valid(_u_prog_id, _err);
#endif
}

err_code CProgram::Link (void) {
	this->m_error<<__METHOD__<<__s_ok;

	static _pc_sz pc_sz_pat_lnk = _T("The program (id = %u) is linked;\n");

	CStatus prog_status(this->Id());
	CLinker linker(this->Id());

	if ( __failed(linker.Link()) ) {
	     __trace_err_2(_T("%s\n"), (_pc_sz) linker.Error().Print(TError::e_print::e_req)); this->m_error = linker.Error(); }
	else __trace_impt_2(pc_sz_pat_lnk, linker.ProgId());

	// just checks the program link status;
	const bool b_linked = prog_status.Is_linked();
	if ( prog_status.Error() ) {
		__trace_err_2(_T("%s\n"), (_pc_sz) prog_status.Error().Print(TError::e_print::e_req));}
	else {
		__trace_info_2(_T("Program (id = %u) link status is '%s';\n"), linker.ProgId(), TString().Bool(b_linked));
		if (false == b_linked) {
			program::CLog log;
			if (__failed( log.Set(this->Id()))) {
			    __trace_err_2(_T("%s\n"), (_pc_sz) log.Error().Print(TError::e_print::e_req)); }
			else {
				__trace_warn_2(_T("%s\n"), _T("Link log:"));
			    __trace_err(_T("%s"), log.Get());
			}
		}
	}
	return this->Error();
}

const
program::CCache& CProgram::Shaders (void) const { return this->m_shaders; }
program::CCache& CProgram::Shaders (void)       { return this->m_shaders; }
const
program::CStatus& CProgram::Status (void) const { return this->m_status; }
program::CStatus& CProgram::Status (void)       { return this->m_status; }

 err_code CProgram::Use (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Status().Is_current()) {
		this->m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("#__e_inv_state: the program (id = %u) is already used"), this->Id()());
		return this->Error();
	}

	if (__failed(__get_prog_procs().Use(this->Id()())))
		this->m_error = __get_prog_procs().Error();
	else __trace_info_2(_T("Program (id = %u) is in use;\n"), this->Id().Get());

	return this->Error();
 }

err_code CProgram::Validate (void) {
	this->m_error<<__METHOD__<<__s_ok;

	procs::CProg& procs = __get_prog_procs();

	if (__failed(procs.Validate(this->Id()))) {
	    __trace_err_2(_T("%s\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req));
		this->m_error = procs.Error();
	}
	else __trace_info_2(_T("Program (id = %u) is validated;\n"), this->Id().Get());
	return this->Error();
}

CProgram& CProgram::operator <<(const CProgId& _prog_id) { this->Id() << _prog_id; return *this; }