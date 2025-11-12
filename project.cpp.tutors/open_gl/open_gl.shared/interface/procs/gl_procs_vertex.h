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

	/* GL_UNSIGNED_INT_2_10_10_10_REV: specifies a packed vertex attribute format to 32-bit signed integer;
	(1) colors with reduced alpha precision: 2-bit integer for the W (or alpha) component (30-31);
	(2) normals: the 10-bit precision for X, Y, and Z components offers a good balance between precision and memory efficiency for normalized vectors;
	(3) tangents and binormals: similar to normals, these vectors benefit from the reduced memory footprint;
	pakiging is in reverse order: uint32_t = (alpha << 30) 2-bit; (x << 20); 10-bit x/red; (y << 10); 10-bit y/green; (z << 0); 10-bit z;
	*/
	#define GL_INT_2_10_10_10_REV 0x8D9F  // from glcorearb.h          ; indicating four signed elements packed into a single GLuint;
	#define GL_UNSIGNED_INT_2_10_10_10_REV  0x8368 // from glcorearb.h ; indicating four unsigned elements packed into a single GLuint;

	/* GL_UNSIGNED_INT_10F_11F_11F_REV: specifies a packed format for floating-point data to 32-bit integer; since ver.4.4;
	(1) often used for colors or normal vectors;
	packiging is in reverse order: uint32_t = (x << 22) 10-bit x/red; (y << 11) 11-bit y/green; (z << 0) 11-bit z/blue; 
	*/
	#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8C3B // from glcorearb.h ; indicating three floating point values packed into a single GLuint;

	// using enumerations instead of #defines makes easier the selection of required value that is pros, but cons the cast is required;
	enum class e_att_val_int : uint32_t {
	e_byte  = 0x1400, /*GL_BYTE */ e_u_byte  = 0x1401, /*GL_UNSIGNED_BYTE */
	e_short = 0x1402, /*GL_SHORT*/ e_u_short = 0x1403, /*GL_UNSIGNED_SHORT*/
	e_int   = 0x1404, /*GL_INT  */ e_u_int   = 0x1405, /*GL_UNSIGNED_INT  */
	e_fixed = 0x140C, /*GL_FIXED*/
	e_int_2_10_10_10 = GL_INT_2_10_10_10_REV, e_uint_2_10_10_10 = GL_UNSIGNED_INT_2_10_10_10_REV, e_uint_10_11_11 = GL_UNSIGNED_INT_10F_11F_11F_REV
	};
	static __inline uint32_t _i_to_u(const e_att_val_int _e_el) { return static_cast<uint32_t>(_e_el);}

	enum class e_att_val_float : uint32_t {
	e_double = 0x140A, /*GL_DOUBLE*/
	e_float  = 0x1406, /*GL_FLOAT */
	e_float_16bits = 0x140B /*GL_HALF_FLOAT*/,
	};
	static __inline uint32_t _i_to_f(const e_att_val_float _e_el) { return static_cast<uint32_t>(_e_el);}

	enum class e_att_val_vec : uint32_t {
	e_bool_vec2 = 0x8B57, /*GL_BOOL_VEC2*/ e_dbl_vec2 = 0x8FFC, /*GL_DOUBLE_VEC2*/ e_float_vec2 = 0x8B50, /*GL_FLOAT_VEC2*/ e_int_vec2 = 0x8B53, /*GL_INT_VEC2*/ e_uint_vec2 = 0x8DC6, /*GL_UNSIGNED_INT_VEC2*/
	e_bool_vec3 = 0x8B58, /*GL_BOOL_VEC3*/ e_dbl_vec3 = 0x8FFD, /*GL_DOUBLE_VEC3*/ e_float_vec3 = 0x8B51, /*GL_FLOAT_VEC3*/ e_int_vec3 = 0x8B54, /*GL_INT_VEC3*/ e_uint_vec3 = 0x8DC7, /*GL_UNSIGNED_INT_VEC3*/
	e_bool_vec4 = 0x8B59, /*GL_BOOL_VEC4*/ e_dbl_vec4 = 0x8FFE, /*GL_DOUBLE_VEC4*/ e_float_vec4 = 0x8B52, /*GL_FLOAT_VEC4*/ e_int_vec4 = 0x8B55, /*GL_INT_VEC4*/ e_uint_vec4 = 0x8DC8, /*GL_UNSIGNED_INT_VEC4*/
	};

	enum class e_att_val_mtx : uint32_t {
	e_dbl_mtx2   = 0x8F46, /*GL_DOUBLE_MAT2*/   e_float_mtx2 = 0x8B5A, /*GL_FLOAT_MAT2*/  e_float_mtx2x3 = 0x8B65, /*GL_FLOAT_MAT2x3*/ e_float_mtx3x4 = 0x8B68, /*GL_FLOAT_MAT3x4*/
	e_dbl_mtx3   = 0x8F47, /*GL_DOUBLE_MAT3*/   e_float_mtx3 = 0x8B5B, /*GL_FLOAT_MAT3*/  e_float_mtx2x4 = 0x8B66, /*GL_FLOAT_MAT2x4*/ e_float_mtx4x2 = 0x8B69, /*GL_FLOAT_MAT4x3*/
	e_dbl_mtx4   = 0x8F48, /*GL_DOUBLE_MAT4*/   e_float_mtx4 = 0x8B5C, /*GL_FLOAT_MAT4*/  e_float_mtx3x2 = 0x8B67, /*GL_FLOAT_MAT3x2*/ e_float_mtx4x4 = 0x8B6A, /*GL_FLOAT_MAT4x4*/
	e_dbl_mtx2x3 = 0x8F49, /*GL_DOUBLE_MAT2x3*/ e_dbl_mtx3x2 = 0x8F4B, /*GL_DOUBLE_MAT3x2*/ e_dbl_mtx4x2 = 0x8F4D, /*GL_DOUBLE_MAT4x2*/ 
	e_dbl_mtx2x4 = 0x8F4A, /*GL_DOUBLE_MAT2x4*/ e_dbl_mtx3x4 = 0x8F4C, /*GL_DOUBLE_MAT3x4*/ e_dbl_mtx4x3 = 0x8F4E, /*GL_DOUBLE_MAT4x3*/ 
	};

	class CArray : public CBase {
	typedef void (__stdcall *pfn_Binding) (uint32_t _arr_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml ;
	typedef void (__stdcall *pfn_Delete ) (int32_t _n_count, const uint32_t* _p_arrays); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml ;
	typedef void (__stdcall *pfn_GetIds ) (int32_t _n_count, uint32_t* _p_ids); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml ;
	typedef int32_t (__stdcall *pfn_IsArr) (uint32_t _u_arr_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsVertexArray.xhtml ; (no ms windows doc);
	public:
		CArray (void); ~CArray (void) = default;

		err_code Bind    (const uint32_t _arr_id); // binds the vertex array object with identifier (aka name) of the array; in case of _arr_id == 0, unbound process is initiated;
		err_code Delete  (const uint32_t _n_count, const uint32_t* _p_arrays); // deletes vertex array objects;
		err_code GetIds  (const uint32_t _n_count, uint32_t* _p_ids); // generates vertex array object identifiers (aka names) and guarantees that none of the returned names was in use immediately before the call to it ;
		/* the excerpt from https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsVertexArray.xhtml :
		return false in cases
		...if array is zero, or if array is not the name of a vertex array object, or if an error occurs...
		...if array is a name returned by glGenVertexArrays, by that has not yet been bound through a call to glBindVertexArray...
		*/
		bool Is_array (const uint32_t _arr_id); // determines if an identifier (aka name) corresponds to a vertex array object;

		err_code Get_all (void) ;

	private:
		CArray& operator = (const CArray&) = delete; CArray& operator = (CArray&&) = delete;
	};

	class CAttr : public CBase {
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetActiveAttrib.xhtml ;
	typedef void    (__stdcall *pfn_Active ) (uint32_t _prog_id, uint32_t _n_ndx, uint32_t _u_buf_size, uint32_t* _p_length, int32_t* _p_size, uint32_t* _p_type, char* _p_name);
	typedef void    (__stdcall *pfn_Disable) (uint32_t _arr_id , uint32_t _n_ndx); // since v.4.5; // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
	typedef void    (__stdcall *pfn_Enable ) (uint32_t _arr_id , uint32_t _n_ndx); // since v.4.5; // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
	typedef int32_t (__stdcall *pfn_GetIndex)(uint32_t _prog_id, const char* _p_att_name);         // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttribLocation.xhtml ;
	typedef void    (__stdcall *pfn_SetIndex)(uint32_t _prog_id, uint32_t _u_ndx, const char* _p_att_name); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindAttribLocation.xhtml ;
	public:
		CAttr (void); ~CAttr (void) = default;

		err_code Disable  (const uint32_t _arr_id , const uint32_t _n_ndx); // disables an attribute by index and updates state of the vertex array object with _arr_id ;
		err_code Enable   (const uint32_t _arr_id , const uint32_t _n_ndx); // enables an attribute by index and updates state of the vertex array object with _arr_id ;
		err_code GetActive(const uint32_t _prog_id, const uint32_t _n_ndx, uint32_t& _u_size, uint32_t& _u_type, CString& _name); // gets info of an active attribute variable for the specified program object;
		int32_t  GetIndex (const uint32_t _prog_id, _pc_sz _p_att_name);    // returns the location (i.e. the index) of an attribute variable ; *after* the link;
		err_code SetIndex (const uint32_t _prog_id, _pc_sz _p_att_name, const uint32_t _u_ndx); // sets the index *before* the link, otherwise no effect;

		err_code Get_all (void) ;

	private:
		CAttr& operator = (const CAttr&) = delete; CAttr& operator = (CAttr&&) = delete;
	};

	class CAttrArray : public CBase {
	typedef void (__stdcall *pfn_Disable) (uint32_t _u_ndx);  // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
	typedef void (__stdcall *pfn_Enable ) (uint32_t _u_ndx);  // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
	public:
		CAttrArray (void); ~CAttrArray (void) = default;

		err_code Disable (const uint32_t _u_ndx);  // disables currently bound vertex attribute array object for the operation;
		err_code Enable  (const uint32_t _u_ndx);  // enables currently bound vertex attribute array object for the operation;

		err_code Get_all (void) ;

	private:
		CAttrArray& operator = (const CAttrArray&) = delete; CAttrArray& operator = (CAttrArray&&) = delete;
	};

	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml ;
	class CAttrPtr : public CBase {
	typedef void (__stdcall *pfn_AttPtr)   (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, uint16_t _b_norm, int32_t _n_stride, const void* _ptr);
	typedef void (__stdcall *pfn_AttPtr_I) (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void* _ptr);
	typedef void (__stdcall *pfn_AttPtr_L) (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void* _ptr);
	public:
		CAttrPtr (void); ~CAttrPtr (void) = default;
		// the input arg 'size' should *not* have 'signed int' data type, because all acceptable values are greater than 0 (zero);
		// the input arg 'stride' may have value 0 or greater; its data type intentionally is changed to 'unsigned';
		err_code Set   (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const bool _b_normalized, const uint32_t _u_stride, const uint32_t _u_offset = 0); // defines an array of generic vertex attribute data (signed & unsigned) ;
		err_code Set_I (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const uint32_t _u_stride, const uint32_t _u_offset = 0); // the integer types GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT ;
		err_code Set_L (const uint32_t _u_ndx, const uint32_t _u_size, const uint32_t _u_type, const uint32_t _u_stride, const uint32_t _u_offset = 0); // specifies state for a generic vertex attribute array associated with a shader attribute variable declared with 64-bit double precision components ;

		err_code Get_all (void) ;

	private:
		CAttrPtr& operator = (const CAttrPtr&) = delete; CAttrPtr& operator = (CAttrPtr&&) = delete;
	};
}
}}}}

typedef ex_ui::draw::open_gl::procs::vertex::CArray     TVertArrProcs;      TVertArrProcs&  __get_arr_procs (void);
typedef ex_ui::draw::open_gl::procs::vertex::CAttr      TVertAttrProcs;     TVertAttrProcs& __get_attr_procs (void);
typedef ex_ui::draw::open_gl::procs::vertex::CAttrArray TAttrArrProcs;      TAttrArrProcs&  __get_attr_arr_procs (void);
typedef ex_ui::draw::open_gl::procs::vertex::CAttrPtr   TVertAttrPtrProcs;  TVertAttrPtrProcs& __get_attr_ptr_procs (void);

#endif/*_GL_PROCS_VERTEX_H_INCLUDED*/