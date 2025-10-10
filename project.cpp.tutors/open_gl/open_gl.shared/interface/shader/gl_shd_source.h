#ifndef _GL_SHD_SOURCE_H_INCLUDED
#define _GL_SHD_SOURCE_H_INCLUDED
/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 17:13:32.083, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader SL source wrapper interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShaderSource.xhtml ;
	class CSource {
	public: CSource (void); CSource (const CSource&); CSource (CSource&&) = delete; ~CSource (void) ;

		TErr_ex& Error (void) const;
		_pc_sz   Get (void) const;
		err_code Set (_pc_sz _p_source, const uint32_t _n_shader_id);       // sets the source text to the shader;
		err_code Set (const uint16_t _res_id, const uint32_t _n_shader_id); // loads source text from the executable resource table string;

	public: CSource& operator = (const CSource&); CSource& operator = (CSource&&) = delete;
	private:
	mutable
		CError_ex m_error ;
		CString   m_buffer;
	};

}}}}

#endif/*_GL_SHD_SOURCE_H_INCLUDED*/