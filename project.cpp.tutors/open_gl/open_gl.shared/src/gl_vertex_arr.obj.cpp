/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Nov-2025 at 00:57:38.067, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' vertex array object wrapper interface implementation file;
*/
#include "gl_vertex_arr.obj.h"
#include "gl_procs.h"
#include "gl_renderer.h"

#include "procs\gl_procs_vertex.h"
#include "program\gl_prog_status.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vertex;

#define __gl_arr_bound 0x8894 // GL_ARRAY_BUFFER_BINDING;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl { static CArrObject inv_arr_obj; }}}}
using namespace _impl;

using CVertDat = CArrObject::CVertDat;

#pragma region cls::CArrObject{}

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
		__trace_warn_2(_T("The vertex array object (id = %u) is already bound;\n"), this->GetId());
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
		this->VertArray().Target(CPipeline::Target());
#if (0) // at this point the vertex array does not contain any data yet, no vertex yet, so setting program identifier to nothing;
		const CProgram& prog = ::Get_renderer().Scene().Progs().Get(CPipeline::Target());
		this->VertArray() << prog.Id().Get();
#endif
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
	if (__failed(this->VertArray().Delete())) this->m_error = this->VertArray().Error(); // the vertex data array and vertex buffer object error is traced;
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

bool     CArrObject::Is_bound (void) const {
	this->m_error <<__CLASS__<<__METHOD__<<__s_ok;

	/* https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGet.xhtml
	   the excerpt from the above article:
	   ...returns a single value, the name of the buffer object currently bound to the target GL_ARRAY_BUFFER.
	      If no buffer object is bound to this target, 0 is returned....
	   the following block of the code is incorrect and must be fixed;
	*/
	const int32_t n_result = __get_param_procs().GetInt(__gl_arr_bound);
	if (__get_param_procs().Error()) {
		this->m_error = __get_param_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return false;
	}
	const bool b_result = this->GetId() == static_cast<uint32_t>(n_result);
#if (0)
	if (false == b_result)
		__trace_info_2(_T("the vertex array object of '_arr_id' (%u) is not bound;\n"), this->GetId());
#endif
	return b_result;
}

err_code CArrObject::SetData (const TVertData& _v_data) {
	_v_data;
	this->m_error <<__METHOD__<<__s_ok;

	if (0 == this->GetId() || false == ::Get_renderer().Cfg().Is_drawable(this->Target()))
		return this->Error();

	if (__failed(this->Bind())) return this->Error(); // (1) tries to bind this vertex array object first;
	if (__failed(this->VertArray().Buffer().Bind())) return this->m_error = this->VertArray().Buffer().Error(); // (2) the buffer binding;

	const CProgram& prog = ::Get_renderer().Scene().Progs().Get(CPipeline::Target());
	this->VertArray() << prog.Id().Get(); // no check for errors;

	if (__failed(this->VertArray().Buffer().SetData(_v_data))) return this->m_error = this->VertArray().Buffer().Error(); // (3) defining the data format;
	if (__failed(this->VertArray().Set_ptrs())) return this->m_error = this->VertArray().Error(); // (4) setting the vertex attributes' pointers;
#if (0)
	// it is assumed that the vertex position and vertex color attributes are used; it is not a very good assumption, but it is suitable for this version of the implementation;
	if (__failed(::__get_attr_arr_procs().Enable(0))) return this->m_error = ::__get_attr_arr_procs().Error();
	if (__failed(::__get_attr_arr_procs().Enable(1))) return this->m_error = ::__get_attr_arr_procs().Error();
#endif
//	Unbinding the buffer must be made first, otherwise the error occurs :
//	[error] cls::[CTriangle].Draw()>>cls::[CError]>>{code=5023;result=0x8007139f;desc='#__e_inv_oper: vertex buffer is mapped';context=CBase::CRenderer::DrawArrays()};
//	that means: vertex array object is unbound, thus the vertex buffers sets to read-only access;
	if (__failed(CArrObject::Unbind(this->m_error))) {} // (6) sets the currently bound vao to 'default' one, i.e. no bound vertex array object;

	return this->Error();
}

err_code CArrObject::Unbind (CError& _err) {
#if (0)
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
#else
	if (__failed(__get_arr_procs().Bind(0))) {
		_err = __get_arr_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}
	return _err;
#endif
}

const
CVertDat&   CArrObject::VertArray (void) const { return this->m_vex_arr; }     
CVertDat&   CArrObject::VertArray (void)       { return this->m_vex_arr; }

CArrObject& CArrObject::operator = (const CArrObject& _src) { _src; return *this; }
CArrObject& CArrObject::operator = (CArrObject&& _victim) { *this = (const CArrObject&)_victim; return *this; }

#pragma endregion

CArrObj_enum:: CArrObj_enum (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
	m_objects[0].Target(e_object::e_grid);
	m_objects[1].Target(e_object::e_tria);
}
CArrObj_enum::~CArrObj_enum (void) {}

err_code CArrObj_enum::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	const render::CCfg& cfg = ::Get_renderer().Cfg();

	for (uint32_t i_ = 0; i_ < CPipeline::u_tgt_count; i_++) {
		CArrObject& object = this->Ref(i_);
		if (false == cfg.Is_drawable(object.Target()))
			continue;
		if (__failed(object.Create())) { this->m_error = object.Error(); break; }
	//	if (__failed(object.Bind()))   { this->m_error = object.Error(); break; }
	}

	return this->Error();
}

TError& CArrObj_enum::Error (void) const { return this->m_error; }

using CArrObj = CArrObj_enum::CArrObj;

const
CArrObj&   CArrObj_enum::Get (const e_object _u_target) const {
	_u_target;
	if (e_object::e_grid == _u_target) return this->m_objects[0];
	if (e_object::e_tria == _u_target) return this->m_objects[1];
	return _impl::inv_arr_obj;
}

CArrObj&   CArrObj_enum::Get (const e_object _u_target) {
	_u_target;
	if (e_object::e_grid == _u_target) return this->m_objects[0];
	if (e_object::e_tria == _u_target) return this->m_objects[1];
	return _impl::inv_arr_obj;
}

const
CArrObj& CArrObj_enum::Ref (const uint32_t _u_ndx) const { if (_countof(this->m_objects) > _u_ndx) return this->m_objects[_u_ndx]; else return _impl::inv_arr_obj; }
CArrObj& CArrObj_enum::Ref (const uint32_t _u_ndx)       { if (_countof(this->m_objects) > _u_ndx) return this->m_objects[_u_ndx]; else return _impl::inv_arr_obj; }