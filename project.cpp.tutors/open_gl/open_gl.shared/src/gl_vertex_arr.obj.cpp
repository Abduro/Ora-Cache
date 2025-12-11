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

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	static CArrObject inv_arr_obj;

}}}}
using namespace _impl;

using CVertDat = CArrObject::CVertDat;

#pragma region cls::CArrObject

CArrObject:: CArrObject (void) : m_arr_id(0) { this->m_error <<__CLASS__<<__METHOD__<<__e_not_inited; }
CArrObject:: CArrObject (const CArrObject& _src) : CArrObject() { *this = _src; }
CArrObject:: CArrObject (CArrObject&& _victim) : CArrObject() { *this = _victim; }
CArrObject::~CArrObject (void) {}

err_code CArrObject::Bind (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (this->Is_bound()) {
#if (0) // no error is set, the array is already bound, so just returns __s_ok;
		this->m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("the array of '_arr_id' (%u) is already bound"), this->GetId());
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
#else
		__trace_warn(_T("The vertex array object (id = %u) is already bound;\n"), this->GetId());
#endif
		return this->Error();
	}
	if (__failed(__get_arr_procs().Bind(this->GetId()))) {
		this->m_error = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
#if (1)
		__trace_info_2(_T("The vertex array object (id = %u) is bound;\n"), this->GetId());
#endif
	}
	return this->Error();
}

bool     CArrObject::Is_bound (void) const {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	const int32_t n_result = __get_param_procs().GetInt(__gl_arr_bound);
	if (__get_param_procs().Error()) {
		this->m_error = __get_param_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return false;
	}
	const bool b_result = this->GetId()== static_cast<uint32_t>(n_result);
#if (0)
	if (false == b_result)
		__trace_info_2(_T("the vertex array object of '_arr_id' (%u) is not bound;\n"), this->GetId());
#endif
	return b_result;
}

err_code CArrObject::Create (void) {
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
	else if (__failed(this->VertArray().Create())) {
		this->m_error = this->VertArray().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_impt_2(_T("The vertex array object (id = %u) is created;\n"), this->m_arr_id);
	}
	return this->Error();
}

err_code CArrObject::Delete (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (0 == this->GetId())  // if the array is not created yet success is returned and just keeping the silence;
		return this->Error();
	/* it looks like this operation is not required because when the object is being deleted it will be unbound automatically;
	   the excerpt from https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml :
	   ...if a vertex array object that is currently bound is deleted, the binding for that object reverts to zero and the default vertex array becomes current...
	*/
#if (0)
	if (this->Is_bound()) {
	    this->Unbind();
	}
#endif
	if (__failed(__get_arr_procs().Delete(1, &this->m_arr_id))) {
		this->m_error = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_warn_2(_T("The vertex array object (id = %u) is deleted;\n"), this->m_arr_id);
		this->m_arr_id = 0;
	}
	return this->Error();
}

TError&  CArrObject::Error (void) const { return this->m_error; }

uint32_t CArrObject::GetId (void) const { return this->m_arr_id; }

err_code CArrObject::Unbind (void) {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	if (false == this->Is_bound()) {
		__trace_info_2(_T("The vertex array object (id = %u) is not bound;\n"), this->GetId());
		return this->Error();
	}
	if (__failed(__get_arr_procs().Bind(0))) {
		this->m_error = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else
		__trace_info_2(_T("The vertex array object (id = %u) is unbound;\n"), this->GetId());

	return this->Error();
}

const
CVertDat& CArrObject::VertArray (void) const { return this->m_vex_arr; }     
CVertDat& CArrObject::VertArray (void)       { return this->m_vex_arr; }

CArrObject& CArrObject::operator = (const CArrObject& _src) { _src; return *this; }
CArrObject& CArrObject::operator = (CArrObject&& _victim) { *this = (const CArrObject&)_victim; return *this; }

#pragma endregion

CArrObj_enum:: CArrObj_enum (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CArrObj_enum::~CArrObj_enum (void) {}

err_code CArrObj_enum::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	for (uint32_t i_ = 0; i_ < CArrObj_enum::u_count; i_++) {
		CArrObj& object = this->Get((CArrObj_enum::e_arr_ndx)i_);

		if (__failed(object.Create())) { this->m_error = object.Error(); break; }
		if (__failed(object.Bind()))   { this->m_error = object.Error(); break; }
	}

	return this->Error();
}

TError& CArrObj_enum::Error (void) const { return this->m_error; }

using CArrObj = CArrObj_enum::CArrObj;

const
CArrObj&   CArrObj_enum::Get (const e_arr_ndx _ndx) const {
	_ndx;
	if (e_arr_ndx::e_grid == _ndx) return this->m_arr_objs[_ndx];
	if (e_arr_ndx::e_tria == _ndx) return this->m_arr_objs[_ndx];
	return _impl::inv_arr_obj;
}

CArrObj&   CArrObj_enum::Get (const e_arr_ndx _ndx) {
	_ndx;
	if (e_arr_ndx::e_grid == _ndx) return this->m_arr_objs[_ndx];
	if (e_arr_ndx::e_tria == _ndx) return this->m_arr_objs[_ndx];
	return _impl::inv_arr_obj;
}