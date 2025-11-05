#ifndef _GL_VERTEX_ARR_H_INCLUDED
#define _GL_VERTEX_ARR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Nov-2025 at 00:45:01.915, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' vertex array object wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_vertex_attr.h"
#include "program\gl_prog_id.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace vertex {

	// https://stackoverflow.com/questions/11821336/what-are-vertex-array-objects ;
	class CArrObject {
	public:
		CArrObject (void); CArrObject (const CArrObject&) = delete; CArrObject (CArrObject&&) = delete; ~CArrObject (void);

		const
		CAttrs&  Attrs (void) const;
		CAttrs&  Attrs (void) ;

		err_code Bind  (void);        // perhaps it would be better to replace word 'bind' by 'activate' or 'current';
		bool  Is_bound (void) const;  // returns 'true' if the array is bound;
		err_code Unbind (void);       // unbinds this array by setting 0 (zero) as identifier of the array being bounded; 

		err_code Enable (const bool); // enables/disables all attributes of this array;

		err_code Create (void);
		err_code Delete (void);
		TError&  Error  (void) const;
		uint32_t GetId  (void) const;

	private:
		CArrObject& operator = (const CArrObject&) = delete; CArrObject& operator = (CArrObject&&) = delete;
		mutable
		CError   m_error;
		uint32_t m_arr_id;
		CAttrs   m_attrs;
	};

}}}}

#endif/*_GL_VERTEX_ARR_H_INCLUDED*/