#ifndef _GL_VERTEX_H_INCLUDED
#define _GL_VERTEX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Sep-2025 at 21:29:58.844, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' shader vertex base interface declaration file;
*/
#include "gl_defs.h"
#include "color._defs.h"

namespace ex_ui { namespace draw { namespace open_gl {

	// https://en.wikipedia.org/wiki/Vertex_(geometry) ;
	// https://en.wikipedia.org/wiki/Vertex_(computer_graphics) ;

	typedef ::std::vector<float>  TVertData; // perhaps 'TVertData' is better; (done);

namespace vertex {
#if (1)
	class CCoord : private no_copy {
	public:
		CCoord (const float _x = 0.0f, const float _y = 0.0f, const float _z = 0.0f); CCoord (const CCoord&); CCoord (CCoord&&); ~CCoord (void) = default;

		float X (void) const; void  X (const float); float& X (void);
		float Y (void) const; void  Y (const float); float& Y (void);
		float Z (void) const; void  Z (const float); float& Z (void);

	public:
		CCoord& operator = (const CCoord&);
		CCoord& operator = (CCoord&&); // neither 'swap' or 'move' operations due to there is no non-copyable handles; https://en.cppreference.com/w/cpp/algorithm/swap.html ; 
	private:
		float m_coord[3]; // 0:_x; 1:_y; 2:_z;
	};
#endif
	/* https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml ;
	   the CData class is the wrapper over parameters for calling the one of the functions glVertexAttrib*Pointer();
	*/
	class CData {
	private: CData (void) = delete; CData (const CData&) = delete; CData (CData&&) = delete;
	public : CData (TVertData&);   ~CData (void);

		static CString Class (void);

		uint32_t  Index (void) const;        // the index is set as attribute index (aka location) from source of the shader;
		bool      Index (const uint32_t);    // returns 'true' in case of attribute index value is changed;

		bool   Is_normalized (void) const;   // initial value of this flag is false and is set by default;
		bool   Is_normalized (const bool);   // returns 'true' in case of normalization flag value change;

		uint32_t  Offset (void) const;       // initial value of the offset is set by color and position classes and does not require any change;
		bool      Offset (const uint32_t);   // returns 'true' in case of offset value change; the value is set by color and position classes;
		uint32_t  Stride (void) const;       // it is set by default and does not require any change of stride value;
		bool      Stride (const uint32_t);   // returns 'true' in case of stride value change;
		uint32_t  Size   (void) const;       // specifies the number of components per generic vertex attribute; must be [1-4] or GL_BGRA;

	protected:
		CData& operator = (const CData&) = delete; CData& operator = (CData&&) = delete;
		
		TVertData& m_data ;
		uint32_t   m_index;
		bool       m_normal; // vertex value(s) normalization flag;
		uint32_t   m_offset;
		uint32_t   m_size;   // it would be better to name this variable and the related property to something similar to 'count', not 'size';
		uint32_t   m_stride; // it sets to sizeof(float) * m_data.size() by default and does not require any change;
	};
	// the color channels follow in the sequence: r-g-b-a => offset + ndx[0..3];
	class CColor : public CData {
	private: CColor (void) = delete; using CConvert = ex_ui::color::rgb::CConvert; // this class has static method for converting color channel to float value;
	public:
		CColor (TVertData&); ~CColor (void);

		void Set (const float _r, const float _g, const float _b, const float _a = 1.0f); // sets color as float value; if the value is out of range [0.0...1.0], the value is set to min or max value of the range;
		void Set (const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a = 0xff);
		void Set (const rgb_color);  // sets color in RGBA format; the input value is converted in float value color;
	};
	// https://learnopengl.com/Getting-started/Coordinate-Systems ;
	// the position coordinates value follow in the next sequence: x-y-z => offset + ndx[0..2];
	class CPosition : public CData { typedef CData TData;
	private: CPosition (void) = delete;
	public:
		CPosition (TVertData&); ~CPosition (void);

		void Set (const float _x, const float _y, const float _z = 0.0f); // sets coordinates in local/object 3D space;
		void Set (const long  _x, const long  _y/*const long  _z = 0*/ ); // converts screen space coordinates to local space; it requires viewport size;
	};
}
	class CVertex {
	using CClr = vertex::CColor;
	using CPos = vertex::CPosition;
	public:
		CVertex (void) ;  CVertex (const CVertex&) = delete; CVertex (CVertex&&) = delete; ~CVertex (void) ;

		TError& Error (void) const;

		const
		CClr&   Clr (void) const;
		CClr&   Clr (void) ;
		const
		CPos&   Pos (void) const;
		CPos&   Pos (void) ;
		const
		TVertData& Raw (void) const; // gives the read-only access to element of the vector;
		TVertData& Raw (void) ;      // gives the direct access to the vector of data; *important*: the size of the vector must remain the same;

		uint32_t   Size(void) const; // returns the required number of elements in vertex data; 'stride' is not acceptable in this case, because it returns an offset in number of elements multiplied by data type size;

	private:
		CVertex& operator = (const CVertex&) = delete; CVertex& operator = (CVertex&&) = delete;
		mutable
		CError    m_error;
		CClr      m_clr;
		CPos      m_pos;
		TVertData m_data;  // the container, i.e. this class, contains data that will be shared between several classes internal or external, but that classes will belong to this container;
	};

}}}

typedef ex_ui::draw::open_gl::vertex::CData TData;

#endif/*_GL_VERTEX_H_INCLUDED*/