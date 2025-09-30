/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Sep-2025 at 16:57:20.305, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL log functions' wrapper interface implementation file;
*/
#include "gl_logs.h"
#include "shared.preproc.h"
#include "gl_program.h"
#include "gl_shader.h"

using namespace ex_ui::draw::open_gl;

CLog_Base:: CLog_Base (void) { this->m_error()>>__CLASS__<<__METHOD__<<__e_not_inited; }
CLog_Base::~CLog_Base (void) {}

TErr_ex&  CLog_Base::Error (void) const { return this->m_error; }
_pc_sz    CLog_Base::Get (void) const { return (_pc_sz) this->m_buffer; }

#define GL_INFO_LOG_LEN    0x8B84
/////////////////////////////////////////////////////////////////////////////

program::CLog:: CLog (void) : TBase() {
	TBase::m_error() >> TString().Format(_T("%s::%s"), (_pc_sz) CProgram::Class(), (_pc_sz)__CLASS__)<<__METHOD__<<__e_not_inited; }
program::CLog::~CLog (void) {}

err_code program::CLog::Set (const uint32_t _u_prog_id) {
	_u_prog_id;
	TBase::m_error()<<__METHOD__<<__s_ok;

	if (false == CProgram::Is_valid(_u_prog_id, this->m_error()))
		return TBase::Error()();

	procs::CProg& procs = CProgram::Cache();
	// (1) gets the shader log length;
	int32_t n_length = 0;
	if (__failed(procs.Params(_u_prog_id, GL_INFO_LOG_LEN, &n_length))) {
		this->m_buffer = _T("#error");
		return this->m_error() = procs.Error();
	}

	if (0 == n_length) {
		this->m_buffer = _T("#no_info");
		return this->Error()();
	}
	// (2) retrieves the actual data from the log;
	::std::vector<char> buffer(n_length + 1, 0);
	if (__failed(procs.InfoLog(_u_prog_id, n_length, &n_length, buffer.data()))) {
		this->m_buffer = _T("#error");
		return this->m_error() = procs.Error();
	}

	this->m_buffer = buffer.data(); // ATL::CString makes the auto-conversion from 'char' to 'tchar';
	this->m_buffer.Replace(_T("  "), _T(" "));

	return this->Error()();
}

/////////////////////////////////////////////////////////////////////////////

shader::CLog:: CLog (void) : TBase() {
	TBase::m_error() >> TString().Format(_T("%s::%s"), (_pc_sz) CShader::Class(), (_pc_sz)__CLASS__)<<__METHOD__<<__e_not_inited; }
shader::CLog::~CLog (void) {}

err_code shader::CLog::Set (const uint32_t _u_shader_id) {
	_u_shader_id;
	TBase::m_error()<<__METHOD__<<__s_ok;

	if (0 == _u_shader_id)
		return this->m_error() <<__e_inv_arg = TString().Format(_T("Invalid shader id (%u)"), _u_shader_id);

	procs::CShader& procs = CShader::Cache();
	// (1) gets the shader log length;
	int32_t n_length = 0;
	if (__failed(procs.Params(_u_shader_id, GL_INFO_LOG_LEN, &n_length))) {
		this->m_buffer = _T("#error");
		return this->m_error() = procs.Error();
	}

	if (0 == n_length) {
		this->m_buffer = _T("#no_info");
		return this->Error()();
	}
	// retrieves the actual data from the log;
	::std::vector<char> buffer(n_length + 1, 0);
	if (__failed(procs.InfoLog(_u_shader_id, n_length, &n_length, buffer.data()))) {
		this->m_buffer = _T("#error");
		return this->m_error() = procs.Error();
	}

	this->m_buffer = buffer.data(); // ATL::CString makes the auto-conversion from 'char' to 'tchar';
	this->m_buffer.MakeLower();
	// ToDo: this is temporary solution and will be replaced with the better one later;
 	this->m_buffer.Replace(_T("error"), _T("  error")); // makes an indentation at the beginning of each error line;
	this->m_buffer.Replace(_T("   "), _T(" "));         // replaces the sequence of 3 (three) whitespaces by one;

	return this->Error()();
}