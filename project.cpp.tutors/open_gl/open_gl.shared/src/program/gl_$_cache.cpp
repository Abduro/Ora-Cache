/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Oct-2025 at 16:50:53.142, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL shader collection or cache (used by program) interface implementation file;
*/
#include "gl_$_cache.h"
#include "shared.preproc.h"
#include "gl_prog_linker.h"
#include "gl_program.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;

CCache:: CCache (const uint32_t _prog_id) : m_prog_id(0) { this->m_error>>__CLASS__<<__METHOD__<<__s_ok; if (!!_prog_id) *this<<_prog_id; }
CCache::~CCache (void) { this->Detach_all(); }

err_code  CCache::Attach (const uint32_t _u_shader_id) {
	return CCache::Attach(_u_shader_id, this->ProgId(), this->m_error);
}

err_code  CCache::Attach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError& _err) {
	_u_shader_id; _u_prog_id; _err;

	procs::CLinker& procs = CLinker::Cache();
	if (__failed( procs.Attach(_u_prog_id, _u_shader_id )))
		_err = procs.Error();

	return _err.Result();
}

err_code CCache::Detach (const uint32_t _u_shader_id) {
	return CCache::Detach(_u_shader_id, this->ProgId(), this->m_error);
}

err_code CCache::Detach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError& _err) {
	_u_shader_id; _u_prog_id; _err;

	procs::CLinker& procs = CLinker::Cache();
	if (__failed( procs.Detach(_u_prog_id, _u_shader_id )))
		_err = procs.Error();

	return _err;
}

err_code  CCache::Detach_all (void) {
	return  CCache::Detach_all(this->ProgId(), this->m_error);
}

err_code  CCache::Detach_all (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
	if (false == CProgram::Is_valid(_u_prog_id, _err))
		return _err;

	static const uint32_t u_max_count = 32;

	uint32_t shader_ids[u_max_count] = {0};
	uint32_t u_count = 0;

	procs::CLinker& procs = CLinker::Cache();
	if (__failed(procs.Attached(_u_prog_id, u_max_count, &u_count, shader_ids)))
		return _err = procs.Error();

	for (uint32_t i_ = 0; i_ < u_count && i_ < u_max_count; i_++) {
		if (__failed(procs.Detach(_u_prog_id, shader_ids[i_]))) {
			_err = procs.Error(); break;
		}
	}

	return _err;
}
 
TError&  CCache::Error (void) const { return this->m_error; }

uint32_t CCache::ProgId (void) const { return this->m_prog_id; }   
err_code CCache::ProgId (const uint32_t _prog_id) {
	_prog_id;
	if (0 == _prog_id) return this->m_error <<__e_inv_arg;
	this->m_prog_id = _prog_id;

	return this->Error();
}

CCache& CCache::operator <<(const uint32_t _prog_id) { this->ProgId(_prog_id); return *this; }

CCache&  CCache::operator +=(const uint32_t _u_shader_id) {
	this->Attach(_u_shader_id);
	return *this;
}

CCache&  CCache::operator -=(const uint32_t _u_shader_id) {
	this->Detach(_u_shader_id);
	return *this;
}