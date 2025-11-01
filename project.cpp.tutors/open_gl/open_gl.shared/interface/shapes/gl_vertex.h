#ifndef _GL_VERTEX_H_INCLUDED
#define _GL_VERTEX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Sep-2025 at 21:29:58.844, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' shader vertex base interface declaration file;
*/
#include "gl_defs.h"
#include "color.rgb.h"

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
	// https://stackoverflow.com/questions/11821336/what-are-vertex-array-objects ;
	class CArray {
	public:
		CArray (void); CArray (const CArray&) = delete; CArray (CArray&&) = delete; ~CArray (void);

		err_code Bind   (void); // perhaps it would be better to replace word 'bind' by 'activate' or 'current';
		bool  Is_bound  (void) const;
		err_code Create (void);
		err_code Delete (void);
		TError&  Error  (void) const;
		uint32_t GetId  (void) const;
		err_code Unbind (void);

	private:
		CArray& operator = (const CArray&) = delete; CArray& operator = (CArray&&) = delete;
		mutable
		CError   m_error;
		uint32_t m_arr_id;
	};

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

	class CColor : public CData, public ex_ui::color::rgb::CFloat {
	using CFltClr = ex_ui::color::rgb::CFloat;
	private: CColor (void) = delete;
	public:
		CColor (TVertData&); ~CColor (void);
	};
	// https://learnopengl.com/Getting-started/Coordinate-Systems ;
	class CPosition : public CData { typedef CData TData;
	private: CPosition (void) = delete;
	public:
		CPosition (TVertData&); ~CPosition (void);

		void Set (const float _x, const float _y, const float _z = 0.0f); // sets coordinates in local/object 3D space;
		void Set (const long  _x, const long  _y/*const long  _z = 0*/ ); // converts screen space coordinates to local space;
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