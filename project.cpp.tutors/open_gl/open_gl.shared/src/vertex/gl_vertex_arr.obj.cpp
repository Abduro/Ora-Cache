/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Nov-2025 at 00:57:38.067, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' vertex array object wrapper interface implementation file;
*/
#include "gl_vertex_arr.obj.h"
#include "gl_procs.h"
#include "procs\gl_procs_vertex.h"
#include "program\gl_prog_status.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vertex;

#define __gl_arr_bound 0x8894 // GL_ARRAY_BUFFER_BINDING;

#pragma region _vert_array

vertex::CArrObject:: CArrObject (void) : m_arr_id(0) { this->m_error <<__CLASS__<<__METHOD__<<__e_not_inited; }
vertex::CArrObject:: CArrObject (const CArrObject& _src) : CArrObject() { *this = _src; }
vertex::CArrObject:: CArrObject (CArrObject&& _victim) : CArrObject() { *this = _victim; }
vertex::CArrObject::~CArrObject (void) {}

const
CAttrArray& vertex::CArrObject::Attrs (void) const { return this->m_attrs; }
CAttrArray& vertex::CArrObject::Attrs (void)       { return this->m_attrs; }

err_code vertex::CArrObject::Bind (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (this->Is_bound()) {
#if (0) // no error is set, the array is already bound, so just returns __s_ok;
		this->m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("the array of '_arr_id' (%u) is already bound"), this->GetId());
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
#else
		__trace_warn(_T("The array (id = %u) is already bound;\n"), this->GetId());
#endif
		return this->Error();
	}
	if (__failed(__get_arr_procs().Bind(this->GetId()))) {
		this->m_error = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_info_2(_T("The array (id = %u) is bound;\n"), this->GetId());
	}
	return this->Error();
}

bool vertex::CArrObject::Is_bound (void) const {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	const int32_t n_result = __get_param_procs().GetInt(__gl_arr_bound);
	if (__get_param_procs().Error()) {
		this->m_error = __get_param_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return false;
	}
	const bool b_result = this->GetId()== static_cast<uint32_t>(n_result);
	if (false == b_result)
		__trace_info_2(_T("the array of '_arr_id' (%u) is not bound;\n"), this->GetId());

	return b_result;
}

err_code vertex::CArrObject::Create (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (!!this->GetId()) {
		this->m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(_T("#__e_inv_state: array (id = %u) already exists"), this->GetId());
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}
	if (__failed(__get_arr_procs().GetIds(1, &this->m_arr_id))) {
		this->m_error = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_impt_2(_T("The vertex array (id = %u) is created;\n"), this->m_arr_id);
	}
	return this->Error();
}

err_code vertex::CArrObject::Delete (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (0 == this->GetId())  // if the array is not created yet success is returned and just keeping the silence;
		return this->Error();

	if (__failed(__get_arr_procs().Delete(1, &this->m_arr_id))) {
		this->m_error = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_warn_2(_T("The vertex array (id = %u) is deleted;\n"), this->m_arr_id);
		this->m_arr_id = 0;
	}
	return this->Error();
}

err_code vertex::CArrObject::Enable (const bool _b_state) {
	_b_state;
	this->m_error <<__METHOD__<<__s_ok;

	CAttr* attrs[] = { &this->Attrs().Clr(), &this->Attrs().Pos() };

	for (uint32_t i_ = 0; i_ < _countof(attrs); i_++) {
		const int32_t n_att_ndx = attrs[i_]->Locate().Value();
		if (_b_state) {
			if (__failed(__get_attr_procs().Enable(this->GetId(), n_att_ndx))) {
				this->m_error = __get_attr_procs().Error();
				__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			}
			else {
				__trace_info_2(_T("The attr (ndx = %u) of the array (id = %u) is enabled;\n"), n_att_ndx, this->GetId());
			}
		}
		else {
			if (__failed(__get_attr_procs().Disable(this->GetId(), n_att_ndx))) {
				this->m_error = __get_attr_procs().Error();
				__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			}
			else {
				__trace_info_2(_T("The attr (ndx = %u) of the array (id = %u) is disabled;\n"), n_att_ndx, this->GetId());
			}
		}
	}

	return this->Error();
}

TError&  vertex::CArrObject::Error (void) const { return this->m_error; }

uint32_t vertex::CArrObject::GetId (void) const { return this->m_arr_id; }

err_code vertex::CArrObject::Unbind (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (false == this->Is_bound()) {
		__trace_info_2(_T("The array id = %u is not bound;\n"), this->GetId());
		return this->Error();
	}
	if (__failed(__get_arr_procs().Bind(0))) {
		this->m_error = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else
		__trace_info_2(_T("The array id = %u is unbound;\n"), this->GetId());

	return this->Error();
}

CArrObject& CArrObject::operator = (const CArrObject& _src) { this->Attrs() = _src.Attrs(); return *this; }
CArrObject& CArrObject::operator = (CArrObject&& _victim) { *this = (const CArrObject&)_victim; return *this; }

#pragma endregion