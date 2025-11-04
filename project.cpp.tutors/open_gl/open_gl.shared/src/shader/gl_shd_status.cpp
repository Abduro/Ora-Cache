/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Sep-2025 at 08:11:45.776, UTC+4, Batumi, Tuesday;
	This Ebo Pack OpenGL shader status wrapper interface implementation file;
*/
#include "gl_shd_status.h"
#include "gl_procs.h"
#include "gl_shader.h"
#include "shared.preproc.h"

#include "procs\gl_procs_shader.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

/////////////////////////////////////////////////////////////////////////////

// the error state must be set to 'no error' otherwise static CStatus::Get() will return 'not inited';
CStatus:: CStatus (const uint32_t _shader_id) : m_shd_id(_shader_id) { this->m_error>>__CLASS__<<__METHOD__<<__s_ok; }
CStatus::~CStatus (void) {}

TError&   CStatus::Error (void) const { return this->m_error; }
const
shader::CShaderId&  CStatus::ShaderId (void) const { return this->m_shd_id; }
shader::CShaderId&  CStatus::ShaderId (void)       { return this->m_shd_id; }

#define __gl_cmpl_status  0x8B81 // GL_COMPILE_STATUS;

bool  CStatus::Get (const uint32_t _param_id) const {
	return CStatus::Get(_param_id, this->ShaderId(), this->m_error);
}
bool  CStatus::Get (const uint32_t _param_id, const uint32_t _shader_id, CError& _err) {
	_param_id; _shader_id; _err;
	if (__gl_cmpl_status != _param_id) { _err << __e_inv_arg = TString().Format(_T("#__e_inv_arg: '_param_id' (%u) is unknown")); return false; }

	if (false == CShaderId::Is_valid(_shader_id, _err))
		return false;

	int32_t n_result = 0;

	if (__failed(__get_$_procs().Params(_shader_id, _param_id, &n_result)))
	     return false == (_err = __get_$_procs().Error()).Is();
	else return !!n_result;
}

bool  CStatus::Is_compiled (void) const {
	return CStatus::Is_compiled(this->ShaderId(), this->m_error);
}
bool  CStatus::Is_compiled (const uint32_t _shader_id, CError& _err) {
	return CStatus::Get(__gl_cmpl_status, _shader_id, _err);
}

CStatus& CStatus::operator <<(const uint32_t _shader_id) { this->ShaderId() << _shader_id; return *this; }