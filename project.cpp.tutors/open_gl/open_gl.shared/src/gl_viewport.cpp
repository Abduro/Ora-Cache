/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Oct-2025 at 19:30:37.003, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL viewport wrapper interface implementation file;
*/
#include "gl_viewport.h"
#include "shared.preproc.h"
#include "procs\gl_procs_view.h"

using namespace ex_ui::draw::open_gl;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	procs::CDepth&  __get_depth_procs(void) {
		static procs::CDepth procs;
		return procs;
	}

	procs::CViewport&  __get_depth_view(void) {
		static procs::CViewport procs;
		return procs;
	}

}}}}
using namespace ex_ui::draw::open_gl::_impl;

CViewPort:: CViewPort (const uint32_t _u_width, const uint32_t _u_height) : m_size{_u_width, _u_height} {
	this->m_error >>__CLASS__<<__METHOD__<<(this->Is_valid() ? __s_ok : __e_not_inited);
}
CViewPort::~CViewPort (void) {}

TError& CViewPort::Error(void) const { return this->m_error; }

t_size  CViewPort::Get (void) const { return t_size{ (long)this->m_size.cx, (long)this->m_size.cy}; }
t_size_u& CViewPort::Get (void) {
	return this->m_size;
}

err_code CViewPort::Set (const uint32_t _u_width, const uint32_t _u_height) {
	_u_width; _u_height;
	this->m_error << __METHOD__<<__s_ok;

	if (0 == _u_height) return this->m_error << __e_inv_arg = _T("Height cannot be 0 (zero)");
	if (0 == _u_width) return this->m_error << __e_inv_arg = _T("Width cannot be 0 (zero)");

	this->m_size.cy = _u_height;
	this->m_size.cx = _u_width ;

	return this->Error();
}

err_code CViewPort::Set (const t_rect& _rect) {
	_rect;
	this->m_error << __METHOD__<<__s_ok;
	if (::IsRectEmpty(&_rect))
		return this->m_error <<__e_inv_arg;

	this->m_size.cy = __H(_rect);
	this->m_size.cx = __W(_rect);

	return this->Error();
}

bool CViewPort::Is_valid (void) const {
	return this->m_size.cy != 0 && this->m_size.cx != 0;
}

vertex::CCoord  CViewPort::ToPos (const long _x, const long _y) {
	_x; _y;
	if (false == this->Is_valid()) {
		this->m_error <<__METHOD__<<__e_inv_arg = TString().Format(_T("Input coords are invalid: x=0x%04x, y=0x%04x"), _x, _y);
		return vertex::CCoord(); // returns 'empty' or 'default' coord which has x|y = {0};
	}
	// https://discourse.glfw.org/t/converting-between-screen-coordinates-and-pixels/1841/2 ; thanks @dougbinks for good answer;

	return vertex::CCoord(
		2.0f * (float)_x/(float)this->m_size.cx - 1.0f, 1.0f - 2.0f * (float)_y/(float)this->m_size.cy
	);
}