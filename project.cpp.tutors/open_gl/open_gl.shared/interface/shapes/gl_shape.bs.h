#ifndef _GL_SHAPE_BS_H_INCLUDED
#define _GL_SHAPE_BS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Oct-2024 at 17:52:08.453, UTC+4, Batumi, Monday;
	This is Ebo Pack 2D space geometry base shape interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to OpenGL tutorials on 23-Oct-2025 at 20:56:51.657, UTC+4, Batumi, Friday;
*/
#include "vertex\gl_vertex_arr.dat.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shapes {

	// https://simple.wikipedia.org/wiki/Shape ;
	// https://en.wikipedia.org/wiki/List_of_two-dimensional_geometric_shapes ;

	class CShape {
	private: CShape (const CShape&) = delete; CShape (CShape&&) = delete;
	public : CShape (void); ~CShape (void);
	public :
		static const uint32_t n_min_vertex_count = 3; // a triangle is the simplest figure that can be considered as a shape;
		static CString Class (void);

		TError&  Error (void) const;

	private: CShape& operator = (const CShape&) = delete; CShape& operator = (CShape&&) = delete;
	protected:
		mutable
		CError      m_error;
		CVertArray  m_array;
	};

}}}}

#endif/*_GL_SHAPE_BS_H_INCLUDED*/