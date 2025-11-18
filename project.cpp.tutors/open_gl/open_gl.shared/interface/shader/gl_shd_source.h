#ifndef _GL_SHD_SOURCE_H_INCLUDED
#define _GL_SHD_SOURCE_H_INCLUDED
/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 17:13:32.083, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader SL source wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "win.app.res.h"
#include "shader\gl_shd_type.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

	using namespace shared::app::res;

	class CSrc_Cfg {
	public:
		enum e_prefer : uint32_t {
		e_undef = 0x0,  // no preference is defined;
		e_res   = 0x1,  // loading from a resource of the executable by specified string table identifier;
		e_file  = 0x2,  // loading from a disk file by path specified;
		};
		CSrc_Cfg (void); CSrc_Cfg (const CSrc_Cfg&); CSrc_Cfg (CSrc_Cfg&&) = delete; ~CSrc_Cfg (void);

		TError&   Error  (void) const;

		bool   Is_valid  (void) const;

		e_prefer  Prefer (void) const;
		bool      Prefer (const e_prefer); // returns 'true' in case of preference change;

		uint16_t  ResId  (void) const;
		err_code  ResId  (const uint16_t, const e_res_types); // checks the availability of resources in the executable file that created this process;

		_pc_sz    Path   (void) const;
		err_code  Path   (const $Type);    // the path to source file for particular type of shader is loaded from system registry;
		err_code  Path   (_pc_sz);         // sets the path to the file directly, the path is checked in order to guarantee the file exists;

		CSrc_Cfg& operator <<(const e_prefer);
		CSrc_Cfg& operator <<(const uint16_t);
		CSrc_Cfg& operator <<(_pc_sz _p_path);

	public:
		CSrc_Cfg& operator = (const CSrc_Cfg&); CSrc_Cfg& operator = (CSrc_Cfg&&) = delete;
	private:
	mutable
		CError    m_error ;
		e_prefer  m_prefer;
		uint16_t  m_res_id;
		CString   m_path  ;
	};

	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShaderSource.xhtml ;
	class CSource {
	public: CSource (void); CSource (const CSource&); CSource (CSource&&) = delete; ~CSource (void) ;
		static
		CString  Class (void);
		const
		CSrc_Cfg& Cfg (void) const;
		CSrc_Cfg& Cfg (void) ;

		uint32_t $Id  (void) const;     // returns the shader identifier for which this code sourse belongs to;
		err_code $Id  (const uint32_t); // sets the shader identifier; returns __s_ok on change, __s_false - no change, otherwise the error code;

		TError&  Error (void) const;
		_pc_sz   Get (void) const;

		err_code Load (const uint16_t _res_id, const uint32_t _n_shader_id); // loads source text from the executable resource table string;
		err_code Load (_pc_sz _p_path, const uint32_t _n_shader_id);         // loads the shader source code file ;

		err_code Set (_pc_sz _p_source, const uint32_t _n_shader_id);        // sets the source text to the shader;
		err_code Set (void); // it is assumed the source cfg is already set;

	public: CSource& operator = (const CSource&); CSource& operator = (CSource&&) = delete; CSource& operator <<(const uint32_t _shader_id);
	private:
	mutable
		CError   m_error ;
		CString  m_buffer;
		CSrc_Cfg m_cfg ;
		uint32_t m_$_id;
	};

}}}}

#endif/*_GL_SHD_SOURCE_H_INCLUDED*/