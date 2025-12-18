/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Oct-2025 at 21:59:45.986, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL data buffer wrapper interface implementation file;
*/
#include "gl_buffer.h"
#include "shared.dbg.h"
#include "shared.preproc.h"
#include "gl_procs.h"
#include "procs\gl_procs_buffer.h"
#include "procs\gl_procs_surface.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::data;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {
}}}}

#define __gl_bound_to_arr 0x8894 // GL_ARRAY_BUFFER_BINDING;

using namespace ex_ui::draw::open_gl::_impl;

/////////////////////////////////////////////////////////////////////////////
#pragma region vertex::cls::CCfg{}
data::CCfg:: CCfg (void) : m_count_ndx(0), m_prim_mode((uint32_t)procs::CPrimitives::e_others::e_points), m_start_ndx(0) {}

uint32_t data::CCfg::Count (void) const { return this->m_count_ndx; }
bool     data::CCfg::Count (const uint32_t _n_count) {
	_n_count;
	const bool b_changed = (this->Count() != _n_count);
	if (b_changed)
		this->m_count_ndx = _n_count;
	return b_changed;
}

uint32_t data::CCfg::Primitive (void) const { return this->m_prim_mode; }
bool     data::CCfg::Primitive (const uint32_t _u_mode) {
	_u_mode;
	const bool b_changed = (this->Primitive() != _u_mode);
	if (b_changed)
		this->m_prim_mode = _u_mode;
	return b_changed;
}

uint32_t data::CCfg::StartAt (void) const { return this->m_start_ndx; }
bool     data::CCfg::StartAt (const uint32_t _u_ndx) {
	_u_ndx;
	const bool b_changed = (this->StartAt() != _u_ndx);
	if (b_changed)
		this->m_start_ndx = _u_ndx;
	return b_changed;
}

CString  CTarget::To_str (const e_bind_targets _e_target) {
	_e_target;
	CString cs_out;
	switch (_e_target) {
	case e_bind_targets::e_array   : cs_out = _T("$__gl_array"); break;
	case e_bind_targets::e_counter : cs_out = _T("$__gl_counter"); break;
	case e_bind_targets::e_read    : cs_out = _T("$__gl_copy_read"); break;
	case e_bind_targets::e_write   : cs_out = _T("$__gl_copy_write"); break;
	case e_bind_targets::e_disp    : cs_out = _T("$__gl_disp_inderect"); break;
	case e_bind_targets::e_draw    : cs_out = _T("$__gl_draw_indirect"); break;
	case e_bind_targets::e_el_arr  : cs_out = _T("$__gl_element_arr"); break;
	case e_bind_targets::e_pxl_pk  : cs_out = _T("$__gl_pixel_pack"); break;
	case e_bind_targets::e_pxl_unpk: cs_out = _T("$__gl_pixel_unpack"); break;
	case e_bind_targets::e_query   : cs_out = _T("$__gl_query"); break;
	case e_bind_targets::e_$_stg   : cs_out = _T("$__gl_shader_stg"); break;
	case e_bind_targets::e_texture : cs_out = _T("$__gl_texture"); break;
	case e_bind_targets::e_trans   : cs_out = _T("$__gl_transform"); break;
	case e_bind_targets::e_uniform : cs_out = _T("$__gl_uniform"); break;
	default:
		cs_out = _T("#undef");
	}
	return  cs_out;
}
#pragma endregion
#if (0)
CBuffer_Base::CBinder:: CBinder (CBuffer_Base& _buf) : m_buffer(_buf) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CBuffer_Base::CBinder::~CBinder (void) {}

TError&  CBuffer_Base::CBinder::Error (void) const { return this->m_error; }
#endif
/////////////////////////////////////////////////////////////////////////////

CBuffer_Base:: CBuffer_Base (void) : m_buf_id(0), m_target(e_bind_targets::e__undef) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CBuffer_Base::~CBuffer_Base (void) {}

err_code  CBuffer_Base::BindTo (const e_bind_targets _e_target) {
	this->m_error <<__METHOD__<<__s_ok;

	if (e_bind_targets::e__undef == _e_target) {
		this->m_error <<__e_inv_arg = _T("#__e_inv_arg: '_e_target' is undefined");
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}

	if (false == this->Is_valid()) {
		this->m_error <<__e_not_inited = _T("#__e_inv_state: the buffer is not created");
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}

	if (__failed(__get_buf_procs().Bind((uint32_t)_e_target, this->GetId()))) {
		this->m_error = __get_buf_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		this->m_target = _e_target;
		__trace_info_2(_T("The buffer (id = %u) is bound to target = '%s';\n"), this->GetId(), (_pc_sz) data::CTarget::To_str(_e_target));
	}

	return this->Error();
}

err_code  CBuffer_Base::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (!!this->GetId())
		return this->m_error << (err_code) TErrCodes::eObject::eExists = _T("The buffer is already created");

	if (__failed(__get_buf_procs().GenerateIds(1, &this->m_buf_id))) {
		this->m_error = __get_buf_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else __trace_impt_2(_T("The buffer (id = %u) is created;\n"), this->GetId());

	return this->Error();
}

err_code  CBuffer_Base::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;
#if (0) // no check for binding is required here, the unbinding must be made outside of this procedure;
	if (false == this->Is_bound()) {
		if (this->Error()) {
			__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			return this->Error();
		}
		else {
			__trace_info_2(_T("The buffer (id = %u) is not bound; nothing to delete;\n"), this->GetId());
		}
	}
#endif
	if (false == this->Is_valid()) // no error this time, just returning the success code;
		return this->Error();

	if (__failed(__get_buf_procs().Delete(1, &this->m_buf_id))) { // ToDo: perhaps the buffer identifier should be set to zero, but under specific circumstances it is cannot be made;
		this->m_error = __get_buf_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_warn_2(_T("The buffer (id = %u) is deleted;\n"), this->GetId());
		this->m_buf_id = 0;
	}
	return this->Error();
}

const
data::CCfg& CBuffer_Base::Cfg (void) const { return this->m_cfg; }
data::CCfg& CBuffer_Base::Cfg (void)       { return this->m_cfg; }

TError&   CBuffer_Base::Error (void) const { return this->m_error; }

uint32_t  CBuffer_Base::GetId (void) const { return this->m_buf_id; }

bool  CBuffer_Base::Is_bound (void) const {
	return CBuffer_Base::Is_bound(this->GetId(), this->m_error);
}

// https://stackoverflow.com/questions/70884233/opengl-get-currently-bound-vertex-buffer-and-index-buffer ;
bool  CBuffer_Base::Is_bound (const uint32_t _buffer_id, CError& _err) {
	_buffer_id; _err;
	if (0 == _buffer_id)
		return false == (_err << __e_inv_arg = _T("#__e_inv_val: '_buffer_id' cannot be set to zero (0)")).Is(); // 'false' does not equal to 'true';
	procs::CParam procs;
	const int32_t n_result = procs.GetInt(__gl_bound_to_arr);
	if (procs.Error()) {
		_err = procs.Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}

	return (n_result == static_cast<int32_t>(_buffer_id));
}

bool  CBuffer_Base::Is_valid (void) const {
	return CBuffer_Base::Is_valid(this->GetId(), this->m_error);
}

bool  CBuffer_Base::Is_valid (const uint32_t _buffer_id, CError& _err) {
	_buffer_id; _err;
#if (0)
	const bool b_valid = __get_buf_procs().Is_Buffer(_buffer_id);

	if (false == b_valid) {
		if (__get_buf_procs().Error())
			_err = __get_buf_procs().Error();
	}
#else
	const bool b_valid = !!_buffer_id; // the only reason that is taken into account is the buffer identifier value, the buffer binding is ignored;
#endif
	return b_valid;
}

using e_bind_targets = ex_ui::draw::open_gl::procs::e_bind_targets;

e_bind_targets CBuffer_Base::Target (void) const { return this->m_target; }
const bool     CBuffer_Base::Target (const e_bind_targets e_target) {
	e_target;
	const bool b_changed = this->Target() != e_target;

	if (b_changed)
		this->m_target = e_target;

	return b_changed;
}

err_code CBuffer_Base::Unbind (void) {
#if (1)
	this->m_error <<__METHOD__<<__s_ok;
	if (false == this->Is_bound())
		return this->m_error = __s_ok; // Is_bound can generate an error, in order to avoid it the error status is set to __s_ok;

	if (__failed(__get_buf_procs().Bind((uint32_t)this->Target(), 0))) {
		this->m_error = __get_buf_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_info_2(_T("The buffer id = %u is unbound from target = '%s';\n"), this->GetId(), (_pc_sz) data::CTarget::To_str(this->Target()));
	}

	return this->Error();
#else
	if (__failed(__get_buf_procs().Bind((uint32_t)this->Target(), 0))) {
		this->m_error = __get_buf_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}

	return _err;
#endif
}

/////////////////////////////////////////////////////////////////////////////

vertex::CBuffer:: CBuffer (void) { TBase::m_error <<__CLASS__; TBase::Target(e_bind_targets::e_array); }
vertex::CBuffer::~CBuffer (void) {}

err_code vertex::CBuffer::Bind (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	TBase::BindTo(TBase::Target());

	return TBase::Error();
}
#if (0)
err_code vertex::CBuffer::SetData (const CTriangle& _shape) {
	_shape;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return TBase::m_error <<__e_not_inited = _T("The buffer is not created yet");

	if (false == _shape.Is_valid())
		return TBase::m_error <<__e_inv_arg = _T("The input shape is not valid");

	const CVertArray& v_arr = _shape.Vertices();

	const void* const p_vertices = v_arr.Data_Ptr();
	if (nullptr == p_vertices)
		return TBase::m_error <<__e_pointer;

	const uint32_t u_bytes = static_cast<uint32_t>(sizeof(float) * v_arr.Data_ref().size());

#if (1)
	if (__failed(__get_buf_procs().Data((uint32_t)TBase::Target(), static_cast<ptrdiff_t>(u_bytes), p_vertices, (uint32_t)procs::e_buf_usage::e_static_draw))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) __get_buf_procs().Error().Print(TError::e_print::e_req));
		return TBase::m_error = __get_buf_procs().Error();
	}
#else
	if (__failed(__get_buf_procs().Named(this->GetId(), static_cast<ptrdiff_t>(v_arr.Bytes()), p_vertices, (uint32_t)procs::e_buf_usage::e_static_draw))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) __get_buf_procs().Error().Print(TError::e_print::e_req));
		return TBase::m_error = __get_buf_procs().Error();
	}
#endif
	if (__failed(v_arr.Set_ptrs())) {
		return TBase::m_error = v_arr.Error();
	}

	__trace_info_2(_T("The shape data of size = %u (bytes) is set;\n"), v_arr.Bytes());

	return TBase::Error();
}
#endif
err_code vertex::CBuffer::SetData (const TVertData& _v_data) {
	_v_data;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (_v_data.empty()) {
		TBase::m_error <<__e_inv_arg = _T("#__e_inv_arg: vertex data vector is empty");
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}

	if (false == this->Is_valid()) {
		TBase::m_error <<__e_not_inited = _T("#__e_mot_init: the buffer is not created");
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}

	const uint32_t u_bytes = static_cast<uint32_t>(sizeof(float) * _v_data.size());
	/**important*: before setting the data to buffer it must be bound, otherwise:
	   [error] cls::[CError]>>{code=87;result=0x80070057;desc='#__e_inv_oper: bound reserved buffer (id = 0)';context=CBase::CBuffer::Data()};
	*/
	if (__failed(__get_buf_procs().Data((uint32_t)TBase::Target(), static_cast<ptrdiff_t>(u_bytes), _v_data.data(), (uint32_t)procs::e_buf_usage::e_static_draw))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) __get_buf_procs().Error().Print(TError::e_print::e_req));
		return TBase::m_error = __get_buf_procs().Error();
	}
	else __trace_info_2(_T("The buffer (id = %u) is set to %u (bytes);\n"), TBase::GetId(), u_bytes);

	return TBase::Error();
}