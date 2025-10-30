#ifndef _GL_SHAPE_2D_H_INCLUDED
#define _GL_SHAPE_2D_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Oct-2025 at 15:29:58.463, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL generic 2D shape wrapper interface declaration file;
*/
#include "gl_shape.bs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shapes {
	// https://en.wikipedia.org/wiki/Triangle ;
	class CTriangle : public CShape {
	private: CTriangle (const CTriangle&) = delete; CTriangle (CTriangle&&) = delete;
	public : CTriangle (void); ~CTriangle (void);

		/*    A    this is a triangle vertises' of the corners naming; *important*: only such comment specifiers can be applied,
		     / \   otherwise the slash symbol (between A and C) destroys the comment and the compiler throws errors;
		    B — C
		*/
		enum e_vertices : uint32_t { 
		    e_a = 0x0, e_b = 0x1, e_c = 0x2
		};
		// important: do not change neither stride nor offset because they are already set by vertex data itself;
		const
		CVertex& A (void) const;
		CVertex& A (void) ;
		const
		CVertex& B (void) const;
		CVertex& B (void) ;
		const
		CVertex& C (void) const;
		CVertex& C (void) ;
		const
		CVertex& Get (const e_vertices) const; // returns a reference to the vertex by corner index; (ro);
		CVertex& Get (const e_vertices) ;      // returns a reference to the vertex by corner index; (rw);

		bool  Is_valid (void) const;       // returns true is the vector of the cached vertices is not empty;
		const
		void* const  Cached (void) const;  // gets pointer to cached vertices' data;
		uint32_t     Size (void) const;    // gets memory size of all vertices of this shape;
		err_code     Update (void) ;       // updates cached data for case of one of the vertices' data is changed;

	private: CTriangle& operator = (const CTriangle&) = delete; CTriangle& operator = (CTriangle&&) = delete;
		mutable
		TVertData m_cache; // the cache vector contains all above vertices as the sequence of the data;
		CVertex   m_vertices[CShape::n_min_point_count]; // 0 - A; 1 - B; 2 - C;
	};

}}}}

#endif/*_GL_SHAPE_2D_H_INCLUDED*/