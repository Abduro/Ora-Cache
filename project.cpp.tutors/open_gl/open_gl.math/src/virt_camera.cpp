/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Feb-2026 at 09:59:32.473, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL 3D virtual camera interface implementation file;
*/
#include "virt_camera.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::camera::opers;

#pragma region cls::CPosition{}

CForward::CForward (void) {}

#pragma endregion
#pragma region cls::CPosition{}

CPosition::CPosition(void) {}

#pragma endregion
#pragma region cls::CRotation{}

CRotation::CRotation (void) {}

#pragma endregion
#pragma region cls::CVirtCamera{}

CVirtCamera::CVirtCamera (void) : m_dist(0.0f) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CVirtCamera::Error (void) const { return this->m_error; }

#pragma endregion