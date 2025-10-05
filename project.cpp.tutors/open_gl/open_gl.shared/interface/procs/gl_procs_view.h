#ifndef _GL_PROCS_VIEW_H_INCLUDED
#define _GL_PROCS_VIEW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Oct-2025 at 16:10:13.881, (UTC+4), Batumi, Saturday;
	This is Ebo Pack OpenGL viewport functions' loader interface declaration file;
*/
#include "gl_procs_base.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace procs {

	class CDepth : public CBase {
	typedef void (__stdcall *pfn_Compare) (uint32_t _u_rule); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDepthFunc.xhtml ; https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthfunc ;
	typedef void (__stdcall *pfn_Range_D) (double _d_near, double _d_far);// https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthrange ;
	typedef void (__stdcall *pfn_Range_F) (float _f_near, float _f_far);  // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDepthRange.xhtml ;
	public:
		CDepth (void); ~CDepth (void) = default;

		err_code SetCompareRule (const uint32_t _u_rule);     // set compare rule like this: GL_NEVER, GL_LESS, GL_EQUAL, etc; GL_LESS is set by default;
		err_code SetRange_D (const double _d_near, const double _d_far);  // specifies a linear mapping of the normalized depth coordinates in this range to window depth ones;
		err_code SetRange_F (const float _f_near, const float _f_far);    // this function is the same as above one, and just is the replacement for the other one: GLclampf();

	private:
		CDepth& operator = (const CDepth&) = delete; CDepth& operator = (CDepth&&) = delete;
	};

	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glViewport.xhtml ;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glviewport ;
	class CViewport : public CBase {
	
	typedef void (__stdcall *pfn_Offset)(float _f_factor, float _f_units); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glPolygonOffset.xhtml ;
	typedef void (__stdcall *pfn_Set) (int32_t _x, int32_t _y, uint32_t _u_width, uint32_t _u_height); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glViewport.xhtml ;
	public:
		CViewport (void); ~CViewport (void) = default;
		// https://learn.microsoft.com/en-us/windows/win32/opengl/glpolygonoffset ;
		err_code Offset (const float _f_factor, const float _f_unit); // sets the scale and units OpenGL uses to calculate depth values;
		// https://en.wikipedia.org/wiki/Affine_transformation ;
		err_code Set (const int32_t _x, const int32_t _y, const uint32_t _u_width, const uint32_t _u_height); // specifies the affine transformation of x and y from normalized device coordinates to window coordinates;
	private:
		CViewport& operator = (const CViewport&) = delete; CViewport& operator = (CViewport&&) = delete;
	};
}}}}

#endif/*_GL_PROCS_VIEW_H_INCLUDED*/