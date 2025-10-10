/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Oct-2025 at 22:06:41.598, (UTC+4), Batumi, Tuesday;
	This is Ebo Pack OpenGL vertex buffer functions' loader interface implementation file;
*/
#include "gl_procs_buffer.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;

bool is_bind_target (const uint32_t _u_tgt_type) {
	return (uint32_t)e_bind_targets::e_array    == _u_tgt_type
		|| (uint32_t)e_bind_targets::e_counter  == _u_tgt_type
		|| (uint32_t)e_bind_targets::e_read     == _u_tgt_type
		|| (uint32_t)e_bind_targets::e_write    == _u_tgt_type
		|| (uint32_t)e_bind_targets::e_disp     == _u_tgt_type
		|| (uint32_t)e_bind_targets::e_draw     == _u_tgt_type
		|| (uint32_t)e_bind_targets::e_el_arr   == _u_tgt_type
		|| (uint32_t)e_bind_targets::e_pxl_pk   == _u_tgt_type
		|| (uint32_t)e_bind_targets::e_pxl_unpk == _u_tgt_type
		|| (uint32_t)e_bind_targets::e_query    == _u_tgt_type
		|| (uint32_t)e_bind_targets::e_$_stg    == _u_tgt_type    
		|| (uint32_t)e_bind_targets::e_texture  == _u_tgt_type
		|| (uint32_t)e_bind_targets::e_trans    == _u_tgt_type   
		|| (uint32_t)e_bind_targets::e_uniform  == _u_tgt_type;
}

bool is_buf_usage (const uint32_t _u_oper_type) {
	return (uint32_t)e_buf_usage::e_stream_draw == _u_oper_type
		|| (uint32_t)e_buf_usage::e_stream_read == _u_oper_type
		|| (uint32_t)e_buf_usage::e_stream_copy == _u_oper_type
		|| (uint32_t)e_buf_usage::e_static_draw == _u_oper_type
		|| (uint32_t)e_buf_usage::e_static_read == _u_oper_type
		|| (uint32_t)e_buf_usage::e_static_copy == _u_oper_type
		|| (uint32_t)e_buf_usage::e_dyna_draw   == _u_oper_type
		|| (uint32_t)e_buf_usage::e_dyna_read   == _u_oper_type
		|| (uint32_t)e_buf_usage::e_dyna_copy   == _u_oper_type;
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz buf_fun_names[] = {
	_T("glBindBuffer"), _T("glBufferData"), _T("glDeleteBuffers"), _T("glGenBuffers"), _T("glIsBuffer"), _T("glNamedBufferData")
};

enum class e_buf_fun_ndx : uint32_t {
	e_bind = 0x0, e_data = 0x1, e_delete = 0x2, e_generate = 0x3, e_is_buffer = 0x4, e_named = 0x5
};

CBuffer:: CBuffer (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml ;
err_code CBuffer::Bind (const uint32_t _u_tgt_id, const uint32_t _u_buf_id) {
	_u_tgt_id; _u_buf_id;
	/* Possible errors:
		GL_INVALID_ENUM  : _u_tgt_id is not one of the allowable values ;
		GL_INVALID_VALUE : _u_buff_id is not an identifier of data buffer that is previously returned from a call to glGenBuffers() ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Bind p_fun = reinterpret_cast<pfn_Bind>(CBase::Get(buf_fun_names[(uint32_t)e_buf_fun_ndx::e_bind]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_tgt_id, _u_buf_id);

	switch (CErr_ex().Get_last(false)) {
	case GL_INVALID_ENUM : CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_enum: '_u_tgt_id' (%u) is not accepted"), _u_tgt_id); break;
	case GL_INVALID_VALUE: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_u_buff_id' (%u) is not valid"), _u_buf_id); break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml ;
err_code CBuffer::Data (const uint32_t _u_tgt_id, const ptrdiff_t _n_size, const void* _p_data, const uint32_t _u_usage) {
	_u_tgt_id; _n_size; _p_data; _u_usage;
	/* Possible errors:
		GL_INVALID_ENUM      : '_u_tgt_id' is not one of the accepted buffer targets;
		GL_INVALID_VALUE     : '_n_size' is negative;
		GL_INVALID_OPERATION : the reserved buffer object of identifier 0 is bound to target;
		GL_OUT_OF_MEMORY     : the GL is unable to create a data store with the specified size;
		GL_INVALID_ENUM      : '_u_usage' is not one of the acceptable tokens;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Data p_fun = reinterpret_cast<pfn_Data>(CBase::Get(buf_fun_names[(uint32_t)e_buf_fun_ndx::e_data]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_tgt_id, _n_size, _p_data, _u_usage);

	switch (CErr_ex().Get_last(false)) {
	case GL_INVALID_ENUM : {
			if (false){}
			else if (false == ::is_bind_target(_u_tgt_id)) CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_tgt: '_u_tgt_id' (%u) is not accepted"), _u_tgt_id);
			else if (false == ::is_buf_usage(_u_usage)) CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_use: '_u_usage' (%u) is not acceptad"), _u_usage);
			else CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_enum: #undef error"));
		} break;
	case GL_OUT_OF_MEMORY : CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_no_mem: creating data store with size (%I64d) failed"), _n_size); break;
	case GL_INVALID_OPERATION : CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: bound reserved buffer (id=%d)"), 0); break;
	case GL_INVALID_VALUE : {
			if (0 > _n_size) CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_n_size' (%I64d) has invalid value"), _n_size);
			else CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: #undef error"));
		} break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteBuffers.xhtml ;
// https://stackoverflow.com/questions/27937285/when-should-i-call-gldeletebuffers << good explanation;
err_code CBuffer::Delete (const int32_t _n_count, const uint32_t* _p_buffers) {
	_n_count; _p_buffers;
	// GL_INVALID_VALUE : _n_count is negative ;
	// ToDo: but what is about the pointer to buffers' array? for example, the count of the buffers that are going to be deleted > 0, but the pointer is 0;
	CBase::m_error << __METHOD__ << __s_ok;
	// there is no memory check, but just for 0 (zero) and (DWORD)-1 (invalid handle);
	if (nullptr == _p_buffers || __e_handle == _p_buffers)
		return CBase::m_error << __e_pointer = TString().Format(_T("#__e_inv_ptr: '_p_buffers' %s is invalid"), (_pc_sz)__address_of(_p_buffers, _T("0x%08x")));

	pfn_Delete p_fun = reinterpret_cast<pfn_Delete>(CBase::Get(buf_fun_names[(uint32_t)e_buf_fun_ndx::e_delete]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_n_count, _p_buffers);

	switch (CErr_ex().Get_last(false)) {
	case GL_INVALID_VALUE : CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_n_count' (%d) has invalid value"), _n_count); break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml ;
err_code CBuffer::GenerateIds (const int32_t _n_count, uint32_t* _p_buf_ids) {
	_n_count; _p_buf_ids;
	// GL_INVALID_VALUE : _n_count is negative ;
	// ToDo: what is about pointer to the buffer identifiers' array?
	CBase::m_error << __METHOD__ << __s_ok;

	// there is no memory check, but just for 0 (zero) and (DWORD)-1 (invalid handle);
	if (nullptr == _p_buf_ids || __e_handle == _p_buf_ids)
		return CBase::m_error << __e_pointer = TString().Format(_T("#__e_inv_ptr: '_p_buf_ids' %s is invalid"), (_pc_sz)__address_of(_p_buf_ids, _T("0x%08x")));

	pfn_GenIds p_fun = reinterpret_cast<pfn_GenIds>(CBase::Get(buf_fun_names[(uint32_t)e_buf_fun_ndx::e_generate]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_n_count, _p_buf_ids);

	switch (CErr_ex().Get_last(false)) {
	case GL_INVALID_VALUE : CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_n_count' (%d) has invalid value"), _n_count); break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsBuffer.xhtml ;
bool CBuffer::Is_Buffer (const uint32_t _u_buf_id) {
	_u_buf_id;
	// no error is generated by this function;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_IsBuf p_fun = reinterpret_cast<pfn_IsBuf>(CBase::Get(buf_fun_names[(uint32_t)e_buf_fun_ndx::e_is_buffer]));
	if (nullptr == p_fun)
		return false;

	const int32_t n_result = p_fun(_u_buf_id);

	return !!n_result;
}

// https://www.reddit.com/r/opengl/comments/aifvjl/glnamedbufferstorage_vs_glbufferdata/ ; as an example;
// https://www.reddit.com/r/cpp_questions/comments/aik18a/after_two_years_seems_like_i_still_dont/ ; as an example too;
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml ;
err_code CBuffer::Named (const uint32_t _u_buf_id, const ptrdiff_t _n_size, const void* _p_data, const uint32_t _u_usage) {
	_u_buf_id; _n_size; _p_data; _u_usage;
	/* Possible errors:
		GL_INVALID_VALUE     : '_n_size' is negative;
		GL_INVALID_OPERATION : '_u_buf_id' is zero (0) that is the identifier of the reserved buffer object;
		GL_INVALID_OPERATION : '_u_buf_id' is not the identifier of an existing buffer object;
		GL_INVALID_OPERATION : GL_BUFFER_IMMUTABLE_STORAGE flag of the buffer object is GL_TRUE; i.e. the buffer is *read-only*;
		GL_OUT_OF_MEMORY     : the GL is unable to create a data store with the specified size;
		GL_INVALID_ENUM      : '_u_usage' is not one of the acceptable tokens;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Named p_fun = reinterpret_cast<pfn_Named>(CBase::Get(buf_fun_names[(uint32_t)e_buf_fun_ndx::e_named]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_buf_id, _n_size, _p_data, _u_usage);

	switch (CErr_ex().Get_last(false)) {
	case GL_INVALID_ENUM : {
			if (false == ::is_buf_usage(_u_usage)) CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_use: '_u_usage' (%u) is not acceptad"), _u_usage);
			else CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_enum: #undef error"));
		} break;
	case GL_INVALID_OPERATION : {
			if (false){}
			else if (0 == _u_buf_id) CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_u_buf_id' (%u) refers to reserved buffer"), _u_buf_id);
			else if (false == this->Is_Buffer(_u_buf_id)) // ToDo: Is_Buffer() may fail and its error is not taken into account yet;
				CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_u_buf_id' (%u) does not refer to buffer"), _u_buf_id);
			else CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_u_buf_id' (%u) refers to read-only buffer"), _u_buf_id);
		} break;
	case GL_OUT_OF_MEMORY : CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_no_mem: creating data store with size (%I64d) failed"), _n_size); break;
	case GL_INVALID_VALUE : {
			if (0 > _n_size) CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_n_size' (%I64d) has invalid value"), _n_size);
			else CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: #undef error"));
		} break;
	default:;
	}

	return CBase::Error();
}

err_code CBuffer::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(buf_fun_names); i_++) {
		if (nullptr == CBase::Get(buf_fun_names[i_]))
			break;
	}

	return CBase::Error();
}