#ifndef _UIX_GDI_SHADE_H_INCLUDED
#define _UIX_GDI_SHADE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 23:46:31.484, UTC+4, Batumi, Saturday;
	This is Ebo Pack GDI gradient of shading functionality wrapper interface declaration file;
*/
#include "uix.gdi.defs.h"

namespace ex_ui { namespace draw { namespace shade {

	// https://en.wikipedia.org/wiki/List_of_mathematical_abbreviations   ;
	// https://learn.microsoft.com/en-us/windows/win32/gdi/smooth-shading ;

	using namespace ex_ui::draw::defs;
	
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-gradient_rect ;
	// https://learn.microsoft.com/en-us/windows/win32/gdi/drawing-a-shaded-rectangle << sample;

	typedef GRADIENT_RECT TRectMesh;
	typedef ::std::vector<TRectMesh> TRectMeshes;  // this is a set of raw meshes for filling by gradient;

	class CRectMesh {
	public:
		 CRectMesh (const uint32_t _left_top = 0, const uint32_t _right_bottom = 0);
		 CRectMesh (const CRectMesh&);
		 CRectMesh (const TRectMesh&);
		 CRectMesh (CRectMesh&&) = delete;
		~CRectMesh (void);

	public:
		uint32_t   LeftTop (void) const;
		bool       LeftTop (const uint32_t);
		uint32_t   RightBottom (void) const;
		bool       RightBottom (const uint32_t);

#if defined (_DEBUG)
		CString    Print (const e_print = e_print::e_all) const;
#endif
		const
		TRectMesh& Raw (void) const;
		TRectMesh& Raw (void) ;

		bool Set (const uint32_t _n_left_top, const uint32_t _n_right_bottom); // returns 'true' in case when one of the index values is changed;
		bool Set (const TRectMesh&);

	public:
		CRectMesh& operator = (const CRectMesh&);
		CRectMesh& operator = (CRectMesh&&) = delete;
		CRectMesh& operator <<(const TRectMesh&);
		CRectMesh& operator <<(const uint32_t _n_left_top);
		CRectMesh& operator >>(const uint32_t _n_right_bottom);

		operator const TRectMesh& (void) const;
		operator       TRectMesh& (void) ;

	private:
		TRectMesh  m_mesh;
	};

	typedef ::std::vector<CRectMesh> TRectMeshSet;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-gradient_triangle ;
	// https://learn.microsoft.com/en-us/windows/win32/gdi/drawing-a-shaded-triangle << sample;

	// https://www.allacronyms.com/triangle/abbreviated ;

	typedef GRADIENT_TRIANGLE TTriMesh;
	typedef ::std::vector<TTriMesh> TTriMeshes; // this is a set of raw meshes for filling by gradient;
	
	class CTriMesh {
	public:
		enum e_corner : uint32_t {
		     e_vert_a = 0, // a vertex of corner 'A';
		     e_vert_b = 1, // a vertex of corner 'B'; 
		     e_vert_c = 2, // a vertex of corner 'C';
		};

	public:
		 CTriMesh (void);
		 CTriMesh (const CTriMesh&); CTriMesh (CTriMesh&&) = delete;
		 CTriMesh (const TTriMesh&);
		~CTriMesh (void);

	public:
		uint32_t   Index (const e_corner) const;                    // if input argument value is out of range, the first one value is returned;
		const bool Index (const e_corner, const uint32_t _n_value); // returns 'true' in case of index value is changed;
#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all) const;
#endif
		const
		TTriMesh&  Raw (void) const;
		TTriMesh&  Raw (void) ;

	public:
		CTriMesh&  operator = (const CTriMesh&);
		CTriMesh&  operator = (CTriMesh&&) = delete;
		CTriMesh&  operator <<(const TTriMesh&);

	private:
		TTriMesh   m_mesh;
	};

	typedef ::std::vector<CTriMesh> TTriMeshSet;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-trivertex ;
	typedef TRIVERTEX TVertex;
	typedef ::std::vector<TVertex> TVertices;  // this vector composes a set of vertices for input to draw function;

	// this is a vertex structure wrapper class;
	class CVertex {
	public:
		 CVertex (void); CVertex (const CVertex&); CVertex (CVertex&&) = delete;
		~CVertex (void);

	public:
		TRgbQuad  Clr (void) const;
		bool      Clr (const TRgbQuad&); // returns 'true' in case of one of the color channel values is changed;
		const
		t_point   Point (void) const;
		bool      Point (const int32_t _x, const int32_t _y); // returns 'true' in case when anchor point is changed;
		bool      Point (const t_point&);
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		TVertex&  Raw (void) const;
		TVertex&  Raw (void) ;

	public:
		CVertex&  operator <<(const t_point&);
		CVertex&  operator <<(const TVertex&);

		operator const TVertex& (void) const;
		operator       TVertex& (void) ;

	public:
		CVertex&  operator = (const CVertex&);
		CVertex&  operator = (CVertex&&) = delete;

	private:
		TVertex m_vertex;
	};

	typedef ::std::vector<CVertex> TVertexSet;

	class CRectShader {
	public:
		enum e_mode : uint32_t {
		e_horz = GRADIENT_FILL_RECT_H,
		e_vert = GRADIENT_FILL_RECT_V,
		};
	public:
		 CRectShader (void); CRectShader (const CRectShader&) = delete; CRectShader (CRectShader&&) = delete;
		~CRectShader (void);

	public:
		const
		TRectMeshSet& Meshes (void) const;
		TRectMeshSet& Meshes (void) ;

		e_mode Mode (void) const;
		bool   Mode (const e_mode);  // returns 'true' in case of mode change;

		TRectMeshes   RawMeshes (void) const;
		TVertices     RawVertices (void) const;

		const
		TVertexSet&   Vertices (void) const;
		TVertexSet&   Vertices (void) ;

	private:
		CRectShader&  operator = (const CRectShader&) = delete;
		CRectShader&  operator = (CRectShader&&) = delete;

	private:
		TRectMeshSet  m_meshes;
		TVertexSet    m_vertices;
		e_mode m_mode;
	};
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-gradientfill ;

	class CRenderer {
	public:
		 CRenderer (void); CRenderer (const CRenderer&) = delete; CRenderer (CRenderer&&) = delete;
		~CRenderer (void);

	public:
		TError&  Error(void) const;
		err_code Draw (const HDC, const CRectShader&);

	private:
		CRenderer&  operator = (const CRenderer&) = delete;
		CRenderer&  operator = (CRenderer&&) = delete;

	private:
		mutable
		CError m_error;
	};
}}}

#endif/*_UIX_GDI_SHADE_H_INCLUDED*/