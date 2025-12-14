/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2025 at 12:09:33.744, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL common definitions' implamentation file;
*/
#include "gl_defs.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_0 { void __warning_lnk_4221 (void) {}}}}}

using e_object = CPipeline::e_object;

CPipeline:: CPipeline (void) : m_target(e_object::e_none) {}
CPipeline::~CPipeline (void) {}

e_object  CPipeline::Target (void) const { return this->m_target; }
 bool     CPipeline::Target (const e_object _u_target) {
	 _u_target;
	 const bool b_changed = this->Target() != _u_target; if (b_changed) this->m_target = _u_target; return b_changed;
 }