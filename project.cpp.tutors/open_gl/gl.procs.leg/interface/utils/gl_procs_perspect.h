#ifndef _GL_PROCS_PERSPECT_H_INCLUDED
#define _GL_PROCS_PERSPECT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jun-2026 at 11:15:02.071, UTC+4, Batumi, Friday;
	This is OpenGL utility perspective function wrapper interface declaration file;
*/
#include "gl_procs_basic.h"
#include "matrix\gl_procs_mtx.stack.h"
/*
	These procedure wrappers are espacially intended for OpenGL vers 1.1 API (aka legacy);
*/
namespace open_gl { namespace procs { namespace utils { namespace ver_1_1 {
	
	using namespace ::shared::defs;
	using namespace ::open_gl::procs::ver_1_1;

	using f_mat_4x4 = ::open_gl::procs::f_mat_4x4;
	using CMode = ::open_gl::procs::matrix::ver_1_1::CMode;

	// https://en.cppreference.com/cpp/utility/variant ;
	// this class hides the casting inside of it;
	class c_converter {
	public:
		 c_converter (void); c_converter (const float); c_converter (const double); c_converter (const c_converter&); c_converter (c_converter&&) = delete;
		~c_converter (void) = default;

		float Float (void) const;
		double Double (void) const;

		c_converter& operator = (const c_converter&); c_converter& operator = (c_converter&&) = delete;

		double operator <<(const float);
		float  operator <<(const double);

		operator float (void) const;
		operator double (void) const;

	private:
		double m_data;
	};

	using var = c_converter;

	// https://learn.microsoft.com/en-us/windows/win32/opengl/gluperspective ;
	/* Important Tips:
	(1) always call glLoadIdentity() before gluPerspective to ensure you aren't multiplying new projection settings on top of old ones;
	(2) avoid zNear = 0: setting the near plane to zero will cause the depth-buffer math to fail, resulting in nothing being rendered or severe flickering;
	(3) matrix Mode: ensure you are in GL_PROJECTION mode when calling it, then switch back to GL_MODELVIEW for your drawing commands;
	*/
	struct s_pers_args {
		float _fov_y, _aspect, _near, _far;
		s_pers_args (void);
		s_pers_args (const float _f_fov_y, const float _f_aspect, const float _f_near, const float _f_far);

		CString To_str (void) const;
	};

	class CPers_Cfg {
	public:
		CPers_Cfg (void); CPers_Cfg (const CPers_Cfg&) = delete; CPers_Cfg (CPers_Cfg&&) = delete; ~CPers_Cfg (void) = default;

	private:
		CPers_Cfg& operator = (const CPers_Cfg&) = delete; CPers_Cfg& operator = (CPers_Cfg&&) = delete;
	};
	/* https://community.khronos.org/t/how-to-choose-between-glortho-perspective-frustum/53659/4 << good snipped code of using frustum;
	   gluPerspective is just an utility function that calls glFrustum;
	   Under the hood, gluPerspective calculates the raw mathematical coordinates and passes them directly down to the core glFrustum function.
	*/
	class CPerspect : public CBasic { typedef CBasic TBase;
	public:
		CPerspect (void); CPerspect (const CPerspect&) = delete; CPerspect (CPerspect&&) = delete; ~CPerspect (void) = default;

		const
		f_mat_4x4& Ref (void) const;
		err_code   Get (void); // queries the perspective matrix that is currently loaded in matrix stack;
		err_code   Set (const float _fov_y, const float _f_aspect, const float _f_near, const float _f_far); // generates perspective matrix;
		err_code   Set (const s_pers_args&); // generates perspective matrix;
		const
		f_mat_4x4& operator <<(const s_pers_args&); // generates the perspective matrix by setting input args and returns the matrix being generated;

	protected:
		CPerspect& operator = (const CPerspect&) = delete; CPerspect& operator = (CPerspect&&) = delete;
		f_mat_4x4  m_data;
	};
	
	class CProject : public CBasic { typedef CBasic TBase;
	public:
		CProject (void); CProject (const CProject&) = delete; CProject (CProject&&) = delete; ~CProject (void) = default;
	private:
		CProject& operator = (const CProject&) = delete; CProject& operator = (CProject&&) = delete;
	};

}}}}

#endif/*_GL_PROCS_PERSPECT_H_INCLUDED*/