#ifndef _GL_PROCS_VERTEX_H_INCLUDED
#define _GL_PROCS_VERTEX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Oct-2025 at 12:10:39.867, (UTC+4), Batumi, Monday;
	This is Ebo Pack OpenGL vertex related functions' loader interface declaration file;
*/
#include "gl_procs_base.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
namespace vertex {

	// https://wikis.khronos.org/opengl/OpenGL_Type ;

	#define GL_FIXED              0x140C  // from glcorearb.h ; supported from version 4.1;
	#define GL_INT_2_10_10_10_REV 0x8D9F  // from glcorearb.h ; ToDo: brief desc is required;
	#define GL_UNSIGNED_INT_2_10_10_10_REV  0x8368 // from glcorearb.h ; ToDo: brief desc is required;
	#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8C3B // from glcorearb.h ; ToDo: brief desc is required;

	// using enumerations instead of #defines makes easier the selection of required value that is pros, but cons the cast is required;
	enum class e_att_val_int : uint32_t {
	e_byte  = GL_BYTE , e_u_byte  = GL_UNSIGNED_BYTE ,
	e_short = GL_SHORT, e_u_short = GL_UNSIGNED_SHORT,
	e_int   = GL_INT  , e_u_int   = GL_UNSIGNED_INT  ,
	e_fixed = GL_FIXED,
	e_int_2_10_10_10 = GL_INT_2_10_10_10_REV, e_uint_2_10_10_10 = GL_UNSIGNED_INT_2_10_10_10_REV, e_uint_10_11_11 = GL_UNSIGNED_INT_10F_11F_11F_REV
	};
	static __inline uint32_t _i_to_u(const e_att_val_int _e_el) { return static_cast<uint32_t>(_e_el);}

	#define GL_HALF_FLOAT 0x140B // from glcorearb.h ; supported from version 4.1;
	enum class e_att_val_float : uint32_t {
	e_double = GL_DOUBLE, e_float = GL_FLOAT, e_float_16bits = GL_HALF_FLOAT,
	};
	static __inline uint32_t _i_to_f(const e_att_val_float _e_el) { return static_cast<uint32_t>(_e_el);}

	class CArray : public CBase {
	typedef void (__stdcall *pfn_Binding) (uint32_t _arr_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml ;
	typedef void (__stdcall *pfn_Delete ) (int32_t _n_count, const uint32_t* _p_arrays); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml ;
	typedef void (__stdcall *pfn_Disable) (uint32_t _u_ndx);  // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
	typedef void (__stdcall *pfn_Enable ) (uint32_t _u_ndx);
	typedef void (__stdcall *pfn_GetIds ) (int32_t _n_count, uint32_t* _p_ids); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml ;
	typedef int32_t (__stdcall *pfn_IsArr) (uint32_t _u_arr_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsVertexArray.xhtml ; (no ms windows doc);
	public:
		CArray (void); ~CArray (void) = default;

		err_code Bind    (const uint32_t _arr_id); // binds the vertex array object with identifier (aka name) of the array; in case of _arr_id == 0, unbound process is initiated;
		err_code Delete  (const uint32_t _n_count, const uint32_t* _p_arrays); // deletes vertex array objects;
		err_code Disable (const uint32_t _u_ndx);  // disables currently bound vertex array object for the operation;
		err_code Enable  (const uint32_t _u_ndx);  // enables currently bound vertex array object for the operation;
		err_code GetIds  (const uint32_t _n_count, uint32_t* _p_ids); // generates vertex array object identifiers (aka names) and guarantees that none of the returned names was in use immediately before the call to it ;
		/* the excerpt from https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsVertexArray.xhtml :
		return false is cases
		...if array is zero, or if array is not the name of a vertex array object, or if an error occurs...
		...if array is a name returned by glGenVertexArrays, by that has not yet been bound through a call to glBindVertexArray...
		*/
		bool Is_array (const uint32_t _arr_id); // determines if an identifier (aka name) corresponds to a vertex array object;
	};
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
	// surprisingly weird documentation if above article mixes the array of attributes enabling/disabling with the same properties of an attribute itself;
	class CAttr : public CBase {
	typedef void (__stdcall *pfn_Disable) (uint32_t _arr_id, uint32_t _n_ndx);
	typedef void (__stdcall *pfn_Enable ) (uint32_t _arr_id, uint32_t _n_ndx);
	public:
		CAttr (void); ~CAttr (void) = default;

		err_code Disable (const uint32_t _arr_id, const uint32_t _n_ndx); // disables an attribute by index and updates state of the vertex array object with _arr_id ;
		err_code Enable  (const uint32_t _arr_id, const uint32_t _n_ndx); // enables an attribute by index and updates state of the vertex array object with _arr_id ;
	};

	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml ;
	class CAttPtr : public CBase {
	typedef void (__stdcall *pfn_AttPtr)   (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, uint16_t _b_norm, int32_t _n_stride, const void* _ptr);
	typedef void (__stdcall *pfn_AttPtr_I) (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void* _ptr);
	typedef void (__stdcall *pfn_AttPtr_L) (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void* _ptr);
	public:
		CAttPtr (void); ~CAttPtr (void) = default;
		// the input arg 'size' should *not* have 'signed int' data type, because all acceptable values are greater than 0 (zero);
		// the input arg 'stride' may have value 0 or greater; its data type intentionally is changed to 'unsigned';
		err_code Get   (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const bool _b_normalized, const uint32_t _u_stride, const uint32_t _u_offset = 0); // defines an array of generic vertex attribute data (signed & unsigned) ;
		err_code Get_I (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const uint32_t _u_stride, const uint32_t _u_offset = 0); // the integer types GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT ;
		err_code Get_L (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const uint32_t _u_stride, const uint32_t _u_offset = 0); // specifies state for a generic vertex attribute array associated with a shader attribute variable declared with 64-bit double precision components ;
	private:
		CAttPtr& operator = (const CAttPtr&) = delete; CAttPtr& operator = (CAttPtr&&) = delete;
	};
}
}}}}

#endif/*_GL_PROCS_VERTEX_H_INCLUDED*/