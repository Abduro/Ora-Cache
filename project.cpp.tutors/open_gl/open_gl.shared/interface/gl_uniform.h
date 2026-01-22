#ifndef _GL_UNIFORM_H_INCLUDED
#define _GL_UNIFORM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Dec-2025 at 11:28:10.278, UTC+4, Batumi, Tuesday;
	This Ebo Pack OpenGL shader variable uniform data type wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_types.h"
#include "gl_procs_uniform.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace vars {

	using CType = procs::CType;
	using t_uniform_3f = procs::vars::t_uniform_3f;
	using t_uniform_4f = procs::vars::t_uniform_4f;

	static const uint32_t u_inv_loc  = (uint32_t)-1;
	static const uint32_t u_inv_prog = (uint32_t)-1;

	class CU_bas_0x0 : public TPipe {
	public:
		CU_bas_0x0 (const e_object = e_object::e_none); CU_bas_0x0 (const CU_bas_0x0&); CU_bas_0x0 (CU_bas_0x0&&); ~CU_bas_0x0 (void) = default;

		TError&  Error  (void) const;
		bool   Is_valid (void) const;     // validates the location/index value;
		uint32_t Locate (void) const;     // gets variable location (the index within shader source code);
		bool     Locate (const uint32_t); // sets variable location; it is mainly used by uniform enumerator class; returns 'true' in case of value change;

	public:
		CU_bas_0x0& operator = (const CU_bas_0x0&); CU_bas_0x0& operator = (CU_bas_0x0&&);
		CU_bas_0x0& operator <<(const uint32_t _u_locate);

	protected:
		mutable
		CError   m_error;
		uint32_t m_index; // aka location;
	};

	class CU_frm_0x0 : public CU_bas_0x0 { typedef CU_bas_0x0 TBase;
	public:
		CU_frm_0x0 (const e_object = e_object::e_none); CU_frm_0x0 (const CU_frm_0x0&); CU_frm_0x0 (CU_frm_0x0&&); ~CU_frm_0x0 (void) = default;

		bool Is_valid (void) const; // uses the 'Is_valid' of parent class for checking the variable location/index and checks variable name itself;

		_pc_sz   Name (void) const;   // gets the name of this variable;
		bool     Name (_pc_sz);       // sets the name of this variable; returns 'true' in case of the name change;
		err_code Query_name (void);   // gets name from shader code by specifying target draw type and variable location;

		CU_frm_0x0& operator = (const CU_frm_0x0&); CU_frm_0x0& operator = (CU_frm_0x0&&);
		CU_frm_0x0& operator <<(_pc_sz _p_name);
		CU_frm_0x0& operator <<(const CString& _cs_name);
	protected:
		CString m_name;
	};

	class CU_val_0x0 : public CU_bas_0x0 { typedef CU_bas_0x0 TBase;
	public:
		CU_val_0x0 (const e_object = e_object::e_none); CU_val_0x0 (const CU_val_0x0&); CU_val_0x0 (CU_val_0x0&&); ~CU_val_0x0 (void) = default;

		bool Is_valid (void) const; // uses 'Is_valid' of the parent class and checks the type value;

		const
		CType& Type (void) const;
		CType& Type (void) ;

		CU_val_0x0& operator <<(const CType&);
		CU_val_0x0& operator = (const CU_val_0x0&); CU_val_0x0& operator = (CU_val_0x0&&);
	protected:
		CType  m_type;
	};

	class CU_val_v3 : public CU_val_0x0 { typedef CU_val_0x0 TBase;
	public:
		CU_val_v3 (const e_object = e_object::e_none); CU_val_v3 (const CU_val_v3&); CU_val_v3 (CU_val_v3&&); ~CU_val_v3 (void) = default;
		const
		t_uniform_3f& Data (void) const;
		t_uniform_3f& Data (void) ;
		static
		err_code Get (const e_object, const uint32_t _locate, t_uniform_3f&, CError&);
		err_code Get (void) ; // gets the value of the uniform variable in accordance with its data type;

		CU_val_v3& operator = (const CU_val_v3&); CU_val_v3& operator = (CU_val_v3&&);
		CU_val_v3& operator <<(const t_uniform_3f&);

	private:
		t_uniform_3f m_data;
	};

	class CU_val_v4 : public CU_val_0x0 { typedef CU_val_0x0 TBase;
	public:
		CU_val_v4 (const e_object = e_object::e_none); CU_val_v4 (const CU_val_v4&); CU_val_v4 (CU_val_v4&&); ~CU_val_v4 (void) = default;
		const
		t_uniform_4f& Data (void) const;
		t_uniform_4f& Data (void) ;
		static
		err_code Get (const e_object, const uint32_t _locate, t_uniform_4f&, CError&);
		err_code Get (void) ; // gets the value of the uniform variable in accordance with its data type;

		CU_val_v4& operator = (const CU_val_v4&); CU_val_v4& operator = (CU_val_v4&&);
		CU_val_v4& operator <<(const t_uniform_4f&);

	private:
		t_uniform_4f m_data;
	};

	class CU_frm_v4 : public CU_frm_0x0 { typedef CU_frm_0x0 TBase;
	public:
		CU_frm_v4 (const e_object = e_object::e_none); CU_frm_v4 (const CU_frm_v4&); CU_frm_v4 (CU_frm_v4&&); ~CU_frm_v4 (void) = default;

		bool Locate (const uint32_t); // the base class 'Locate()' is overriden due to the value of this variable needs alsp 'to know' the location;

		const
		CU_val_v4&  Vec4 (void) const;
		CU_val_v4&  Vec4 (void) ;

		const
		CU_frm_0x0& operator ()(void) const;  // gets the reference to the base 'CU_frm_0x0' class; (ro)
		CU_frm_0x0& operator ()(void);        // gets the reference to the base 'CU_frm_0x0' class; (rw)

		CU_frm_v4&  operator = (const CU_frm_v4&);
		CU_frm_v4&  operator = (CU_frm_v4&&); // no swap is used yet;
		CU_frm_v4&  operator <<(const CU_val_v4&);

	private:
		CU_val_v4  m_vec4;
	};

	typedef ::std::vector<CU_frm_v4> TU_vars_v4;

	class CUniform_enum : public TPipe {
	public:
		CUniform_enum (const e_object = e_object::e_none); ~CUniform_enum (void);
		static
		uint32_t Count (const e_object, CError&); // gets count of uniforms in the active/bound program object;
		uint32_t Count (void) const;              // gets active program reference from the global renderer;
		TError&  Error (void) const;
		static
		err_code Get (const e_object, TU_vars_v4&, CError&); // enumerates all uniform variables;
	
	private:
		mutable
		CError  m_error;
	};

}
}}}

#endif/*_GL_UNIFORM_H_INCLUDED*/