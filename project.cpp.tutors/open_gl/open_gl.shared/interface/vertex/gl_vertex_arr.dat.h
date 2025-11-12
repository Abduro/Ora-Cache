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

	class CVertArray {
		public:
		CVertArray (void); CVertArray (const CVertArray&) = delete; CVertArray (CVertArray&&) = delete; ~CVertArray (void);
		const
		void*    GetData (void) const;                  // gets the pointer to vertex array data

		uint32_t GetElements (void) const;              // returns the count of vertex elements' count;
		err_code SetElements (const uint32_t _u_count); // sets the count of the vertex elements;

		TError&  Error (void) const;

	private:
		CVertArray& operator = (const CVertArray&) = delete; CVertArray& operator = (CVertArray&&) = delete;
		mutable
		CError    m_error;
		TVertData m_data ;
	};

}}}

#endif/*_GL_VERTEX_ARR_DAT_H_INCLUDED*/