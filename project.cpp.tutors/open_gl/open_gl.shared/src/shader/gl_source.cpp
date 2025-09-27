/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 17:18:00.979, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader SL source wrapper interface implementation file;
*/
#include "gl_source.h"
#include "gl_shader.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

CSource:: CSource (void) { this->m_error() >> TString().Format(_T("%s::%s"), (_pc_sz) CShader::Class(), (_pc_sz)__CLASS__)<<__METHOD__<<__e_not_inited; }
CSource::~CSource (void) {}

TErr_ex& CSource::Error (void) const { return this->m_error; }

err_code CSource::Set (_pc_sz _p_source, const uint32_t _u_shader_id) {
	_p_source; _u_shader_id;
	this->m_error()<<__METHOD__<<__s_ok;

	if (nullptr == _p_source || CString(_p_source).IsEmpty())
		return this->m_error() << __e_inv_arg = _T("Source code is empty");

	if (false == CShader::Is_valid(_u_shader_id, this->m_error())) {
		return this->Error()();
	}
	this->m_buffer = _p_source; m_buffer.Trim();

	CStringA src_a((_pc_sz) this->m_buffer); // converts to ansi-char from unicode if necessary;
	int32_t n_len = src_a.GetLength();

	const char* p_buffer = src_a.GetBuffer();

	procs::CShader& procs = CShader::Cache();
	if (__failed(procs.Source(_u_shader_id, 1, &p_buffer, &n_len)))
		return this->m_error() = procs.Error();

	return this->Error()();
}

err_code CSource::Set (const uint16_t _res_id, const uint32_t _n_shader_id) {
	_res_id; _n_shader_id;
	this->m_error()<<__METHOD__<<__s_ok;
	if (0 == _res_id)
		return this->m_error() << __e_inv_arg = _T("String resource identifier is invalid");

	CString cs_src;
	cs_src.LoadString(_res_id);

	return this->Set((_pc_sz) cs_src, _n_shader_id);
}