#ifndef _GL_VERTEX_ARR_DAT_H_INCLUDED
#define _GL_VERTEX_ARR_DAT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Nov-2025 at 22:22:42.427, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' generic vertex data array interface declaration file; 
*/
#include "gl_defs.h"
#include "gl_vertex_attr.h"
#include "gl_vertex_data.h"

namespace ex_ui { namespace draw { namespace open_gl {

	typedef ::std::vector<CVertex> TVertices; // the seperate vertex collection, not the data for vertex buffer;

	class CVertArray {
		public:
		CVertArray (void); CVertArray (const CVertArray&) = delete; CVertArray (CVertArray&&) = delete; ~CVertArray (void);
		// https://www.allacronyms.com/elements/abbreviated ;

		uint32_t  Count (void) const;    // gets count of vertices elements, the same can be made by direct access to the vertices' vector;
		err_code  Count (const uint32_t _n_elems); // sets the number of the required vertices, i.e. elements;
		TError&   Error (void) const;
		const
		void*     GetData (void) const;  // gets the pointer to vertex array data, this is the data for vertex buffer;
		const
		TVertices& Items (void) const;   // gets the reference to vertex collection; (ro)
		TVertices& Items (void) ;        // gets the reference to vertex collection; (rw)

		err_code  Update (void);         // updates vertex data vector by applying vertices' attribute arrays' data;
	
	private:
		CVertArray& operator = (const CVertArray&) = delete; CVertArray& operator = (CVertArray&&) = delete;
		mutable
		CError    m_error;
		TVertices m_items;  // this is the set of vertices themselves;
		TVertData m_data ;  // this is the data for vertex buffer;
	};

}}}

#endif/*_GL_VERTEX_ARR_DAT_H_INCLUDED*/