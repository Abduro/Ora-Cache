/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-May-2026 at 02:02:39.322, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' virtual camera base interface implementation file;
*/
#include "camera.base.h"

using namespace ::open_gl;
using namespace ::open_gl::camera;
using namespace ::open_gl::views;

#pragma region cls::CCamera{}

CCamera::CCamera (void) : m_dist(0.0f) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

const
s_angles& CCamera::Angles (void) const { return this->m_angles; }
s_angles& CCamera::Angles (void)       { return this->m_angles; }

err_code  CCamera::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	return this->Error();
}
err_code  CCamera::Destroy(void) {
	this->m_error <<__METHOD__<<__s_ok;

	return this->Error();
}
float     CCamera::Dist (void) const { return this->m_view(3,2); }  // references to z-coord of tranclate column;
float&    CCamera::Dist (void)       { return this->m_view(3,2); }     

TError&   CCamera::Error  (void) const { return this->m_error; }
const
s_pos&    CCamera::Pos (void) const { return this->m_pos; }
s_pos&    CCamera::Pos (void)       { return this->m_pos; }
const
c_mat4x4& CCamera::View (void) const { return this->m_view; }
c_mat4x4& CCamera::View (void)       { return this->m_view; }

#pragma endregion
#pragma region cls::CFrustum{}

CFrustum::CFrustum (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not__inited: frustum is not set");}

TError&   CFrustum::Error (void) const { return this->m_error; }

#pragma endregion