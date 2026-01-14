#ifndef _GL_UNIFORM_H_INCLUDED
#define _GL_UNIFORM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Dec-2025 at 11:28:10.278, UTC+4, Batumi, Tuesday;
	This Ebo Pack OpenGL shader variable uniform data type wrapper interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace vars {

	class CUniform : no_copy {
	public:
		class CValue : no_copy {
		public:
			CValue (CUniform* = nullptr); ~CValue (void) = default;

			TError& Error (void) const;

		private:
			CUniform* m_p_form;
			CError    m_error ;
		};

	public:
		CUniform (void); ~CUniform (void);

		TError& Error (void) const;
		_pc_sz  Name  (void) const;
		bool    Name  (_pc_sz);
		const
		CValue& Value (void) const;
		CValue& Value (void) ;

	private:
		CError  m_error;
		CString m_name ; // this is variable name that is used inside of shader source code;
		CValue  m_value;
	};

	typedef ::std::vector<CUniform> TUniVars;

	class CUniform_enum : no_copy {
	public:
		CUniform_enum (void); ~CUniform_enum (void);
		static
		uint32_t Count (const uint32_t prog_id,  CError&); // gets count of uniforms in the active/bound program object;
		uint32_t Count (void) const; // gets active program reference from the global renderer;
		TError&  Error (void) const;
		static
		err_code Get (const uint32_t prog_id, TUniVars&, CError&); // enumerates all uniform variables;
	
	private:
		mutable
		CError  m_error;
	};

}
}}}

#endif/*_GL_UNIFORM_H_INCLUDED*/