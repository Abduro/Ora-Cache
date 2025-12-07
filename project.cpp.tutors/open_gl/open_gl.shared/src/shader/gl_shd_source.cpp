/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 17:18:00.979, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader SL source wrapper interface implementation file;
*/
#include "gl_shd_source.h"
#include "gl_shader.h"
#include "shared.dbg.h"
#include "shared.preproc.h"
#include "sys.registry.h"

#include "procs\gl_procs_shader.h"

#pragma warning(disable: 4702)

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;
using namespace shared::app;
using namespace shared::sys_core::storage;

using e_shaders = CReg_router::CShaders::e_types;

CSrc_Cfg:: CSrc_Cfg (void) : m_prefer(e_prefer::e_undef), m_res_id(0) {
	this->m_error >> TString().Format(_T("%s::%s"), (_pc_sz) CShader::Class(), (_pc_sz)__CLASS__)<<__METHOD__<<__e_not_inited; }
CSrc_Cfg:: CSrc_Cfg (const CSrc_Cfg& _src) : CSrc_Cfg() { *this = _src; }
CSrc_Cfg::~CSrc_Cfg (void) {}

TError&   CSrc_Cfg::Error (void) const { return this->m_error; }

bool CSrc_Cfg::Is_valid (void) const {
	return ((e_prefer::e_res == this->Prefer() && !!this->ResId()) ||
	        (e_prefer::e_file == this->Prefer() &&  this->m_path.IsEmpty() == false));
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
	else {
		this->m_prefer = e_prefer::e_res;
		this->m_res_id = _res_id;
	}
	return this->Error();
}

_pc_sz    CSrc_Cfg::Path (void) const { return (_pc_sz)this->m_path; }
err_code  CSrc_Cfg::Path (_pc_sz _p_object, const $Type _e_type) {
	_p_object, _e_type;
	this->m_error <<__METHOD__<<__s_ok;

	e_shaders e_shader = e_shaders::e__undef;

	// only supported shader types is considered as correct ones;
	switch (_e_type) {
	case $Type::e_fragment: e_shader = e_shaders::e_fragment; break;
	case $Type::e_vertex  : e_shader = e_shaders::e_vertex; break;
	default:
		return this->m_error <<__e_inv_arg = TString().Format(_T("Unsupported shader type '%s'"), (_pc_sz) CType::To_str((uint32_t)_e_type));
	}

	CString cs_path = Get_registry().Value(_p_object, e_shader);
	if (cs_path.IsEmpty()) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) Get_registry().Error().Print(TError::e_print::e_req));
		return this->m_error = Get_registry().Error();
	}
	return this->Path((_pc_sz) cs_path);
}

err_code  CSrc_Cfg::Path (_pc_sz _p_path) {
	_p_path;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_path || 0 == ::_tcslen(_p_path))
		return this->m_error <<__e_inv_arg = _T("The file path is empty");

#if (1)
	// https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathfileexistsa ;
	if (false == !!::PathFileExists(_p_path)) // ::GetLastError() can be called for additional detals of the error;
		this->m_error <<__e_inv_arg << TString().Format(_T("#__e_not_valid: '_p_path' %s does not exist"), _p_path);
	else {
		this->m_prefer = e_prefer::e_file;
		this->m_path = _p_path;
	}
#endif

	return this->Error();
}


CSrc_Cfg& CSrc_Cfg::operator = (const CSrc_Cfg& _src) { *this << _src.Prefer() << _src.ResId() << _src.Path(); return *this; }

CSrc_Cfg& CSrc_Cfg::operator <<(const e_prefer _e_mode) { this->Prefer(_e_mode); return *this; }
CSrc_Cfg& CSrc_Cfg::operator <<(const uint16_t _res_id) { this->m_res_id = _res_id; return *this; }
CSrc_Cfg& CSrc_Cfg::operator <<(_pc_sz _p_path) { this->m_path = _p_path; return *this; }

/////////////////////////////////////////////////////////////////////////////

CSource:: CSource (void) : m_$_id(0) { this->m_error >> TString().Format(_T("%s::%s"), (_pc_sz) CShader::Class(), (_pc_sz)__CLASS__)<<__METHOD__<<__e_not_inited; }
CSource:: CSource (const CSource& _src) : CSource() { *this = _src; }
CSource::~CSource (void) {}

const
CSrc_Cfg& CSource::Cfg (void) const { return m_cfg; }
CSrc_Cfg& CSource::Cfg (void)       { return m_cfg; }

CString  CSource::Class (void) { return __CLASS__; }

uint32_t CSource::$Id  (void) const { return this->m_$_id; }
err_code CSource::$Id  (const uint32_t _shader_id) {
	_shader_id;
	this->m_error <<__METHOD__<<__s_ok;

	if (0 == _shader_id)
		return this->m_error << __e_inv_arg = _T("#__e_inv_val: '_shader_id' cannot be zero");

	const bool b_changed = _shader_id != this->$Id();
	if (b_changed)
		this->m_$_id = _shader_id;

	return this->Error();
}

TError&  CSource::Error (void) const { return this->m_error; }

_pc_sz   CSource::Get (void) const { return (_pc_sz)this->m_buffer; }

err_code CSource::Set (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Cfg().Is_valid()) {
		return this->m_error <<__e_not_inited = _T("Config is not set");
	}

	switch (this->Cfg().Prefer()) {
	case CSrc_Cfg::e_res: this->Load(this->Cfg().ResId(), this->$Id()); break;
	case CSrc_Cfg::e_file: this->Load(this->Cfg().Path(), this->$Id()); break;
	default:
		this->m_error << (err_code)TErrCodes::eData::eUnsupport = _T("Not supported");
	}

	return this->Error();
}

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

	if (__failed(__get_$_procs().Source(_u_shader_id, 1, &p_buffer, &n_len)))
		this->m_error = __get_$_procs().Error();

	return this->Error();
}

err_code CSource::Load (const uint16_t _res_id, const uint32_t _n_shader_id) {
	_res_id; _n_shader_id;
	this->m_error <<__METHOD__<<__s_ok;
	if (0 == _res_id)
		return this->m_error << __e_inv_arg = TString().Format(_T("String resource identifier (%u) is invalid"), _res_id);

	CString cs_src;
	cs_src.LoadString(_res_id);

	return this->Set((_pc_sz) cs_src, _n_shader_id);
}
// https://stackoverflow.com/questions/52282990/what-does-cstringgetbuffer-with-no-size-parameter-do << good discussion;
err_code CSource::Load (_pc_sz _p_path, const uint32_t _u_shader_id) {
	_p_path; _u_shader_id;
	this->m_error <<__METHOD__<<__s_ok;

	::ATL::CAtlFile file_;

	err_code h_result = __s_ok;
	ULONGLONG ul_size = 0;

	if (__failed(h_result = file_.Create(_p_path, FILE_READ_DATA, FILE_SHARE_READ, OPEN_EXISTING))) return this->m_error << h_result;
	if (__failed(h_result = file_.Seek(0, FILE_BEGIN))) return this->m_error << h_result;
	if (__failed(h_result = file_.GetSize(ul_size))) return this->m_error << h_result;

	if (this->m_buffer.IsEmpty() == false)
		this->m_buffer.ReleaseBuffer();

	CStringA src_a;

	if (__failed(h_result = file_.Read(src_a.GetBuffer(static_cast<int>(ul_size)), static_cast<uint32_t>(ul_size)))) return this->m_error << h_result;

	int32_t n_len = src_a.GetLength();

	const char* p_buffer = src_a.GetBuffer();

	if (__failed(__get_$_procs().Source(_u_shader_id, 1, &p_buffer, &n_len)))
		this->m_error = __get_$_procs().Error();
	else
		this->m_buffer = src_a; // just making the copy; it is not necessary, but for debug puposes only;

	return this->Error();
}

CSource& CSource::operator = (const CSource& _src) { this->m_buffer = _src.Get(); return *this; }
CSource& CSource::operator <<(const uint32_t _shader_id) { this->$Id(_shader_id); return *this; }