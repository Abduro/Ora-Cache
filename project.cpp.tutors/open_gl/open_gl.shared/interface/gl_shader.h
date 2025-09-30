#ifndef _GL_SHADER_H_INCLUDED
#define _GL_SHADER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2025 at 23:01:56.472, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' shader base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_procs.h"
#include "gl_logs.h"
#include "shader\gl_shd_source.h"
#include "shader\gl_shd_type.h"
#include "shader\gl_shd_status.h"

namespace ex_ui { namespace draw { namespace open_gl {

namespace shader {
}
	// https://www.khronos.org/opengl/wiki/shader ;
	class CShader {
	public:
		 CShader (void); CShader (const CShader&) = delete; CShader (CShader&&) = delete;
		~CShader (void);

		 static procs::CShader& Cache (void) ;
		 static CString  Class (void);       // returns this class name for debug purposes;

		 err_code Create (const TType);
		 err_code Destroy (void);

		 TErr_ex& Error (void) const;
		 uint32_t Id (void) const;

		 bool     Is_compiled (void) const;  // checks compilation status of the shader; the shader::CStatus::Is_compiled actually is called;
		 bool     Is_valid (void) const;     // checks the validity of the shaper but after its compilation only, otherwise it returns 'false';
		 static
		 bool     Is_valid (const uint32_t _u_shader_id, CError&);

		 const
		 shader::CSource&  Src (void) const;
		 shader::CSource&  Src (void) ;

		 const
		 shader::CType& Type (void) const;
		 shader::CType& Type (void) ;

	private:
		 CShader& operator = (const CShader&) = delete; CShader& operator = (CShader&&) = delete;
	protected:
		 mutable
		 CError_ex m_error;
		 uint32_t  m_id ;
		 shader::CSource m_src ;
		 shader::CType  m_type ;
	};

namespace shader {
	// https://www.khronos.org/opengl/wiki/Fragment_Shader ;
	class CFragment : public CShader { typedef CShader TBase;
	public:
		 CFragment (void);
		~CFragment (void);

		err_code Create (void);
	};
	// https://www.khronos.org/opengl/wiki/Vertex_Shader ;
	class CVertex : public CShader { typedef CShader TBase;
	public:
		 CVertex (void);
		~CVertex (void);

		err_code Create (void);
	};
}
}}}

#endif/*_GL_SHADER_H_INCLUDED*/