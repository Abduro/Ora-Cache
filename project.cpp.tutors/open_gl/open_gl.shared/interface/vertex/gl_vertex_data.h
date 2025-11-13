#ifndef _GL_VERTEX_DATA_H_INCLUDED
#define _GL_VERTEX_DATA_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Sep-2025 at 21:29:58.844, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' vertex data base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_vertex_attr.h"

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
	/* https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml ; */
}
	// https://wikis.khronos.org/opengl/Vertex_Specification ;
	class CVertex {
	using CAttrArray = vertex::CAttrArray;
	public:
		CVertex (void); CVertex (const CVertex&); CVertex (CVertex&&); ~CVertex (void) ;

		const
		CAttrArray& Attrs (void) const;
		CAttrArray& Attrs (void) ;
		TError&     Error (void) const;
		const
		TVertData&  Raw (void) const;     // gives the read-only access to element of the vector;
		TVertData&  Raw (void) ;          // gives the direct access to the vector of data; *important*: the size of the vector must remain the same;

		uint32_t    Size (void) const;    // returns the required number of elements in vertex data;
		err_code    Update (void) ;       // updates vertex data array by applying attributes' value;

		CVertex& operator = (const CVertex&); CVertex& operator = (CVertex&&);

	private:
		mutable
		CError      m_error;
		CAttrArray  m_attrs;
		TVertData   m_data ;
	};

}}}

#endif/*_GL_VERTEX_DATA_H_INCLUDED*/