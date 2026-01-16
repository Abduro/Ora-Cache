/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Dec-2025 at 11:29:19.429, UTC+4, Batumi, Tuesday;
	This Ebo Pack OpenGL shader variable uniform data type wrapper interface implementation file;
*/
#include "gl_uniform.h"
#include "gl_renderer.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

#include "gl_procs_prog.h"
#include "gl_procs_uniform.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vars;

using CValue = CUniform::CValue;
using CProgId = program::CProgId;

#pragma region cls::CUniform::CValue{}

CValue::CValue (CUniform* _p_form) : m_p_form(_p_form) {}
CValue::CValue (const CValue& _src) : CValue(_src.m_p_form) { *this = _src; }
CValue::CValue (CValue&& _victim) : CValue() { *this = _victim; }

TError& CValue::Error (void) const { return this->m_error; }

err_code CValue::Get (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == this->m_p_form)
		return this->m_error << __e_pointer = _T("#__e_not_inited: the pointer to uniform var is not set");

	const uint32_t prog_id = ::Get_renderer().Scene().Progs().Get(this->m_p_form->Target()).Id().Get();

	switch (this->Type().Get()) {
	case (uint32_t)procs::e_att_val_vec::e_float_vec3: {

		using t_uniform_3f = procs::vars::t_uniform_3f; t_uniform_3f v_values = {0.0f};

		if (__failed(::__get_uni_val_procs().Get_3fs(prog_id, this->m_p_form->Locate(), v_values))) {
			this->m_error = ::__get_uni_val_procs().Error();
			__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		}
	} break;
	case (uint32_t)procs::e_att_val_vec::e_float_vec4: {

		using t_uniform_4f = procs::vars::t_uniform_4f; t_uniform_4f v_values = {0.0f};

		if (__failed(::__get_uni_val_procs().Get_4fs(prog_id, this->m_p_form->Locate(), v_values))) {
			this->m_error = ::__get_uni_val_procs().Error();
			__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		}
	} break;
	default:;
	}

	return this->Error();
}

const
CType&  CValue::Type (void) const { return this->m_type; }
CType&  CValue::Type (void)       { return this->m_type; }

CValue& CValue::operator = (const CValue& _src) { *this << _src.Type(); this->m_error = _src.Error(); return *this; }
CValue& CValue::operator = (CValue&& _victim) { _victim; return *this; }

CValue& CValue::operator <<(const CType& _type) { this->Type() = _type; return *this; }

#pragma endregion
#pragma region cls::vars::CUniform{}

CUniform:: CUniform (const e_object _target) : TPipe(_target), m_value(this), m_index(u_inv_ndx) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CUniform:: CUniform (const CUniform& _src) : CUniform() { *this = _src; }
CUniform:: CUniform (CUniform&& _victim) : CUniform() { *this = _victim; }
CUniform::~CUniform (void) {}

TError&    CUniform::Error (void) const { return this->m_error; }

_pc_sz  CUniform::Name (void) const { return (_pc_sz) this->m_name; }
bool    CUniform::Name (_pc_sz _p_name) {
	_p_name;
	const bool b_changed = !!this->m_name.CompareNoCase(_p_name); if (b_changed) this->m_name = _p_name; return b_changed;
}

uint32_t CUniform::Locate (void) const { return this->m_index; }
bool     CUniform::Locate (const uint32_t _u_ndx) {
	_u_ndx;
	const bool b_changed = this->Locate() != _u_ndx; if (b_changed) this->m_index = _u_ndx; return b_changed;
}

const
CValue& CUniform::Value (void) const { return this->m_value; }
CValue& CUniform::Value (void)       { return this->m_value; }

CUniform&  CUniform::operator = (const CUniform& _src) {
	(TPipe&)*this = (const TPipe&)_src; *this << _src.Name() << _src.Value() << _src.Locate(); return *this;
}
CUniform&  CUniform::operator = (CUniform&& _victim) { *this = (const CUniform&)_victim; return *this; }

CUniform&  CUniform::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }
CUniform&  CUniform::operator <<(const CValue& _val) { this->Value() = _val; return *this; }
CUniform&  CUniform::operator <<(const uint32_t _u_ndx) { this->Locate(_u_ndx); return *this; }

const
TPipe& CUniform::operator ()(void) const { return (TPipe&)*this; }
TPipe& CUniform::operator ()(void)       { return (TPipe&)*this; }

#pragma endregion
#pragma region cls::vars::CUniform_enum{}

CUniform_enum:: CUniform_enum (const e_object _target) : TPipe(_target) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CUniform_enum::~CUniform_enum (void) {}

uint32_t CUniform_enum::Count (void) const {
	this->m_error <<__METHOD__<<__s_ok;
#if (0)
	const CProgram& prog = ::Get_renderer().Scene().Progs().GetActive(); // the active program may not have the required target object type;
	if (false == prog.Is_valid()) {
		this->m_error = ::Get_renderer().Scene().Progs().Error(); // the error is traced;
		return 0;
	}
#endif
	return CUniform_enum::Count(TPipe::Target(), this->m_error);
}

uint32_t CUniform_enum::Count (const e_object _target,  CError& _err) {
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

TError&  CUniform_enum::Error (void) const { return this->m_error; }

err_code CUniform_enum::Get (const e_object _target, TUniVars& _vars, CError& _err) {
	_target; _vars; _err;

	if (_vars.empty() == false)
		_vars.clear();

	// (1) gets uniform variables number through the program interface object;
	uint32_t u_vars_count = CUniform_enum::Count(_target, _err);
	if (0 == u_vars_count)
		return _err; // no errors and no variables;

	using e_iface = procs::program::e_interface;
	using e_prop = procs::program::e_property;

	enum class e_ndx : uint32_t { e_name = 0, e_type, e_loc, e_bloc }; // for reference to value vector elements;

	procs::program::TRawProps props = {e_prop::e_name_len, e_prop::e_type, e_prop::e_location, e_prop::e_block_ndx};
	procs::program::TRawValues values(props.size());
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
		CString cs_name;
		if (__failed(::__get_res_procs().GetName(prog_id, e_iface::e_uniform, i_, cs_name))) {
			_err = ::__get_res_procs().Error(); break;
		}

		CUniform u_form; u_form.Name((_pc_sz)cs_name);
#if (0)
		try {
			_vars.at(i_) = u_form;
		} catch (const ::std::out_of_range&) {
			_err << __e_index; break;
		}
#else
		try {
			u_form.Value().Type() << (uint32_t) values.at((uint32_t)e_ndx::e_type); // data type can be converted to 'unsigned', no negative value is expected;
			u_form << i_;         // sets the index/location of the variable;
			u_form() << _target;  // sets the draw target object type;

			u_form.Value().Get(); // this method may generate an error, the value object saves the error state;

			_vars.push_back(u_form);
		} catch (const ::std::bad_alloc&) {
			_err << __e_no_memory; break;
		}
#endif
	}

	return _err;
}

#pragma endregion