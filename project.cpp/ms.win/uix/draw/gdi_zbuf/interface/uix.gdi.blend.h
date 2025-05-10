#ifndef _UIX_GDI_BLEND_H_INCLUDED
#define _UIX_GDI_BLEND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 09:58:01.060, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI blend function wrapper interface declaration file;
*/
#include "uix.gdi.defs.h"

namespace ex_ui { namespace draw { namespace blend {

	using namespace ex_ui::draw::defs;
	// https://learn.microsoft.com/en-us/windows/win32/gdi/smooth-shading;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-trivertex ;
	typedef TRIVERTEX TVertex;
	typedef ::std::vector<TVertex> TVertexSet;

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

	// https://en.wikipedia.org/wiki/List_of_mathematical_abbreviations ;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-gradient_rect ;
	// https://learn.microsoft.com/en-us/windows/win32/gdi/drawing-a-shaded-rectangle << sample;

	typedef GRADIENT_RECT TRectGrad;
	// this class is for linear gradient of the shaded rectangle in two possible directions: horizontal or vertical;
	class CRectGrad {
	public:
		 CRectGrad (void); CRectGrad (const CRectGrad&) = delete; CRectGrad (CRectGrad&&) = delete;
		~CRectGrad (void);

	public:
		const
		TRectGrad& Indices (void) const;
		TRectGrad& Indices (void) ;
		const bool Is_valid(void) const; // the points of two vertices must create not empty rectangle area;
		const
		CVertex&   LeftTop (void) const;
		CVertex&   LeftTop (void) ;
		const
		CVertex&   RightBottom (void) const;
		CVertex&   RightBottom (void) ;
#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	public:
		CRectGrad& operator <<(const CVertex&); // sets the left-top vertex object;
		CRectGrad& operator >>(const CVertex&); // sets the right-bottom vertex object;

	private:
		CRectGrad& operator = (const CRectGrad&) = delete;
		CRectGrad& operator = (CRectGrad&&) = delete;

	private:
		TRectGrad m_indices;     // these are the vertex indexes that indicate how the colors are positioned to fill the gradient;
		CVertex   m_vertices[2]; // 0-left-top;1-right-bottom; this is by default, but gradient colors may be mixed by the indices;
	};
	
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-gradient_triangle ;
	// https://learn.microsoft.com/en-us/windows/win32/gdi/drawing-a-shaded-triangle << sample;
	typedef GRADIENT_TRIANGLE TTriGrad;

	class CTriaGrad {
	public:
		 CTriaGrad (void); CTriaGrad (const CTriaGrad&) = delete; CTriaGrad (CTriaGrad&&);
		~CTriaGrad (void);

	public:
		const
		TTriGrad&  Indices (void) const;
		TTriGrad&  Indices (void) ;
		const bool Is_valid(void) const; // all points of triangle vertices must be placed in different coordinates; ToDo: must be fixed!

		const
		CVertex&   Get_A (void) const;
		CVertex&   Get_A (void) ;
		const
		CVertex&   Get_B (void) const;
		CVertex&   Get_B (void) ;
		const
		CVertex&   Get_C (void) const;
		CVertex&   Get_C (void) ;
#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif

	private:
		CTriaGrad&  operator = (const CTriaGrad&) = delete;
		CTriaGrad&  operator = (CTriaGrad&&) = delete;

	private:
		TTriGrad m_indices;
		CVertex  m_vertices[3]; // 0 - 'A' vertex, 1 - 'B' vertex, 2 - 'C' vertex;
	};

	class CRenderer {
	public:
		 CRenderer (void); CRenderer (const CRenderer&) = delete; CRenderer (CRenderer&&) = delete;
		~CRenderer (void);

	public:
		TError&  Error (void) const;

	private:
		CRenderer&  operator = (const CRenderer&) = delete;
		CRenderer&  operator = (CRenderer&&) = delete;

	private:
		CError m_error;
	};

}}}


#endif/*_UIX_GDI_BLEND_H_INCLUDED*/