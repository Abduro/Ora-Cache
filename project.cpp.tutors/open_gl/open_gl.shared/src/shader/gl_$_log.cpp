/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Jan-2026 at 01:42:12.431, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL shader log wrapper interface implementation file;
*/
#include "gl_$_log.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

#include "gl_procs_shader.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

CLog::CLog (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CLog::Error (void) const { return this->m_error; }
_pc_sz  CLog::Get (void) const { return (_pc_sz) this->m_buffer; }

// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-2/compiler-errors-c3100-through-c3199 ;
err_code CLog::Set (const uint32_t _u_shader_id) {
	_u_shader_id;
	this->m_error <<__METHOD__<<__s_ok;

	if (0 == _u_shader_id)
		return this->m_error <<__e_inv_arg = TString().Format(_T("Invalid shader id (0x%04x)"), _u_shader_id);

	using e_param_types = procs::CShader::e_param_types;

	// (1) gets the shader log length;
	int32_t n_length = 0;
	if (__failed(__get_$_procs().Params(_u_shader_id, e_param_types::e_info_len, &n_length))) {
		this->m_buffer = _T("#error");
		return this->m_error = __get_$_procs().Error();
	}

	if (0 == n_length) {
		this->m_buffer = _T("#no_info");
		return this->Error();
	}
	// retrieves the actual data from the log;
	::std::vector<char> buffer(n_length + 1, 0);
	if (__failed(__get_$_procs().InfoLog(_u_shader_id, n_length, &n_length, buffer.data()))) {
		this->m_buffer = _T("#error");
		return this->m_error = __get_$_procs().Error();
	}

	this->m_buffer = buffer.data(); // ATL::CString makes the auto-conversion from 'char' to 'tchar';
	this->m_buffer.MakeLower();
	// ToDo: this is temporary solution and will be replaced with the better one later;
 	this->m_buffer.Replace(_T("error"), _T("  error")); // makes an indentation at the beginning of each error line;
	this->m_buffer.Replace(_T("   "), _T(" "));         // replaces the sequence of 3 (three) whitespaces by one;

	this->m_buffer.TrimRight();

	this->m_error << __e_fail = (_pc_sz) this->m_buffer;

	return this->Error();
}