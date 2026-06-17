#ifndef _GL_PROCS_PARAMS_H_INCLUDED
#define _GL_PROCS_PARAMS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Jun-2026 at 00:54:50.827, UTC+4, Batumi, Wednesday;
	This is OpenGL ver.1.1 draw object property wrapper interface declaration file;
*/
#include "gl_procs_basic.h"

namespace open_gl { namespace procs { namespace ver_1_1 {

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetbooleanv ;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetdoublev  ;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetfloatv   ;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetintegerv ;

	class CParam : public CBasic { typedef CBasic TBase;
	public:
		CParam (const uint32_t _param_id = 0); CParam (const CParam&) = delete; CParam (CParam&&) = delete; ~CParam (void) = default;
		/* attention:
		   all three below functions return plane data type value, no arrays are supposed, but with some parameter names it is available to get an array of values;
		*/
		bool    GetBool  (const uint32_t _u_param_id); // returns parameter value as boolean ;
		double  GetDouble(const uint32_t _u_param_id); // returns parameter value as double ;
		float   GetFloat (const uint32_t _u_param_id); // returns parameter value as float number; is not acceptable in some cases, for example how to get pointer to the matrix?
		int32_t GetInt   (const uint32_t _u_param_id); // returns parameter value as integer ;

		/* the query to the Google AI: if values array contains less elements as required by glGetFloatv how handle the error opengl?
		   OpenGL will not catch or report this error. Because glGetFloatv accepts a raw C-style pointer (GLfloat *params), the OpenGL driver does not know the Size of your allocated array.
		   It will blindly write the full number of required elements to your pointer, causing a buffer overflow (memory corruption) or an immediate segmentation fault / crash.
		   (1) Ensure Proper Array Sizing (The Fix):
		    (a) 1 element : Most simple state variables (e.g., GL_MAX_TEXTURE_SIZE); >> just plain float data value or ::std::array<float, 1u>;
		    (b) 2 elements: Ranges (e.g., GL_ALIASED_POINT_SIZE_RANGE); >> ::std::array<float, 0x02u>;
		    (c) 4 elements: Colors, viewports, and bounds (e.g., GL_COLOR_CLEAR_VALUE, GL_VIEWPORT); >> ::std::array<float, 0x04u>;
		    (d) and 16 elements for getting matrix data; >> ::std::array<float, 0x10u>;
		*/

		err_code Get_ptr (const uint32_t _u_param_id, double* );
		err_code Get_ptr (const uint32_t _u_param_id, float*  ); // this is for getting a pointer to specific array of float values, caller of this function must take care how many elements is returned;
		err_code Get_ptr (const uint32_t _u_param_id, int32_t*);

	private:
		CParam& operator = (const CParam&) = delete; CParam& operator = (CParam&&) = delete;
		uint32_t m_param_id;
	};

}}}

#endif/*_GL_PROCS_PARAMS_H_INCLUDED*/