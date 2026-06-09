/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jan-2026 at 23:40:52.858, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL program log wrapper interface implementation file;
*/
#include "gl_prog_log.h"
#include "gl_program.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

#include "gl_procs_prog.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;

CLog::CLog (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CLog::CLog (const CLog& _src) : CLog() { *this = _src; }

const
CString& CLog::Buffer (void) const { return this->m_buffer; }

TError& CLog::Error (void) const { return this->m_error; }
_pc_sz  CLog::Get (void) const { return (_pc_sz) this->m_buffer; }

err_code CLog::Set (const uint32_t _u_prog_id) {
	_u_prog_id;
	this->m_error <<__METHOD__<<__s_ok;

	if (false == CProgram::Is_valid(_u_prog_id, this->m_error))
		return this->Error();

	using e_status_params = procs::program::e_status_params;

	// (1) gets the program log length;
	uint32_t u_length = 0;
	if (__failed(__get_prog_procs().Params(_u_prog_id, (uint32_t)e_status_params::e_info_log_len, &u_length))) {
		this->m_buffer = _T("#error");
		return this->m_error = __get_prog_procs().Error();
	}

	if (0 == u_length) {
		this->m_buffer = _T("#no_info");
		return this->Error();
	}
	// (2) retrieves the actual data from the log;
	::std::vector<char> buffer(u_length + 1, 0);
	if (__failed(__get_prog_procs().InfoLog(_u_prog_id, u_length, &u_length, buffer.data()))) {
		this->m_buffer = _T("#error");
		return this->m_error = __get_prog_procs().Error();
	}

	this->m_buffer = buffer.data(); // ATL::CString makes the auto-conversion from 'char' to 'tchar';
	this->m_buffer.Replace(_T("  "), _T(" "));

	return this->Error();
}

CLog&  CLog::operator = (const CLog& _src) {
	this->m_error = _src.Error(); this->m_buffer = _src.m_buffer;
	return *this;
}