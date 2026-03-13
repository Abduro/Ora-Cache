/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 09:10:27.386, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib common definitions' uint test interface implementation file; 
*/
#include "ebo_test_$m$.defs.h"

using namespace ebo::boo::test::open_gl::math;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_3 { void __warning_lnk_4006 (void) {}}}}}

#pragma region cls::c_mtx_base

c_mtx_base::c_mtx_base (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& c_mtx_base::Error (void) const { return this->m_error; }

#pragma endregion