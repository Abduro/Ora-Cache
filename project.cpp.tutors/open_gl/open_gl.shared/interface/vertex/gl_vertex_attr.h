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
		public:
			static const int32_t _$na = -1;

			CIndex (const CAttr* _p_attr = nullptr); ~CIndex (void); CIndex (const CIndex&);  CIndex (CIndex&&);

			TError&  Error (void) const;
			static
			int32_t  Get (const uint32_t _prog_id, _pc_sz _p_att_name, CError&); // returns attribute variable index that is bound the name, -1 in case of error;
			int32_t  Get (void) const; // calls the above static function by providing the attr name that is set to this class object; *after* linking the program;
			static
			err_code Set (const uint32_t _prog_id, _pc_sz _p_att_name, const uint32_t _u_ndx, CError&); // sets the index to the vertex attr variable;
			err_code Set (const uint32_t _u_ndx); // sets the index by using attr values; *before* the linking operation, otherwise there is no apply;

			int32_t  Value (void) const;     // returns the current value of this index;
			bool     Value (const uint32_t); // sets the index value; returns 'true' in case of change its value;

			bool  Is_valid (void) const;     // checks attribute pointer for nullptr and the index value;

			int32_t  operator ()(void) const;

			CIndex& operator = (const CIndex&); CIndex& operator = (CIndex&&); // no move operation is used;
			CIndex& operator <<(const CAttr* );
			CIndex& operator <<(const int32_t _n_value); // 'signed' integer data type is kept here for copying operation for cases when value is not set yet;

		private:
			const   CAttr*  m_attr_ptr;
			mutable CError  m_error;
			mutable int32_t m_value;  // this is the value of the index that is set by Get() or Set() methods in case of success, -1 by default;
		};
	public:
		CAttr (_pc_sz _p_name = 0); CAttr (const CAttr&); CAttr (CAttr&&); ~CAttr (void);

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
	public:
		CAttr& operator = (const CAttr&); CAttr& operator = (CAttr&&);
	private:
		mutable
		CError  m_error;
		CString m_name ;
		CIndex  m_index;
		CProgId m_prog_id;
	};

	typedef ::std::vector<CAttr> TRawAttrs;
	// attribute array class consists of attributes which compose the vertex in position and color;
	class CAttrArray {
	using CProgId = program::CProgId;
	public:
		CAttrArray (void); ~CAttrArray (void); CAttrArray (const CAttrArray&); CAttrArray (CAttrArray&&);

		err_code Bind (void);        // binds program's attributes with its declaration in shaper's source code; can be called *before* linking;
		err_code Is_bound(void);     // returns indices of the attributes *after* linking the program;

		const
		CAttr&   Clr (void) const;   // playing with property names;
		CAttr&   Clr (void) ;

		err_code Enum_attrs (void) ; // enumerates all attributes that are linked to the program;

		TError&  Error (void) const;
		bool  Is_valid (void) const; // checks each attribute for its validity;
		const
		CAttr&   Pos (void) const;   // playing with property names;
		CAttr&   Pos (void) ;
		
		const
		CProgId& ProgId (void) const;
		err_code ProgId (const uint32_t); // this method updates the program identifiers of all attributes;

		CAttrArray& operator = (const CAttrArray&); CAttrArray& operator = (CAttrArray&&);
		CAttrArray& operator <<(const CProgId&);
		CAttrArray& operator <<(const uint32_t _prog_id);
		CAttrArray& operator >>(const CAttr& _clr);
		CAttrArray& operator <<(const CAttr& _pos);

	private:
		mutable
		CError  m_error;
		CAttr   m_clr;
		CAttr   m_pos;
		CProgId m_prog_id;
		TRawAttrs m_attrs;
	};

	class CVertex : public CAttrArray { typedef CAttrArray TBase;
	};
}}}}

#endif/*_GL_VERTEX_ATTR_H_INCLUDED*/