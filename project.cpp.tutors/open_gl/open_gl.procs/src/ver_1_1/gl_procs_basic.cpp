/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-May-2026 at 00:33:57.629, UTC+4, Batumi, Tuesday;
	This is OpenGL ver.1.1 common basic interface implementation file;
*/
#include "gl_procs_basic.h"

using namespace open_gl::procs::ver_1_1;

#pragma region cls::CBasic{}

CBasic::CBasic (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError&  CBasic::Error (void) const { return this->m_error; }

#pragma endregion