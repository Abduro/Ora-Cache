#ifndef _GL_PROCS_PROJ_H_INCLUDED
#define _GL_PROCS_PROJ_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-May-2026 at 09:22:48.101, UTC+4, Batumi, Wednesday;
	This is OpenGL v.1.1 projection related function set wrapper interface declaration file;
*/
#include "gl_procs_basic.h"
#include "gl_procs_matrix.h"
/*
	These procedure wrappers are espacially intended for OpenGL vers 1.1 API (aka legacy);
*/
namespace open_gl { namespace procs { namespace ver_1_1 { namespace projection { using namespace shared::defs;

	using c_mat4x4 = ex_ui::draw::open_gl::math::c_mat4x4;
	using var = ::open_gl::procs::ver_1_1::c_converter;

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
	class CPerspect : public CBasic { typedef CBasic TBase;
	public:
		CPerspect (void); CPerspect (const CPerspect&) = delete; CPerspect (CPerspect&&) = delete; ~CPerspect (void) = default;

		const
		c_mat4x4& Get (void) const;
		err_code  Get (void); // returns the perspective matrix that is currently loaded in matrix stack;
		err_code  Set (const float _fov_y, const float _f_aspect, const float _f_near, const float _f_far); // generates perspective matrix;
		err_code  Set (const s_pers_args&); // generates perspective matrix;
		const
		c_mat4x4& operator <<(const s_pers_args&); // generates the perspective matrix by setting input args and returns the matrix being generated;
		const
		TMatMode& Mode (void) const; // returns the reference to matrix mode object; (ro)
		TMatMode& Mode (void);       // returns the reference to matrix mode object; (rw)

	protected:
		CPerspect& operator = (const CPerspect&) = delete; CPerspect& operator = (CPerspect&&) = delete;
		c_mat4x4 m_pers;
		TMatMode m_mode;
	};
	
	class CProject : public CBasic { typedef CBasic TBase;
	public:
		CProject (void); CProject (const CProject&) = delete; CProject (CProject&&) = delete; ~CProject (void) = default;
	private:
		CProject& operator = (const CProject&) = delete; CProject& operator = (CProject&&) = delete;
	};

}}}}

#endif/*_GL_PROCS_PROJ_H_INCLUDED*/