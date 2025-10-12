/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Oct-2025 at 21:59:45.986, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL data buffer wrapper interface implementation file;
*/
#include "gl_buffer.h"
#include "shared.preproc.h"
#include "procs\gl_procs_buffer.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::data;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	procs::CBuffer&  __get_buf_procs (void) {
		static procs::CBuffer procs;
		return procs;
	}
}}}}

using namespace ex_ui::draw::open_gl::_impl;

CBuffer:: CBuffer (void) : m_buf_id(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CBuffer::~CBuffer (void) {}

err_code  CBuffer::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists = _T("The buffer is already created");

	if (__failed(__get_buf_procs().GenerateIds(1, &this->m_buf_id)))
		this->m_error = __get_buf_procs().Error();

	return this->Error();
}

err_code  CBuffer::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid()) // no error this time, just returning the success code;
		return this->Error();

	if (__failed(__get_buf_procs().Delete(1, &this->m_buf_id))) // ToDo: perhaps the buffer identifier should be set to zero, but under specific circumstances it is cannot be made;
		return this->m_error = __get_buf_procs().Error();

	this->m_buf_id = 0;

	return this->Error();
}

TError&   CBuffer::Error (void) const { return this->m_error; }

uint32_t  CBuffer::Id (void) const { return this->m_buf_id; }

bool  CBuffer::Is_valid (void) const {
	return CBuffer::Is_valid(this->Id(), this->m_error);
}

bool  CBuffer::Is_valid (const uint32_t _buffer_id, CError& _err) {
	_buffer_id; _err;

	const bool b_valid = __get_buf_procs().Is_Buffer(_buffer_id);

	if (false == b_valid) {
		if (__get_buf_procs().Error())
			_err = __get_buf_procs().Error();
	}

	return b_valid;
}