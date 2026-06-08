/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jun-2026 at 23:45:34.980, UTC+4, Batumi, Sunday;
	This is OpenGL v.1.1 orthographic matrix related function set wrapper interface implementation file;
*/
#include "gl_procs_ortho.h"

using namespace ::open_gl::procs::projection::ver_1_1;

#pragma region cls::COrtho{}

COrtho::COrtho (void) { TBase::m_error >>__CLASS__; }

err_code COrtho::Set (const t_rect& _clip, const f_planes& _planes) {
	_clip; _planes;
	/* possible error codes:
	GL_INVALID_VALUE     : If left == right, or bottom == top, or near == far;
	GL_INVALID_OPERATION : The function was called between a call to glBegin and the corresponding call to glEnd.
	*/
	TBase::m_error <<__METHOD__<<__s_ok;

	if (::IsRectEmpty(&_clip))
		return TBase::m_error << __e_rect = _T("#__e_inv_arg: clipping rectangle is empty");
	if (f_planes::Is_singular(_planes, TBase::m_error))
		return TBase::Error();

	const f_rect f_clip( _clip);
	const d_rect d_clip(f_clip);

	::glOrtho(d_clip.d_left, d_clip.d_right, d_clip.d_bottom, d_clip.d_top, _planes.f_near, _planes.f_far);
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code) {
	case GL_INVALID_VALUE : (TBase::m_error = u_err_code) = p_err_neg_value; break;
	case GL_INVALID_OPERATION : (TBase::m_error = u_err_code) = p_err_inv_oper; break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}

	return TBase::Error();
}

#pragma endregion