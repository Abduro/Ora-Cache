#ifndef _GL_VERTEX_ARR_DAT_H_INCLUDED
#define _GL_VERTEX_ARR_DAT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Nov-2025 at 22:22:42.427, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' generic vertex data array interface declaration file; 
*/
#include "gl_defs.h"
#include "vertex\gl_vertex_attr.h"
#include "vertex\gl_vertex_data.h"
#include "gl_buffer.h"

namespace ex_ui { namespace draw { namespace open_gl {

	typedef ::std::vector<CVertex> TVertices; // the seperate vertex collection, not the data for vertex buffer;

	class CVertArray {
	public:
		using CAttr   = vertex::CAttr;
		using CBuffer = vertex::CBuffer;
	public:
		CVertArray (void); CVertArray (const CVertArray&) = delete; CVertArray (CVertArray&&) = delete; ~CVertArray (void);
		const
		CBuffer&  Buffer (void) const;
		CBuffer&  Buffer (void) ;

		uint32_t  Bytes (void) const;    // gets memory size of all vertices of this shape;

		// https://www.allacronyms.com/elements/abbreviated ;
		uint32_t  Count (void) const;    // gets count of vertices elements, the same can be made by direct access to the vertices' vector;
		err_code  Count (const uint32_t _n_elems);   // sets the number of the required vertices, i.e. elements;
		TError&   Error (void) const;

		const void*      Data_Ptr (void) const;      // gets the pointer to vertex array data, this is the data for vertex buffer;
		const TVertData& Data_Ref (void) const;      // gets the reference to the vertex data array;

		const
		CVertex&  Get (const uint32_t _u_ndx) const; // returns the reference to the vertex object by index, in case if the index is out of range, the ref to virtual vertex is returned; 
		CVertex&  Get (const uint32_t _u_ndx) ;      // returns the reference to the vertex object by index, in case if the index is out of range, the ref to virtual vertex is returned;
		
		const
		TVertices& Items (void) const;   // gets the reference to vertex collection; (ro)
		TVertices& Items (void) ;        // gets the reference to vertex collection; (rw)

		bool   Is_valid (void) const;    // returns true in case of vertex buffer data size equals to sum of attributes' sizes;
		static
		err_code  Set_ptrs (const CAttr&, CError&);
		err_code  Set_ptrs (void) const; // it is assumed that each vertex has the same attribute set, i.e. the pos and color attributes;

		err_code  Update (void);         // updates vertex data vector by applying vertices' attribute arrays' data;
	
	private:
		CVertArray& operator = (const CVertArray&) = delete; CVertArray& operator = (CVertArray&&) = delete;
		mutable
		CError    m_error;
		TVertices m_items;  // this is the set of vertices themselves;
		TVertData m_data ;  // this is the data for vertex buffer;
		CBuffer   m_buffer;
	};

}}}

#endif/*_GL_VERTEX_ARR_DAT_H_INCLUDED*/