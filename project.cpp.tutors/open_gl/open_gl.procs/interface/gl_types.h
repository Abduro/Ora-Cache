#ifndef _GL_TYPES_H_INCLUDED
#define _GL_TYPES_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jan-2026 at 00:38:22.282, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL data types' enumeration interface declaration file;
*/
#include "gl_procs_base.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace procs {

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

	class CType {
	public:
		CType (const uint32_t = 0); CType (const CType&); CType (CType&&); ~CType (void) = default;

		static bool  Is_float (const uint32_t _u_type);
		static bool  Is_int (const uint32_t _u_type);
		static bool  Is_vec (const uint32_t _u_type);
#pragma region __for_trace
		static CString To_str (const e_att_val_float);
		static CString To_str (const e_att_val_int);
		static CString To_str (const e_att_val_vec);
		static CString To_str (const e_att_val_mtx);
#pragma endregion

		uint32_t Get (void) const;     // gets the currently set type value;
		bool     Set (const uint32_t); // sets the type value; returns 'true' in case of type value change;

		const
		uint32_t& Ref (void) const;
		uint32_t& Ref (void);          // is used for providing the reference for functions as out-argument;

		CString  To_str (void) const;  // converts data type assigned to this class to string;

		CType& operator <<(const uint32_t); // sets the type value;
		CType& operator = (const CType&);
		CType& operator = (CType&&);

	private:
		uint32_t  m_data;
	};
}}}}

#endif/*_GL_TYPES_H_INCLUDED*/