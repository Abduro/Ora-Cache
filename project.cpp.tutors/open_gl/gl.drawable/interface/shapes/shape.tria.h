#ifndef _GL_SHAPE_TRIA_H_INCLUDED
#define _GL_SHAPE_TRIA_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jun-2026 at 00:54:49.204, UTC+4, Batumi, Friday;
	This is triangle drawable shape interface declaration file.
*/
#include "shape.base.h"
#include "shape.vertex.h"

namespace open_gl { namespace shapes {

	using namespace ::open_gl::procs::ver_1_1;
	using namespace ::open_gl::procs::matrix::ver_1_1;

	typedef ::std::array<CVertex, 0x3u>  f_tria_vert;

	class CTria : public ::open_gl::shapes::CBase { typedef ::open_gl::shapes::CBase TBase;
	public:
		CTria (void); CTria (const CTria&) = delete; CTria (CTria&&) = delete; ~CTria (void) = default;

		void  Draw (void);
		void  Format (void);  // applies default format setting;

		const
		f_tria_vert& operator ()(void) const;
		f_tria_vert& operator ()(void) ;

	private:
		CTria& operator = (const CTria&) = delete;
		CTria& operator = (CTria&&) = delete;
		f_tria_vert m_vert;
	};

}}

#endif/*_GL_SHAPE_TRIA_H_INCLUDED*/