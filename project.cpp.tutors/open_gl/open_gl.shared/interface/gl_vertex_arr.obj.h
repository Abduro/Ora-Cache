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
	using e_object = CPipeline::e_object;
	// vertex array object (aka vao) life cycle or any its function does not depend on program;
	class CArrObject : public CPipeline {
	public:
		using CVertDat = CVertArray;
	public:
		CArrObject (void); CArrObject (const CArrObject&); CArrObject (CArrObject&&); ~CArrObject (void);

		CArrObject& operator = (const CArrObject&); CArrObject& operator = (CArrObject&&);

		err_code  Bind (void);            // perhaps it would be better to replace word 'bind' by 'activate' or 'current'; 

		err_code  Create (void);          // creates this vertex array object (aka vao) and vertex data array; sets program identifiers to vertex data array attributes;
		err_code  Delete (void);          // deletes this vertex array object, vertex data array and vertex buffer object (aka vbo);
		TError&   Error  (void) const;
		uint32_t  GetId  (void) const;

		bool    Is_bound (void) const;  // returns 'true' if the array is bound;
		/* the requirements:
		(1) vertex array object binding; the object defines vertex array data through attributes by using glBindVertexArray();
		(2) the buffer binding through glBindBuffer();
		(3) defining the data format through glBufferData();
		(4) setting vertex array pointers by using glVertexAttribPointer();
		(5) enabling vertex array attributes through glEnableVertexAttribArray();
		*/
		err_code  SetData (const TVertData&);
		const
		CVertDat& VertArray (void) const; // gets the reference to vertex array data; (ro)
		CVertDat& VertArray (void) ;      // gets the reference to vertex array data; (rw)

		err_code  Unbind (void);          // unbinds this array by setting 0 (zero) as identifier of the array being bounded;

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
		CArrObj_enum (void); CArrObj_enum (const CArrObj_enum&) = delete; CArrObj_enum (CArrObj_enum&&) = delete; ~CArrObj_enum (void);

		err_code Create (void);                 // creates all vertex array objects;

		TError&  Error (void) const;
		const
		CArrObject& Get (const e_object) const; // gets the reference to the vertex array object by target object enum; (ro)
		CArrObject& Get (const e_object) ;	    // gets the reference to the vertex array object by target object enum; (rw)
		const
		CArrObject& Ref (const uint32_t _u_ndx) const; // if the input index is out of range the reference to invalid vertex array object is returned; (ro)
		CArrObject& Ref (const uint32_t _u_ndx) ;	    // if the input index is out of range the reference to invalid vertex array object is returned; (rw)

	private:
		CArrObj_enum& operator = (const CArrObj_enum&) = delete; CArrObj_enum& operator = (CArrObj_enum&&) = delete;
		
		CError  m_error;
		CArrObj m_objects[CPipeline::u_tgt_count];
	};

}}}}

#endif/*_GL_VERTEX_ARR_OBJ_H_INCLUDED*/