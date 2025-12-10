#ifndef _GL_VERTEX_ARR_OBJ_H_INCLUDED
#define _GL_VERTEX_ARR_OBJ_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Nov-2025 at 00:45:01.915, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' vertex array object wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_vertex_arr.dat.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace vertex {

	// https://stackoverflow.com/questions/11821336/what-are-vertex-array-objects ;
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml ;
	// vertex array object life cycle or any its function does not depend on program;
	class CArrObject {
	public:
		using CVertDat = CVertArray;
	public:
		CArrObject (void); CArrObject (const CArrObject&); CArrObject (CArrObject&&); ~CArrObject (void);

		CArrObject& operator = (const CArrObject&); CArrObject& operator = (CArrObject&&);

		err_code  Bind (void);            // perhaps it would be better to replace word 'bind' by 'activate' or 'current';
		bool      Is_bound (void) const;  // returns 'true' if the array is bound;
		err_code  Unbind (void);          // unbinds this array by setting 0 (zero) as identifier of the array being bounded; 

		err_code  Create (void);
		err_code  Delete (void);
		TError&   Error  (void) const;
		uint32_t  GetId  (void) const;

		const
		CVertDat& VertArray (void) const; // gets the reference to vertex array data; (ro)
		CVertDat& VertArray (void) ;      // gets the reference to vertex array data; (rw)

	private:
		mutable
		CError     m_error ;
		uint32_t   m_arr_id;
		CVertArray m_vex_arr;
	};

	class CArrObj_enum {
	public:
		using CArrObj = CArrObject;
	public:
		enum e_arr_ndx : uint32_t {
		     e_grid = 0x0,
		     e_tria = 0x1,
		};
		static const uint32_t u_count = e_arr_ndx::e_tria + 1; // the predefined number of the vertex array objects is the same as programs have, but it may be different;
	public:
		CArrObj_enum (void); CArrObj_enum (const CArrObj_enum&) = delete; CArrObj_enum (CArrObj_enum&&) = delete; ~CArrObj_enum (void);

		err_code Create (void);               // creates all vertex array objects;

		TError& Error (void) const;
		const
		CArrObj& Get (const e_arr_ndx) const; // if the input index is out of range the reference to invalid vertex array object is returned; (ro)
		CArrObj& Get (const e_arr_ndx) ;	  // if the input index is out of range the reference to invalid vertex array object is returned; (rw)

	private:
		CArrObj_enum& operator = (const CArrObj_enum&) = delete; CArrObj_enum& operator = (CArrObj_enum&&) = delete;
		CArrObj m_arr_objs[u_count];
		CError  m_error;
	};

}}}}

#endif/*_GL_VERTEX_ARR_OBJ_H_INCLUDED*/