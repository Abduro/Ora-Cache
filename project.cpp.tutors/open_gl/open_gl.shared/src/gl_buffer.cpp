/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Oct-2025 at 21:59:45.986, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL data buffer wrapper interface implementation file;
*/
#include "gl_buffer.h"
#include "shared.dbg.h"
#include "shared.preproc.h"
#include "gl_procs.h"
#include "procs\gl_procs_buffer.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::data;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	procs::CBuffer&  __get_buf_procs (void) {
		static procs::CBuffer procs;
		return procs;
	}
}}}}

#define __gl_bound_to_arr 0x8894 // GL_ARRAY_BUFFER_BINDING

using namespace ex_ui::draw::open_gl::_impl;

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

#if (0)
CBuffer::CBinder:: CBinder (CBuffer& _buf) : m_buffer(_buf) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CBuffer::CBinder::~CBinder (void) {}

TError&  CBuffer::CBinder::Error (void) const { return this->m_error; }
#endif
/////////////////////////////////////////////////////////////////////////////

CBuffer:: CBuffer (void) : m_buf_id(0), m_target(e_bind_targets::e__undef) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CBuffer::~CBuffer (void) {}

err_code  CBuffer::BindTo (const e_bind_targets _e_target) {
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
		__trace_info_2(_T("The buffer id = %u is bound to target = '%s';\n"), this->GetId(), (_pc_sz) data::CTarget::To_str(_e_target));
	}

	return this->Error();
}

err_code  CBuffer::Create (void) {
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

err_code  CBuffer::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_bound()) {
		if (this->Error()) {
			__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			return this->Error();
		}
		else {
			__trace_info_2(_T("The buffer (id = %u) is not bound; nothing to delete;\n"), this->GetId());
		}
	}

	if (false == this->Is_valid()) // no error this time, just returning the success code;
		return this->Error();

	if (__failed(__get_buf_procs().Delete(1, &this->m_buf_id))) { // ToDo: perhaps the buffer identifier should be set to zero, but under specific circumstances it is cannot be made;
		this->m_error = __get_buf_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	else {
		__trace_warn_2(_T("The buffer (id = %u) is destroyed;\n"), this->GetId());
		this->m_buf_id = 0;
	}
	return this->Error();
}

TError&   CBuffer::Error (void) const { return this->m_error; }

uint32_t  CBuffer::GetId (void) const { return this->m_buf_id; }

bool  CBuffer::Is_bound (void) const {
	return CBuffer::Is_bound(this->GetId(), this->m_error);
}

// https://stackoverflow.com/questions/70884233/opengl-get-currently-bound-vertex-buffer-and-index-buffer ;
bool  CBuffer::Is_bound (const uint32_t _buffer_id, CError& _err) {
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

bool  CBuffer::Is_valid (void) const {
	return CBuffer::Is_valid(this->GetId(), this->m_error);
}

bool  CBuffer::Is_valid (const uint32_t _buffer_id, CError& _err) {
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