#ifndef _GL_PROCS_MTX_MODE_H_INCLUDED
#define _GL_PROCS_MTX_MODE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Feb-2026 at 12:27:07.062, (UTC+4), Batumi, Thursday;
	This is Ebo Pack OpenGL math matrix mode functions' loader interface declaration file;
*/
#include "gl_procs_base.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
namespace matrix {
	// https://docs.gl/gl3/glMatrixMode;
	// https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glMatrixMode.xml ;
	enum e_mat_mode : uint32_t {
	/* alias    | value    | OpenGL symbolic defs(gl.h)| brief description ;
	------------+----------+---------------------------+-------------------*/
	e_color     = 0x1800,  // GL_COLOR                 | applies subsequent matrix operations to the color matrix stack;
	e_modelview = 0x1700,  // GL_MODELVIEW             | applies subsequent matrix operations to the modelview matrix stack; (default mode);
	e_project   = 0x1701,  // GL_PROJECTION            | applies subsequent matrix operations to the projection matrix stack;
	e_texture   = 0x1702,  // GL_TEXTURE               | applies subsequent matrix operations to the texture matrix stack;
	e_undef     = 0x0,     // for error case;
	};

	_pc_sz _mat_mode_2_str(const e_mat_mode);

	typedef e_mat_mode e_mat_type;

	class CMode : public CBase {
	typedef void (__stdcall *pfn_Set)(const uint32_t u_mode);
	public:
		CMode (void); ~CMode (void) = default;

		err_code   Get_all (void);

		e_mat_mode Get (void) const;       // returns e_mat_mode::e_undef in case of error;
		err_code   Set (const e_mat_mode); // sets the current mode of the matrix stack;

		static bool   Is_code (const e_mat_type); // checks for e_mat_mode::e_undef;
		static _pc_sz To_str (const e_mat_mode);  // calls above function _mat_mode_2_str(), but for convenient call only; 

	private:
		CMode& operator = (const CMode&) = delete; CMode& operator = (CMode&&) = delete;
	};

}}}}}

typedef ex_ui::draw::open_gl::procs::matrix::CMode TMatModeProcs; TMatModeProcs& __get_mat_mode_procs (void);

#endif/*_GL_PROCS_MTX_MODE_H_INCLUDED*/