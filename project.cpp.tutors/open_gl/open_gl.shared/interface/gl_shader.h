#ifndef _GL_SHADER_H_INCLUDED
#define _GL_SHADER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2025 at 23:01:56.472, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' shader base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_procs.h"
#include "gl_logs.h"

#pragma region __shader_types
/* copied from glcorearb.h */
#define GL_COMPUTE_SHADER         0x91B9
#define GL_FRAGMENT_SHADER        0x8B30
#define GL_GEOMETRY_SHADER        0x8DD9
#define GL_TESS_CONTROL_SHADER    0x8E88
#define GL_TESS_EVALUATION_SHADER 0x8E87
#define GL_VERTEX_SHADER          0x8B31
#pragma endregion

namespace ex_ui { namespace draw { namespace open_gl {

namespace shader {

	class CSource {
	public: CSource (void); CSource (const CSource&) = delete; CSource (CSource&&) = delete; ~CSource (void) ;

		TErr_ex& Error (void) const;
		err_code Set (_pc_sz _p_source, const uint32_t _n_shader_id);       // sets the source text to the shader;
		err_code Set (const uint16_t _res_id, const uint32_t _n_shader_id); // loads source text from the executable resource table string;

	private:CSource& operator = (const CSource&) = delete; CSource& operator = (CSource&&) = delete;
	mutable
		CError_ex m_error ;
		CString   m_buffer;
	};

	class CType {
	public:
		enum e_value : uint16_t {    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml ;
		     e_undef     = 0x0,
		     e_compute   = GL_COMPUTE_SHADER ,         // is intended to run on the programmable compute processor ;
		     e_fragment  = GL_FRAGMENT_SHADER,         // is intended to run on the programmable fragment processor ;
		     e_geometry  = GL_GEOMETRY_SHADER,         // is intended to run on the programmable geometry processor ;
		     e_tess_ctrl = GL_TESS_CONTROL_SHADER,     // is intended to run on the programmable tessellation processor in the control stage ;
		     e_tess_eval = GL_TESS_EVALUATION_SHADER,  // is intended to run on the programmable tessellation processor in the evaluation stage ;
		     e_vertex    = GL_VERTEX_SHADER ,          // is intended to run on the programmable vertex processor ;
		};
		CType (void); CType (const CType&) = delete; CType (CType&&) = delete; ~CType (void) = default;

		e_value Get (void) const;
		bool    Set (const e_value) ;

		operator uint16_t (void) const; // returns currently set value of the shader type;

		static CString To_str(const uint16_t _u_type);

	private:
		CType& operator = (const CType&) = delete; CType& operator = (CType&&) = delete;
		e_value m_value;
	};
}
	typedef shader::CType::e_value TType;

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

		 bool     Is_compiled (void) const;  // checks compilation status of the shader;
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
	class CFragment : public CShader { typedef CShader TBase;
	public:
		 CFragment (void);
		~CFragment (void);

		err_code Create (void);
	};

	class CVertex : public CShader { typedef CShader TBase;
	public:
		 CVertex (void);
		~CVertex (void);

		err_code Create (void);
	};
}
}}}

#endif/*_GL_SHADER_H_INCLUDED*/