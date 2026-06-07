/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jun-2026 at 23:43:29.432, UTC+4, Batumi, Monday;
	This is OpenGL v.1.1 frustum related function set wrapper interface implementation file;
*/
#include "gl_procs_frustum.h"

using namespace ::open_gl::procs::projection;

#pragma region cls::CFrustum{}

CFrustum:: CFrustum (void) : TBase() { TBase::m_error >>__CLASS__; }

// https://learn.microsoft.com/en-us/windows/win32/opengl/glfrustum ;
err_code CFrustum::Set (const f_rect& _clip, const f_planes& _planes) {
	_clip; _planes;
	/* possible error codes:
	GL_INVALID_ENUM      : zNear or zFar was not postitive;
	GL_INVALID_OPERATION : 
	*/
	TBase::m_error <<__METHOD__<<__s_ok;

	if (_clip.Is_empty())
		return TBase::m_error << __e_rect = _T("#__e_inv_arg: clipping rectangle is empty");
	if (__failed(f_planes::Is_valid(_planes, TBase::m_error))) // ignores 'nothing to draw' case, it's necessary to review such case;
		return TBase::Error();

//	const f_rect f_clip(_clip);
	const d_rect d_clip(_clip);

	::glFrustum(d_clip.d_left, d_clip.d_right, d_clip.d_bottom, d_clip.d_top, _planes.f_near, _planes.f_far);
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code) {
	case GL_INVALID_ENUM : (TBase::m_error = u_err_code) = p_err_neg_value; break;
	case GL_INVALID_OPERATION : { (TBase::m_error = u_err_code) = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

err_code CFrustum::Set (const t_rect& _clip, const f_planes& _planes) {
	_clip; _planes;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (::IsRectEmpty(&_clip))
		return TBase::m_error << __e_rect = _T("#__e_inv_arg: clipping rectangle is empty");
	if (__failed(f_planes::Is_valid(_planes, TBase::m_error))) // ignores 'nothing to draw' case, it's necessary to review such case;
		return TBase::Error();

	const f_rect f_clip(_clip);

	return this->Set(f_clip, _planes);
}

#pragma endregion