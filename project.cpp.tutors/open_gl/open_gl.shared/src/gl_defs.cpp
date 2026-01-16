/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2025 at 12:09:33.744, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL common definitions' implamentation file;
*/
#include "gl_defs.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_0 { void __warning_lnk_4221 (void) {}}}}}

using e_object = CPipeline::e_object;

CPipeline:: CPipeline (const e_object _target) : m_target(_target) {}
CPipeline:: CPipeline (const CPipeline& _src) : CPipeline() { *this = _src; }
CPipeline:: CPipeline (CPipeline&& _victim) : CPipeline() { *this = _victim; }
CPipeline::~CPipeline (void) {}

e_object  CPipeline::Target (void) const { return this->m_target; }
bool      CPipeline::Target (const e_object _u_target) {
	 _u_target;
	 const bool b_changed = this->Target() != _u_target; if (b_changed) this->m_target = _u_target; return b_changed;
}

_pc_sz   CPipeline::To_str (const e_object _u_target) {
	 _u_target;
	 static _pc_sz p_names[] = {_T("#none"), _T("grid.1"), _T("triangle.1")};
	 if (false) {}
	 else if (e_object::e_grid == _u_target) return p_names[e_object::e_grid];
	 else if (e_object::e_tria == _u_target) return p_names[e_object::e_tria];
	 else return p_names[e_object::e_none];
}

CPipeline::operator CPipeline::e_targets (void) const { return this->Target(); }
const
CPipeline& CPipeline::operator >>(CPipeline::e_targets& _out) const { _out = this->Target(); return *this; }
CPipeline& CPipeline::operator <<(const e_object _target) { this->Target(_target); return *this; }

CPipeline& CPipeline::operator = (const CPipeline& _src) { *this << _src.Target(); return *this; }
CPipeline& CPipeline::operator = (CPipeline&& _victim) { *this = (const CPipeline&)_victim; return *this; }