/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Dec-2025 at 11:29:19.429, UTC+4, Batumi, Tuesday;
	This Ebo Pack OpenGL shader variable uniform data type wrapper interface implementation file;
*/
#include "gl_uniform.h"
#include "gl_renderer.h"
#include "gl_prog_id.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

#include "gl_procs_prog.h"
#include "gl_procs_uniform.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vars;

using CProgId = program::CProgId;

using e_iface = procs::program::e_interface;
using e_prop = procs::program::e_property;

enum class e_ndx : uint32_t { e_name = 0, e_type, e_loc, e_bloc }; // for reference to value vector elements;

procs::program::TRawProps props = {e_prop::e_name_len, e_prop::e_type, e_prop::e_location, e_prop::e_block_ndx};
procs::program::TRawValues values(props.size());

#pragma region cls::CU_bas_0x0{}

CU_bas_0x0::CU_bas_0x0 (const e_object _target) : TPipe(_target), m_index (0) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CU_bas_0x0::CU_bas_0x0 (const CU_bas_0x0& _src) : CU_bas_0x0(_src.Target()) { *this = _src; }
CU_bas_0x0::CU_bas_0x0 (CU_bas_0x0&& _victim) : CU_bas_0x0(_victim.Target()) { *this = _victim; }

TError&  CU_bas_0x0::Error (void) const { return this->m_error; }

bool CU_bas_0x0::Is_valid (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	const uint32_t u_count = CU_vars_enum::Count(TPipe::Target(), this->m_error);
	
	if (this->m_index >= u_count)
		this->m_error << __e_inv_arg = TString().Format(_T("#__e_inv_arg: _value (%u) is out of range (%u)"), this->m_index, u_count);
	
	return false == this->Error();
}

uint32_t CU_bas_0x0::Locate (void) const { return this->m_index; }
bool     CU_bas_0x0::Locate (const uint32_t _u_ndx) {
	_u_ndx;
	const bool b_changed = this->Locate() != _u_ndx; if (b_changed) this->m_index = _u_ndx; return b_changed;
}

CU_bas_0x0& CU_bas_0x0::operator = (const CU_bas_0x0& _src) { (TPipe&)*this = (const TPipe&)_src; this->m_error = _src.Error(); return *this; }
CU_bas_0x0& CU_bas_0x0::operator = (CU_bas_0x0&& _victim) { *this = (const CU_bas_0x0&)_victim; return *this; }
CU_bas_0x0& CU_bas_0x0::operator <<(const uint32_t _locate) { this->Locate(_locate); return *this; }

#pragma endregion
#pragma region cls::CU_frm_0x0{}

CU_frm_0x0::CU_frm_0x0 (const e_object _target) : TBase(_target) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CU_frm_0x0::CU_frm_0x0 (const CU_frm_0x0& _src) : CU_frm_0x0() { *this = _src; }
CU_frm_0x0::CU_frm_0x0 (CU_frm_0x0&& _victim) : CU_frm_0x0() { *this = _victim; }

bool CU_frm_0x0::Is_valid (void) const {
	const bool b_valid = TBase::Is_valid() && !!this->m_name.GetLength(); return b_valid;
}

_pc_sz   CU_frm_0x0::Name (void) const { return (_pc_sz) this->m_name; }
bool     CU_frm_0x0::Name (_pc_sz _p_name) {
	_p_name;
	const bool b_changed = !!this->m_name.CompareNoCase(_p_name); if (b_changed) this->m_name = _p_name; return b_changed;
}
err_code CU_frm_0x0::Query_name (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (false == TBase::Is_valid()) {
		return this->Error();
	}

	const CProgram& prog = ::Get_renderer().Scene().Progs().Get(TBase::Target());

	if (__failed(::__get_res_procs().GetName(prog.Id().Get(), e_iface::e_uniform, TBase::Locate(), this->m_name))) {
		TBase::m_error = ::__get_res_procs().Error();
	}

	return this->Error();
}

CU_frm_0x0& CU_frm_0x0::operator = (const CU_frm_0x0& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Name(); return *this; }
CU_frm_0x0& CU_frm_0x0::operator = (CU_frm_0x0&& _victim) { *this = (const CU_frm_0x0&)_victim; return *this; }
CU_frm_0x0& CU_frm_0x0::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }
CU_frm_0x0& CU_frm_0x0::operator <<(const CString& _cs_name) { *this << (_pc_sz)_cs_name; return *this; }

#pragma endregion
#pragma region cls::CU_val_0x0{}

CU_val_0x0::CU_val_0x0 (const e_object _target) : TBase(_target) { TBase::m_error >>__CLASS__; }
CU_val_0x0::CU_val_0x0 (const CU_val_0x0& _src) : CU_val_0x0(_src.Target()) { *this = _src; }
CU_val_0x0::CU_val_0x0 (CU_val_0x0&& _victim) : CU_val_0x0() { *this = _victim; }

bool CU_val_0x0::Is_valid (void) const { return !!this->Type().Get() && TBase::Is_valid(); }

const
CType& CU_val_0x0::Type (void) const { return this->m_type; }
CType& CU_val_0x0::Type (void)       { return this->m_type; }

CU_val_0x0& CU_val_0x0::operator = (const CU_val_0x0& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Type(); return *this; }
CU_val_0x0& CU_val_0x0::operator = (CU_val_0x0&& _victim) { *this = (const CU_val_0x0&)_victim; return *this; }
CU_val_0x0& CU_val_0x0::operator <<(const CType& _type) { this->Type() = _type; return *this; }

#pragma endregion
#pragma region cls::CU_val_v3{}

CU_val_v3::CU_val_v3 (const e_object _target) : TBase(_target) { TBase::m_error >>__CLASS__; }
CU_val_v3::CU_val_v3 (const CU_val_v3& _src) : CU_val_v3(_src.Target()) { *this = _src; }
CU_val_v3::CU_val_v3 (CU_val_v3&& _victim) : CU_val_v3(_victim.Target()) { *this = _victim; }

const
t_uniform_3f& CU_val_v3::Data (void) const { return this->m_data; }
t_uniform_3f& CU_val_v3::Data (void)       { return this->m_data; }

err_code CU_val_v3::Get (void) {
	TBase::m_error <<__METHOD__<<__s_ok; return CU_val_v3::Get(TBase::Target(), TBase::Locate(), this->Data(), TBase::m_error);
}
err_code CU_val_v3::Get (const e_object _target, const uint32_t _u_locate, t_uniform_3f& _data, CError& _err) {
	_target; _u_locate; _data; _err;

	const CProgram& prog = ::Get_renderer().Scene().Progs().Get(_target);

	if (__failed(::__get_uni_val_procs().Get_3fs(prog.Id().Get(), _u_locate, _data))) {
		_err = ::__get_uni_val_procs().Error();
	}
	else {}

	return _err;
}

CU_val_v3& CU_val_v3::operator = (const CU_val_v3& _src) { (TBase&)*this = (const TBase&)_src; return *this; }
CU_val_v3& CU_val_v3::operator = (CU_val_v3&& _victim) { *this = (const CU_val_v3&)_victim; return *this; }
CU_val_v3& CU_val_v3::operator <<(const t_uniform_3f& _data) { this->Data() = _data; return *this; }

#pragma endregion
#pragma region cls::CU_val_v4{}

CU_val_v4::CU_val_v4 (const e_object _target) : TBase(_target) { TBase::m_error >>__CLASS__; TBase::Type() << (uint32_t) procs::e_att_val_vec::e_float_vec4; }
CU_val_v4::CU_val_v4 (const CU_val_v4& _src) : CU_val_v4(_src.Target()) { *this = _src; }
CU_val_v4::CU_val_v4 (CU_val_v4&& _victim) : CU_val_v4(_victim.Target()) { *this = _victim; }

const
t_uniform_4f& CU_val_v4::Data (void) const { return this->m_data; }
t_uniform_4f& CU_val_v4::Data (void)       { return this->m_data; }

err_code CU_val_v4::Get (void) {
	TBase::m_error <<__METHOD__<<__s_ok; return CU_val_v4::Get(TBase::Target(), TBase::Locate(), this->Data(), TBase::m_error);
}
err_code CU_val_v4::Get (const e_object _target, const uint32_t _u_locate, t_uniform_4f& _data, CError& _err) {
	_target; _u_locate; _data; _err;

	const CProgram& prog = ::Get_renderer().Scene().Progs().Get(_target);

	if (__failed(::__get_uni_val_procs().Get_4fs(prog.Id().Get(), _u_locate, _data))) {
		_err = ::__get_uni_val_procs().Error();
	}
	else {}

	return _err;
}

CU_val_v4& CU_val_v4::operator = (const CU_val_v4& _src) { (TBase&)*this = (const TBase&)_src; return *this; }
CU_val_v4& CU_val_v4::operator = (CU_val_v4&& _victim) { *this = (const CU_val_v4&)_victim; return *this; }
CU_val_v4& CU_val_v4::operator <<(const t_uniform_4f& _data) { this->Data() = _data; return *this; }

#pragma endregion
#pragma region cls::CU_frm_v4{}

CU_frm_v4::CU_frm_v4 (const e_object _target) : TBase(_target), m_vec4(_target) { TBase::m_error >>__CLASS__; }
CU_frm_v4::CU_frm_v4 (const CU_frm_v4& _src) : CU_frm_v4(_src.Target()) { *this = _src; }
CU_frm_v4::CU_frm_v4 (CU_frm_v4&& _victim) : CU_frm_v4(_victim.Target()) { *this = _victim; }

bool CU_frm_v4::Locate (const uint32_t _u_ndx) {
	_u_ndx;
	bool b_changed = false;
	if (TBase::Locate(_u_ndx)) b_changed = true;
	if (this->Vec4().Locate(_u_ndx)) b_changed = true;

	return b_changed;
}

const
CU_val_v4& CU_frm_v4::Vec4 (void) const { return this->m_vec4; }
CU_val_v4& CU_frm_v4::Vec4 (void)       { return this->m_vec4; }

CU_frm_v4& CU_frm_v4::operator = (const CU_frm_v4& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Vec4();  return *this; }
CU_frm_v4& CU_frm_v4::operator = (CU_frm_v4&& _victim) { *this = (const CU_frm_v4&)_victim; return *this; }
CU_frm_v4& CU_frm_v4::operator <<(const CU_val_v4& _vec4) { this->Vec4() = _vec4; return *this; }

#pragma endregion
#pragma region cls::vars::CU_vars_enum{}

CU_vars_enum:: CU_vars_enum (const e_object _target) : TPipe(_target) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CU_vars_enum::~CU_vars_enum (void) {}

uint32_t CU_vars_enum::Count (void) const {
	this->m_error <<__METHOD__<<__s_ok;
#if (0)
	const CProgram& prog = ::Get_renderer().Scene().Progs().GetActive(); // the active program may not have the required target object type;
	if (false == prog.Is_valid()) {
		this->m_error = ::Get_renderer().Scene().Progs().Error(); // the error is traced;
		return 0;
	}
#endif
	return CU_vars_enum::Count(TPipe::Target(), this->m_error);
}

uint32_t CU_vars_enum::Count (const e_object _target,  CError& _err) {
	_target; _err;
	uint32_t u_result = 0;

	const CProgram& prog = ::Get_renderer().Scene().Progs().Get(_target);
	const uint32_t prog_id = prog.Id();

	if (false == program::CProgId::Is_valid(prog_id, _err))
		return u_result;

#define __use_prior_ver 0
	// this is the approach of getting program uniform variables' count in:
	// OpenGL 3.0+ version;
#if (__use_prior_ver != 0)
	using e_uni_params = procs::program::e_uniform_params;

	if (__failed(::__get_prog_procs().Params(prog_id, (uint32_t)e_uni_params::e_active, &u_result))) {
		_err = ::__get_prog_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}
#else
	// OpenGL 4.3+ or ARB_program_interface_query extension;
	using e_interface = procs::program::e_interface;
	using e_property  = procs::program::e_property;

	if (__failed(::__get_iface_procs().Get(prog_id, e_interface::e_uniform, e_property::e_active_res, u_result))) {
		_err = __get_iface_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}
#endif
	return u_result;
}

TError&  CU_vars_enum::Error (void) const { return this->m_error; }

err_code CU_vars_enum::Get (const e_object _target, TU_vars_v4& _vars, CError& _err) {
	_target; _vars; _err;

	if (_vars.empty() == false)
		_vars.clear();

	// (1) gets uniform variables number through the program interface object;
	uint32_t u_vars_count = CU_vars_enum::Count(_target, _err);
	if (0 == u_vars_count)
		return _err; // no errors and no variables;

	// (2) reserving a vector items number is not good idea, an error may occur and the vector will contain vars that are empty and not valid;
#if (0)
	try {
	_vars.resize(u_vars_count); _vars.reserve(u_vars_count);
	} catch (const ::std::bad_alloc&) {
		_err << __e_no_memory; return _err;
	}
#endif
	const CProgram& prog = ::Get_renderer().Scene().Progs().Get(_target);
	const uint32_t prog_id = prog.Id();

	for (uint32_t i_ = 0; i_ < u_vars_count; i_++) {
		if (__failed(::__get_res_procs().GetValues(prog_id, e_iface::e_uniform, i_, props, values))) {
			_err = ::__get_res_procs().Error(); break;
		}
#if (0) // the variable is still of interest, at least for testing purposes;
		// skips uniforms that are part of a named uniform block, as they are handled separately;
		if (-1 == values.at(3)) // to-do: hard coded index value is not good;
			continue;
#endif
		CU_frm_v4 u_form(_target); u_form.Locate(i_); // just sets the location/index of the variable; calling 'Is_valid()' is unnecessary yet; 
		
		if (__failed(u_form.Query_name())) {
			_err = u_form.Error(); break;
		}
		u_form.Vec4().Type() << (uint32_t) values.at((uint32_t)e_ndx::e_type); // data type can be converted to 'unsigned', no negative value is expected;
		if (__failed(u_form.Vec4().Get())) { // the location and draw target type is already set (at least must be set);
			_err = u_form.Vec4().Error(); break;
		}

		try {
			_vars.push_back(u_form);
		} catch (const ::std::bad_alloc&) {
			_err << __e_no_memory; break;
		}
	}
	return _err;
}

#pragma endregion