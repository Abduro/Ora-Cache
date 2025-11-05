#ifndef _GL_VERTEX_ATTR_H_INCLUDED
#define _GL_VERTEX_ATTR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Nov-2025 at 19:41:10.221, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' vertex attributes' wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "program\gl_prog_id.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace vertex {

	class CAttr {
	using CProgId = program::CProgId;
	public: // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttribLocation.xhtml ;
		class CIndex {
		private: CIndex (const CIndex&&) = delete; CIndex (CIndex&&) = delete; CIndex (void) = delete;
		public:
			static const int32_t _$na = -1;

			CIndex (const CAttr& _attr_ref);  ~CIndex (void);

			TError&  Error (void) const;
			static
			int32_t  Get (const uint32_t _prog_id, _pc_sz _p_att_name, CError&); // returns attribute variable index that is bound the name, -1 in case of error;
			int32_t  Get (void) const;  // calls the above static function by providing the attr name that is set to this class object; *after* linking the program;
			static
			err_code Set (const uint32_t _prog_id, _pc_sz _p_att_name, const uint32_t _u_ndx, CError&); // sets the index to the vertex attr variable;
			err_code Set (const uint32_t _u_ndx); // sets the index by using attr values; *before* the linking operation, otherwise there is no apply;

			int32_t  Value (void) const; // returns the current value of this index;
			int32_t  operator ()(void) const;

		private:
			CIndex& operator = (const CIndex&) = delete; CIndex& operator = (CIndex&&) = delete;
			const   CAttr&  m_attr_ref;
			mutable CError  m_error;
			mutable int32_t m_value;  // this is the value of the index that is set by Get() or Set() methods in case of success, -1 by default;
		};
	public:
		CAttr (_pc_sz _p_name = 0); CAttr (const CAttr&) = delete; CAttr (CAttr&&) = delete; ~CAttr (void);

		TError&  Error (void) const;
		bool  Is_valid (void) const;  // returns 'true' if the name of this attrebute is set;

		const
		CIndex&  Index (void) const;  // gets the attr index reference; (ro)
		CIndex&  Index (void) ;       // gets the attr index reference; (rw)

		_pc_sz   Name  (void) const;
		err_code Name  (_pc_sz) ;     // returns __s_ok in case of change; __s_false - no change, otherwise error code;

		const
		CProgId& ProgId (void) const;
		CProgId& ProgId (void) ;

		CAttr& operator <<(_pc_sz _p_name);
		CAttr& operator <<(const CProgId&);
	private:
		CAttr& operator = (const CAttr&) = delete; CAttr& operator = (CAttr&&) = delete;
		mutable
		CError  m_error;
		CString m_name ;
		CIndex  m_index;
		CProgId m_prog_id;
	};

	class CAttrs {
	private: CAttrs (const CAttrs&) = delete; CAttrs (CAttrs&&) = delete; using CProgId = program::CProgId;
	public:
		CAttrs (void); ~CAttrs (void);

		err_code Bind (void);        // binds program's attributes with its declaration in shaper's source code; can be called *before* linking;
		err_code Bound(void);        // returns indices of the attributes *after* linking the program;

		const
		CAttr&   Clr (void) const;   // playing with property names;
		CAttr&   Clr (void) ;
		const
		CAttr&   Color (void) const;
		CAttr&   Color (void) ;

		TError&  Error (void) const;
		bool  Is_valid (void) const; // checks each attribute for its validity;
		const
		CAttr&   Pos (void) const;   // playing with property names;
		CAttr&   Pos (void) ;
		const
		CAttr&   Position (void) const;
		CAttr&   Position (void) ;
		const
		CProgId& ProgId (void) const;
		err_code ProgId (const uint32_t) ; // this method updates the program identifiers of all attributes;

		CAttrs& operator <<(const CProgId&);
		CAttrs& operator <<(const uint32_t _prog_id);

	private: CAttrs& operator = (const CAttrs&) = delete; CAttrs& operator = (CAttrs&&) = delete;
		mutable
		CError  m_error;
		CAttr   m_clr;
		CAttr   m_pos;
		CProgId m_prog_id;
	};
}}}}

#endif/*_GL_VERTEX_ATTR_H_INCLUDED*/