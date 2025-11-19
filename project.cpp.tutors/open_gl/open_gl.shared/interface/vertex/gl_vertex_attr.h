#ifndef _GL_VERTEX_ATTR_H_INCLUDED
#define _GL_VERTEX_ATTR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Nov-2025 at 19:41:10.221, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' vertex attributes' wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "program\gl_prog_id.h"
#include "color._defs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace vertex {
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttribLocation.xhtml ;
	class CAttr_Location {
	using CProgId = program::CProgId;
	public:
		static const int32_t _$na = -1;
		CAttr_Location (void); ~CAttr_Location (void); CAttr_Location (const CAttr_Location&);  CAttr_Location (CAttr_Location&&);

		_pc_sz  Attr_name (void) const; // returns currently set attribute name;
		bool    Attr_name (_pc_sz);     // returns 'true' in case of attribute name change;

		TError& Error (void) const;
		bool Is_valid (void) const;     // returns 'true' if this location value is set;

		static
		int32_t  Get (const uint32_t _prog_id, _pc_sz _p_att_name, CError&); // returns attribute variable index that is bound the name, _$na (-1) 7in case of error;
		int32_t  Get (void) const;      // calls the above static function by providing the attr name that is set to this class object; *after* linking the program;
		static
		err_code Set (const uint32_t _prog_id, _pc_sz _p_att_name, const uint32_t _u_ndx, CError&); // sets the index to the vertex attr variable;
		err_code Set (const uint32_t _u_ndx); // sets the index by using attr values; *before* the linking operation, otherwise there is no apply;
		const
		CProgId& ProgId (void) const;
		CProgId& ProgId (void) ;

		int32_t  Value (void) const;     // returns the current value of this attribute location/index;
		bool     Value (const uint32_t); // sets the index value; returns 'true' in case of change its value;

	public:
		CAttr_Location& operator = (const CAttr_Location&); CAttr_Location& operator = (CAttr_Location&&); // no move operation, just copying data;
		CAttr_Location& operator <<(const CProgId&);
		CAttr_Location& operator <<(const int32_t _n_value);
		CAttr_Location& operator <<(_pc_sz _attr_name);

	private:
		mutable CError  m_error;
		mutable int32_t m_value;    // this is the value of the index that is set by Get() or Set() methods in case of success, -1 by default;
		CString m_attr_name;
		CProgId m_prog_id;
	};
}}}}

typedef ex_ui::draw::open_gl::vertex::CAttr_Location TLocation;
typedef ::std::vector<float>  TAttrData;

namespace ex_ui { namespace draw { namespace open_gl { namespace vertex {
	class CAttr {
	using CProgId = program::CProgId;
	using CLocate = TLocation;
	public:
		CAttr (_pc_sz _p_name = 0); CAttr (const CAttr&); CAttr (CAttr&&); ~CAttr (void);

		const
		TAttrData&  Data (void) const;    // gets the reference to attribute data vector; (ro)

		TError&  Error (void) const;
		bool  Is_valid (void) const;      // returns 'true' if the name of this attrebute is set;

		const
		TLocation&  Locate (void) const;  // gets the attr index (aka location) reference; (ro)
		TLocation&  Locate (void) ;       // gets the attr index (aka location) reference; (rw)

		_pc_sz    Name  (void) const;
		err_code  Name  (_pc_sz) ;        // returns __s_ok in case of change; __s_false - no change, otherwise error code;
		// https://www.allacronyms.com/NORM/normalized ;
		bool   Is_normal(void) const;     // returns flag of requirement to normalize attribute values;
		bool   Is_normal(const bool);     // sets the value of the normalization flag; by default is set to 'false'; returns 'true' if flag value changed;

		uint32_t  Offset (void) const;    // initial value of the offset is set by color and position classes and does not require any change;
		const
		CProgId&  ProgId (void) const;
		err_code  ProgId (const uint32_t);

		uint32_t  Size  (void) const;     // specifies the number of components per generic vertex attribute; must be [1-4] or GL_BGRA;
		uint32_t  Type  (void) const;     // returns data type of this attribute, e.g. GL_FLOAT, GL_UNSIGNED_INT, etc.; by default is GL_FLOAT;

		uint32_t  Stride(void) const;     // it is set by default and does *not* require any change of stride value; must be set by child class;

		CAttr& operator <<(_pc_sz _p_name);
		CAttr& operator <<(const CProgId&);
		CAttr& operator <<(const bool _b_norm);
		CAttr& operator = (const CAttr&); CAttr& operator = (CAttr&&); // no move operation, just copying data;
	protected:
		CAttr& operator <<(const CLocate&);
		CAttr& operator <<(const uint32_t _u_size);
		CAttr& operator >>(const uint32_t _u_type);
		
	protected:
		mutable
		CError    m_error;
		CLocate   m_index;
		CString   m_name ;
		bool      m_norm ;   // the value of the normalization required to convert this attribute value(s);
		CProgId   m_prog_id;
		uint32_t  m_size ;   // it would be better to name this variable and the related property to something similar to 'count', not 'size';
		uint32_t  m_type ;
		uint32_t  m_offset;
		uint32_t  m_stride;  // it is set to sizeof(this->Type()) * this->Size() by default and does not require any change;
		TAttrData m_data ;   // this is data of attribute settings; 
	};
	// the color channels follow in the sequence: r-g-b-a => offset + ndx[0..3];
	class CColor : public CAttr { typedef CAttr TBase;
	public:
		CColor (void); CColor (const CColor&); CColor (CColor&&); ~CColor (void) = default;

		CColor& operator = (const CColor&);
		CColor& operator = (CColor&&);          // no move operation, just copying data;

		// sets color as float value; if the value is out of range [0.0...1.0], the value is set to min or max value of the range;
		void Set (const float _r, const float _g, const float _b, const float _a = 1.0f);
		void Set (const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a = 0xff);
		void Set (const rgb_color);  // sets color in RGBA format; the input value is converted to float value color;

		static const uint32_t Channels (void);  // returns default size/count of the components: r|g|b|a = 4;
		static const uint32_t Type (void);      // default data type is 'float';
		static const uint32_t Stride (void);    // default stride value = this::Channels() * sizeof(this::Type());

	private:
	};
	// https://learnopengl.com/Getting-started/Coordinate-Systems ;
	// the position coordinates value follow in the next sequence: x-y-z => offset + ndx[0..2];
	class CPosition : public CAttr { typedef CAttr TBase;
	public:
		CPosition (void); CPosition (const CPosition&); CPosition (CPosition&&); ~CPosition (void) = default;

		CPosition& operator = (const CPosition&);
		CPosition& operator = (CPosition&&);    // no move operation, just copying data;

		void Set (const float _x, const float _y, const float _z = 0.0f); // sets coordinates in local/object 3D space;
		void Set (const long  _x, const long  _y/*const long  _z = 0*/ ); // converts screen space coordinates to local space; it requires viewport size;

		static const uint32_t Points (void);    // returns default size/count of the points: x|y|z = 3;
		static const uint32_t Type (void);      // default data type is 'float';
		static const uint32_t Stride (void);    // default stride value = this::Points() * sizeof(this::Type());

	private:
	};
	// attribute array class consists of attributes which compose the vertex in position and color;
	class CAttrArray {
	using CClr = CColor;
	using CPos = CPosition;
	using CProgId = program::CProgId;
	public:
		CAttrArray (void); ~CAttrArray (void); CAttrArray (const CAttrArray&); CAttrArray (CAttrArray&&);

		err_code Bind (void);        // binds program's attributes with its declaration in shaper's source code; can be called *before* linking;
		err_code Is_bound(void);     // returns indices of the attributes *after* linking the program;

		const
		CColor&  Clr (void) const;   // playing with property names;
		CColor&  Clr (void) ;

		err_code Enum_attrs (void) ; // enumerates all attributes that are linked to the program;

		TError&  Error (void) const;
		bool  Is_valid (void) const; // checks each attribute for its validity;
		const
		CPosition& Pos (void) const; // playing with property names;
		CPosition& Pos (void) ;
		
		const
		CProgId& ProgId (void) const;
		err_code ProgId (const uint32_t); // this method updates the program identifiers of all attributes;

		uint32_t Size (void) const;  // returns the number of elements of all attributes in this array;

		CAttrArray& operator = (const CAttrArray&); CAttrArray& operator = (CAttrArray&&); // no move operation, just copying data;
		CAttrArray& operator <<(const CProgId&);
		CAttrArray& operator <<(const uint32_t _prog_id);
		CAttrArray& operator <<(const CColor&);
		CAttrArray& operator <<(const CPosition&);

	private:
		mutable
		CError  m_error;
		CColor  m_clr;
		CPos    m_pos;
		CProgId m_prog_id;
	};
}}}}

#endif/*_GL_VERTEX_ATTR_H_INCLUDED*/