#ifndef _GL_SHAPE_VERTEX_H_INCLUDED
#define _GL_SHAPE_VERTEX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jun-2026 at 19:56:50.627, UTC+4, Batumi, Thursday;
	This is drawable shape vertex interface declaration file.
*/
#include "drawable.defs.h"

namespace open_gl { namespace shapes {

	typedef ::std::array<float, 0x03u> f_set_3; // x|y|z; r|g|b; the same as open_gl::procs::f_set_3 (gl_procs_basic.h)

	class CVertex {
	public:
		CVertex (void); CVertex (const CVertex&); CVertex (CVertex&&) = delete; ~CVertex (void) = default;

		const
		f_set_3& Color (void) const;
		f_set_3& Color (void) ;
		const
		f_set_3& Point (void) const;
		f_set_3& Point (void) ;

		CVertex& operator = (const CVertex&);
		CVertex& operator = (CVertex&&) = delete;

	private:
		f_set_3 m_point;
		f_set_3 m_color;
	};

}}

#endif/*_GL_SHAPE_VERTEX_H_INCLUDED*/