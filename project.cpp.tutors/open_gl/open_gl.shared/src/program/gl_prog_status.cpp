/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Sep-2025 at 18:49:51.933, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL program status wrapper interface implementation file;
*/
#include "gl_prog_status.h"
#include "gl_procs.h"
#include "shared.preproc.h"
#include "gl_program.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;

/////////////////////////////////////////////////////////////////////////////

#define __gl_lnk_status    0x8B82 // GL_LINK_STATUS ;
#define __gl_valid_status  0x8B83 // GL_VALIDATE_STATUS ;
// the error state must be set to 'no error' otherwise static CStatus::Get() will return 'not inited';
CStatus:: CStatus (const uint32_t _prog_id) : m_prog_id(_prog_id) { this->m_error>>__CLASS__<<__METHOD__<<__s_ok; }
CStatus::~CStatus (void) {}

TError&   CStatus::Error (void) const { return this->m_error; }
const
program::CProgId&  CStatus::ProgId (void) const { return this->m_prog_id; }
program::CProgId&  CStatus::ProgId (void)       { return this->m_prog_id; }

bool  CStatus::Get (const uint32_t _param_id) const {
	return CStatus::Get(_param_id, this->ProgId(), this->m_error);
}
bool  CStatus::Get (const uint32_t _param_id, const uint32_t _prog_id, CError& _err) {
	_param_id; _err;
	if (__gl_lnk_status != _param_id &&
	    __gl_valid_status != _param_id) { _err << __e_inv_arg = TString().Format(_T("#__e_inv_arg: '_param_id' (%u) is unknown")); return false; }

	if (false == CProgId::Is_valid(_prog_id, _err))
		return false;

	procs::CProg& procs = CProgram::Cache();
	int32_t n_result = 0;

	if (__failed(procs.Params(_prog_id, _param_id, &n_result)))
	     return false == (_err = procs.Error()).Is();
	else return !!n_result;
}

bool  CStatus::Is_linked (void) const {
	return CStatus::Is_linked(this->ProgId(), this->m_error);
}
bool  CStatus::Is_linked (const uint32_t _u_prog_id, CError& _err) {
	return CStatus::Get(__gl_lnk_status, _u_prog_id, _err);
}

bool  CStatus::Is_valid  (void) const {
	return CStatus::Is_valid(this->ProgId(), this->m_error);
}
bool  CStatus::Is_valid  (const uint32_t _u_prog_id, CError& _err) {
	return CStatus::Get(__gl_valid_status, _u_prog_id, _err);
}