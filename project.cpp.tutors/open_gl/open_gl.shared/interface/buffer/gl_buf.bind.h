#ifndef _Gl_BUF_BIND_H_INCLUDED
#define _Gl_BUF_BIND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jan-2026 at 18:28:44.530, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL vertex buffer bind target wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "buffer\gl_procs_buffer.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace buffer {

	using e_bnd_tgts = ex_ui::draw::open_gl::procs::e_bnd_tgts;

	// unfortunately there's the mix of class names: CPipline has the draw 'target' object and the buffer class also has 'target' object type which it is bound to;
	class CTarget {
	public:
		CTarget (const e_bnd_tgts = e_bnd_tgts::e__undef); CTarget (const CTarget&) = delete; CTarget (CTarget&&); ~CTarget (void) = default;

		e_bnd_tgts Get (void) const;        // gets the target type value;
		const bool Set (const e_bnd_tgts);  // returns 'true' in case of target type value change;

		static CString To_str (const e_bnd_tgts);

		CTarget& operator <<(const e_bnd_tgts);

		operator e_bnd_tgts (void) const;

	private:
		CTarget& operator = (const CTarget&) = delete;
		CTarget& operator = (CTarget&&) = delete;

		e_bnd_tgts m_bound_to;
	};

}}}}

#endif/*_Gl_BUF_BIND_H_INCLUDED*/