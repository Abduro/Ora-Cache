/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Sep-2025 at 18:49:51.933, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL program status wrapper interface implementation file;
*/
#include "gl_prog_status.h"
#include "gl_program.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

#include "procs\gl_procs_prog.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;

/////////////////////////////////////////////////////////////////////////////
#define __gl_curr_prog     0x8B8D // GL_CURRENT_PROGRAM ;
#define __gl_lnk_status    0x8B82 // GL_LINK_STATUS ;
#define __gl_valid_status  0x8B83 // GL_VALIDATE_STATUS ;
// the error state must be set to 'no error' otherwise static CStatus::Get() will return 'not inited';
CStatus:: CStatus (const uint32_t _prog_id) : m_prog_id(_prog_id) { this->m_error>>__CLASS__<<__METHOD__<<__s_ok; }
CStatus::~CStatus (void) {}

TError&   CStatus::Error (void) const { return this->m_error; }

bool  CStatus::Get (const uint32_t _param_id) const {
	return CStatus::Get(_param_id, this->ProgId(), this->m_error);
}
bool  CStatus::Get (const uint32_t _param_id, const uint32_t _prog_id, CError& _err) {
	_param_id; _err;
	if (__gl_lnk_status != _param_id &&
	    __gl_valid_status != _param_id &&
	    __gl_curr_prog != _param_id) { _err << __e_inv_arg = TString().Format(_T("#__e_inv_arg: '_param_id' (%u) is unknown")); return false; }

	if (false == CProgId::Is_valid(_prog_id, _err))
		return false;

	if (__gl_curr_prog == _param_id)
		return CStatus::Is_current(_prog_id, _err);

	uint32_t u_result = 0;

	if (__failed(__get_prog_procs().Params(_prog_id, _param_id, &u_result)))
	     return false == (_err = __get_prog_procs().Error()).Is();
	else return !!u_result;
}

uint32_t CStatus::GetActiveProg (CError& _err) {
	_err;
	uint32_t u_prog_id = abs(__get_param_procs().GetInt(__gl_curr_prog));

	if (__get_param_procs().Error())
		_err = __get_param_procs().Error();

	return u_prog_id;
}

bool  CStatus::Is_current (void) const {
	return CStatus::Is_current(this->ProgId().Get(), this->m_error);
}

bool  CStatus::Is_current (const uint32_t _prog_id, CError& _err) {
	_prog_id; _err;
	
	if (false == CProgId::Is_valid(_prog_id, _err))
		return false;

	return _prog_id == CStatus::GetActiveProg(_err);
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

const
program::CProgId&  CStatus::ProgId (void) const { return this->m_prog_id; }
program::CProgId&  CStatus::ProgId (void)       { return this->m_prog_id; }

CStatus&  CStatus::operator <<(const CProgId& _prog_id) {
	this->ProgId() << _prog_id;
	return *this;
}