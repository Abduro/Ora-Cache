#ifndef _GL_SHADER_H_INCLUDED
#define _GL_SHADER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2025 at 23:01:56.472, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' shader base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_procs.h"

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

	class CLog { public: CLog(void); CLog (const CLog&) = delete; CLog (CLog&&) = delete; ~CLog (void) ;
	private: CLog& operator = (const CLog&) = delete; CLog& operator = (CLog&&) = delete;
	public:
		TErr_ex& Error (void) const;

		_pc_sz   Get (void) const;                    // returns log info ;
		err_code Set (const uint32_t _u_shader_id) ;  // retrieves the log info from current state of specified _u_shader_id to string buffer;

	private:
		mutable
		CError_ex m_error ;
		CString   m_buffer;  // stores the log info;
	};

	class CCompiler {
	public:
		CCompiler (const uint32_t _u_shader_id = 0); CCompiler (const CCompiler&) = delete; CCompiler (CCompiler&&) = delete; ~CCompiler (void);

		err_code Compile (void);              // tries to compile assigned code to the shader;

		TErr_ex& Error (void) const;

		bool  Is_compiled  (void) const;      // checks compilation status of the shader; if it is false, either no compilation was made or getting log info is required for details;
		bool  Is_supported (void) const;
		const
		CLog&    Log (void) const;
		CLog&    Log (void) ;

		uint32_t ShaderId  (void) const;
		err_code ShaderId  (const uint32_t);  // returns an error code in case if input shader identifier is not valid;

		CCompiler& operator <<(const uint32_t _u_shader_id);

	private:
		CCompiler& operator = (const CCompiler&) = delete; CCompiler& operator = (CCompiler&&) = delete;
		mutable
		CError_ex  m_error;
		uint32_t   m_shader_id;
		CLog  m_log;
	};

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