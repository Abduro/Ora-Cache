/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2025 at 12:09:33.744, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL common definitions' implamentation file;
*/
#include "gl_defs.h"

using namespace ex_ui::draw::open_gl::procs;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_0 { void __warning_lnk_4221 (void) {}}}}}

PROC CBase::Get (_pc_sz _p_proc_name) {
	_p_proc_name;
	if (nullptr == _p_proc_name || 0 == ::_tcslen(_p_proc_name))
		return nullptr;

	TProcCache::const_iterator found_ = this->m_cached.find(_p_proc_name);
	if (found_ != this->m_cached.end())
		return found_->second;

	CStringA cs_ansi(_p_proc_name);
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglgetprocaddress?source=docs ;
	PROC p_proc = ::wglGetProcAddress(cs_ansi.GetString());
	if ( p_proc )
		this->m_cached.insert(::std::make_pair(_p_proc_name, p_proc));
	return p_proc;
}