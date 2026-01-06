/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jan-2026 at 21:34:55.786, (UTC+4), Batumi, Monday;
	This is Ebo Pack OpenGL math functions' loader interface implementation file;
*/
#include "gl_procs_math.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;
using namespace ex_ui::draw::open_gl::procs::math;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_3 { void __warning_lnk_4006 (void) {}}}}}

CUniform:: CUniform (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}