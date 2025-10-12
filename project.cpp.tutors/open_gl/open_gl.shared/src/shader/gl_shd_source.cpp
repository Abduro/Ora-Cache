/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 17:18:00.979, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader SL source wrapper interface implementation file;
*/
#include "gl_shd_source.h"
#include "gl_shader.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;
using namespace shared::app;

CSrc_Cfg:: CSrc_Cfg (void) : m_prefer(e_prefer::e_undef), m_res_id(0) {
	this->m_error >> TString().Format(_T("%s::%s"), (_pc_sz) CShader::Class(), (_pc_sz)__CLASS__)<<__METHOD__<<__e_not_inited; }
CSrc_Cfg:: CSrc_Cfg (const CSrc_Cfg& _src) : CSrc_Cfg() { *this = _src; }
CSrc_Cfg::~CSrc_Cfg (void) {}

TError&   CSrc_Cfg::Error (void) const { return this->m_error; }

bool CSrc_Cfg::Is_valid (void) const {
	return ((e_prefer::e_res == this->Prefer() && !!this->ResId()) ||
	        (e_prefer::e_path == this->Prefer() &&  this->m_path.IsEmpty() == false));
}

CSrc_Cfg::e_prefer CSrc_Cfg::Prefer (void) const { return m_prefer; }
bool      CSrc_Cfg::Prefer (const e_prefer _e_mode) {
	const bool b_changed = (_e_mode != this->Prefer()); if (b_changed) this->m_prefer = _e_mode; return b_changed;
}

uint16_t  CSrc_Cfg::ResId  (void) const { return this->m_res_id; }
err_code  CSrc_Cfg::ResId  (const uint16_t _res_id, const e_res_types _e_type) {
	_res_id; _e_type;
	this->m_error <<__METHOD__<<__s_ok;

	res::CLocator locator;
	if (false == locator.Has(_res_id, _e_type)) {
		if (locator.Error())
			this->m_error = locator.Error();
		else
			this->m_error <<__e_inv_arg << TString().Format(_T("#__e_inv_val: '_res_id' (%u) is not found"), _res_id);
	}
	else
		this->m_res_id = _res_id;

	return this->Error();
}

_pc_sz    CSrc_Cfg::Path   (void) const { return (_pc_sz)this->m_path; }
err_code  CSrc_Cfg::Path   (_pc_sz _p_path) {
	_p_path;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_path || 0 == ::_tcslen(_p_path))
		return this->m_error <<__e_inv_arg;
	// https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathfileexistsa ;
	if (false == !!::PathFileExists(_p_path)) // ::GetLastError() can be called for additional detals of the errpr;
		this->m_error <<__e_inv_arg << TString().Format(_T("#__e_not_valid: '_p_path' %s does not exist"), _p_path);

	return this->Error();
}

CSrc_Cfg& CSrc_Cfg::operator = (const CSrc_Cfg& _src) { *this << _src.Prefer() << _src.ResId() << _src.Path(); return *this; }

CSrc_Cfg& CSrc_Cfg::operator <<(const e_prefer _e_mode) { this->Prefer(_e_mode); return *this; }
CSrc_Cfg& CSrc_Cfg::operator <<(const uint16_t _res_id) { this->m_res_id = _res_id; return *this; }
CSrc_Cfg& CSrc_Cfg::operator <<(_pc_sz _p_path) { this->Path(_p_path); return *this; }

/////////////////////////////////////////////////////////////////////////////

CSource:: CSource (void) { this->m_error >> TString().Format(_T("%s::%s"), (_pc_sz) CShader::Class(), (_pc_sz)__CLASS__)<<__METHOD__<<__e_not_inited; }
CSource:: CSource (const CSource& _src) : CSource() { *this = _src; }
CSource::~CSource (void) {}

const
CSrc_Cfg& CSource::Gfg (void) const { return m_cfg; }
CSrc_Cfg& CSource::Cfg (void)       { return m_cfg; }

CString  CSource::Class (void) { return __CLASS__; }

TError&  CSource::Error (void) const { return this->m_error; }

_pc_sz   CSource::Get (void) const { return (_pc_sz)this->m_buffer; }

err_code CSource::Set (_pc_sz _p_source, const uint32_t _u_shader_id) {
	_p_source; _u_shader_id;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_source || CString(_p_source).IsEmpty())
		return this->m_error  << __e_inv_arg = _T("Source code is empty");

	if (false == CShader::Is_valid(_u_shader_id, this->m_error)) {
		return this->Error();
	}
	this->m_buffer = _p_source; m_buffer.Trim();

	CStringA src_a((_pc_sz) this->m_buffer); // converts to ansi-char from unicode if necessary;
	int32_t n_len = src_a.GetLength();

	const char* p_buffer = src_a.GetBuffer();

	procs::CShader& procs = CShader::Procs();
	if (__failed(procs.Source(_u_shader_id, 1, &p_buffer, &n_len)))
		return this->m_error = procs.Error();

	return this->Error();
}

err_code CSource::Set (const uint16_t _res_id, const uint32_t _n_shader_id) {
	_res_id; _n_shader_id;
	this->m_error <<__METHOD__<<__s_ok;
	if (0 == _res_id)
		return this->m_error << __e_inv_arg = _T("String resource identifier is invalid");

	CString cs_src;
	cs_src.LoadString(_res_id);

	return this->Set((_pc_sz) cs_src, _n_shader_id);
}

CSource& CSource::operator = (const CSource& _src) { this->m_buffer = _src.Get(); return *this; }