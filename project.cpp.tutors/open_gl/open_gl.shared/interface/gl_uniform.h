#ifndef _GL_UNIFORM_H_INCLUDED
#define _GL_UNIFORM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Dec-2025 at 11:28:10.278, UTC+4, Batumi, Tuesday;
	This Ebo Pack OpenGL shader variable uniform data type wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_types.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace vars {

	using CType = procs::CType;

	class CUniform : public TPipe {
	public:
		class CValue {
		public:
			CValue (CUniform* = nullptr); ~CValue (void) = default; CValue (const CValue&); CValue (CValue&&);

			TError& Error (void) const;

			err_code Get (void) ; // gets the value of this uniform variable in accordance with its data type;
			const
			CType&  Type (void) const;
			CType&  Type (void) ;

			CValue& operator = (const CValue&); CValue& operator = (CValue&&);
			CValue& operator <<(const CType&);

		private:
			CUniform* m_p_form; // is not used in copy, move ctors and assign operators; otherwise it must be a shared_ptr or the reference;
			CError    m_error ;
			CType     m_type  ;
		};

	public:
		static const uint32_t u_inv_ndx = (uint32_t)-1;
		CUniform (const e_object = e_object::e_none); ~CUniform (void); CUniform (const CUniform&); CUniform (CUniform&&);

		TError& Error (void) const;

		uint32_t Locate (void) const;     // gets variable location (the index within shader context);
		bool     Locate (const uint32_t); // sets variable location; it is mainly used by uniform enumerator class; returns 'true' in case of value change;

		_pc_sz Name (void) const; // gets the name of this variable;
		bool   Name (_pc_sz);     // sets the name of this variable; returns 'true' in case of the name change;

		const
		CValue&  Value (void) const;
		CValue&  Value (void) ;

		CUniform& operator = (const CUniform&); CUniform& operator = (CUniform&&);
		CUniform& operator <<(_pc_sz _p_name);
		CUniform& operator <<(const CValue&);
		CUniform& operator <<(const uint32_t _u_ndx); // sets the location/index value;

		const
		TPipe& operator ()(void) const;
		TPipe& operator ()(void);

	private:
		CError   m_error;
		CString  m_name ; // this is variable name that is used inside of shader source code;
		CValue   m_value;
		uint32_t m_index; // aka location;
	};

	typedef ::std::vector<CUniform> TUniVars;

	class CUniform_enum : public TPipe {
	public:
		CUniform_enum (const e_object = e_object::e_none); ~CUniform_enum (void);
		static
		uint32_t Count (const e_object, CError&); // gets count of uniforms in the active/bound program object;
		uint32_t Count (void) const;              // gets active program reference from the global renderer;
		TError&  Error (void) const;
		static
		err_code Get (const e_object, TUniVars&, CError&); // enumerates all uniform variables;
	
	private:
		mutable
		CError  m_error;
	};

}
}}}

#endif/*_GL_UNIFORM_H_INCLUDED*/