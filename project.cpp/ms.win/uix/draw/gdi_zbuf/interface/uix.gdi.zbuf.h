#ifndef _UIX_GDI_ZBUF_H_INCLUDED
#define _UIX_GDI_ZBUF_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2020 at 4:35:03, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared draw library Z-buffer interface declaration file.
*/
#include "uix.gdi.defs.h"
#include "uix.gdi.zbuf.h"

namespace ex_ui { namespace draw { namespace memory {

	using namespace ex_ui::draw::defs;
	
	/*
		Trying to separate code or to make code more modular requires creating class(es)/structure(s) that share common data;
		otherwise, synch data/state problem arises;
	*/
	class CDrawArea {
	public:
		 CDrawArea (void); CDrawArea (const CDrawArea&) = delete; CDrawArea (CDrawArea&&) = delete;
		 CDrawArea (const t_rect&);
		~CDrawArea (void);

	public:
		const
		t_rect&  Get (void) const;
		t_rect&  Get (void) ;

		bool Is_empty(void) const;
		bool Set (const t_rect&);    // returns 'true' in case of change one of the points of the rectangle field;

	public:
		CDrawArea&  operator <<(const t_rect&);

	private:
		CDrawArea&  operator = (const CDrawArea&) = delete;
		CDrawArea&  operator = (CDrawArea&&) = delete;

	private:
		t_rect   m_rect;
	};

	class CCopier {
	public:
		 CCopier (void) = delete;
		 CCopier (const HDC& _h_mem_dc); CCopier (CCopier&&) = delete;
		~CCopier (void);

	public:
		const
		CDrawArea& DrawArea (void) const;
		CDrawArea& DrawArea (void) ;

		TError&  Error (void) const;
		bool  Is_valid (void) const;  // just validates the memory device context handle;

		err_code To (HBITMAP&) const; // makes a copy of a surface that is currently set in in-memory device context;
		err_code To (const HDC _h_comp_dc, const int32_t _x, const int32_t _y, const _byte _alpha = _Opaque);

	private:
		CCopier& operator = (const CCopier&) = delete;
		CCopier& operator = (CCopier&&) = delete;

	private:
		mutable
		CError     m_error;
		const HDC& m_mem_dc;
		CDrawArea  m_drw_area;
	};

	class CSurface { // this class is exactly for memory device context;
	public:
		 CSurface (void); CSurface (const CSurface&) = delete; CSurface (CSurface&&) = delete;
		~CSurface (void);

	public:
		err_code  ApplyTo(const HDC _h_mem_dc);  // applies the new bitmap of a surface to memory device;
		const
		t_rect&   Area (void) const;
		t_rect&   Area (void) ;

		err_code  Create (const HDC _h_origin, const t_rect& _rc_draw); // creates a new surface bitmat that is compatible to input device context;
		err_code  Destroy(void);

		TError&   Error(void) const;
		bool   Is_valid(void) const;

		const
		HBITMAP&  Prev (void) const;
		HBITMAP&  Prev (void) ;
		const
		HBITMAP&  New  (void) const;
		HBITMAP&  New  (void) ;

	private:
		CSurface& operator = (const CSurface&) = delete;
		CSurface& operator = (CSurface&&) = delete;

	private:
		mutable
		CError   m_error;
		HBITMAP  m_surface[2]; // 0|old surface; 1|new surface;
		t_rect   m_rc_draw;    // draw area of a surface; https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/crect-class ;
	};

#if(0)
	using ex_ui::draw::shape::CRectEdge;
	using ex_ui::draw::shape::CPosition;
	using ex_ui::draw::shape::CRounded ;

	using ex_ui::color::eAlphaValue;
	using ex_ui::color::CColour;
#endif
	//the CZBuffer is not inherited from ::WTL::CMemoryDC due to it makes public its fields, that is not necessary definitely;
	class CZBuffer : public ::WTL::CDC { typedef ::WTL::CDC TDC;
	public:
		 CZBuffer (void);
		 CZBuffer (const HDC _h_origin, const t_rect& _rc_draw);
		 CZBuffer (const CZBuffer&) = delete; CZBuffer (CZBuffer&&) = delete;
		~CZBuffer (void);

	public:
		const
		CCopier&  Copier(void) const;
		err_code  Create(const HDC _h_origin, const t_rect& _rc_draw);
		TError&   Error (void) const;

		bool   Is_valid (void) const;

		err_code  Reset (void) ; // copies the buffer content to original device context and resets the buffer to uninitialized state;
		const
		CSurface& Surface (void) const;
		CSurface& Surface (void) ;
#if (0)
	public: // drawing line(s);
		VOID     DrawLine( const CPosition&, const CColour& _clr, const INT nThickness = 1 ); // TODO: calculated rectangle is not correct; alpha of color is applied;
		VOID     DrawLine( const CPosition&, const COLORREF _clr, const INT nThickness = 1 );
		VOID     DrawLine( const INT _x0, const INT _y0, const INT _x1, const INT _y1 , const COLORREF _clr, const INT nThickness = 1 );
		VOID     DrawLine( const POINT& _start, const POINT& _end, const COLORREF _clr, const INT nThickness = 1 );
	public: // drawing rectangle(s);
		VOID     DrawRectangle(CONST CRounded&, CONST COLORREF _borders, CONST COLORREF _fill) CONST; // GDI+, color is used if no CLR_NONE;
			// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-gradientfill
		VOID     DrawRectangle( const RECT&, const COLORREF _from, const COLORREF _upto,  const bool _b_vert, const BYTE _alpha ) CONST;
		VOID     DrawRectangle( const RECT&, const COLORREF _border, const INT  nThickness = 1, const DWORD dEdges = CRectEdge::eAll );
		VOID     DrawSolidRect( const RECT&, const CColour& ) CONST;
		VOID     DrawSolidRect( const RECT&, const COLORREF clrFill, const BYTE _alpha = eAlphaValue::eOpaque  ) CONST;
	public: // drawing text;
		VOID     DrawTextExt( LPCTSTR pszText, const HFONT fnt_, const RECT& rcDraw, const COLORREF clrFore, const DWORD fmt_ ); // standard/classic GDI;
		VOID     DrawTextExt( LPCTSTR pszText, LPCTSTR pszFontFamily, const DWORD dwFontSize, const RECT& rcDraw, const COLORREF clrFore, const DWORD dwFormat ); // GDI+
		
	public:
		operator HDC     (void) const { return TBaseDC::m_hDC; }
		operator HBITMAP (void) const { return this->m_surface.m_hBitmap; }
#endif
	public:
		static bool Is_DC (const HDC); // returns true if an input handle has proper data type such as: OBJ_DC|OBJ_MEMDC;
		static bool Is_DC_mem (const HDC); // returns true if an input handle has proper data type is OBJ_MEMDC;

	private:
		CZBuffer& operator = (const CZBuffer&) = delete;
		CZBuffer& operator = (CZBuffer&&) = delete;

	private:
		CCopier  m_copier;
		CError   m_error ;
		HDC      m_origin;
		CSurface m_surface;
	};
}}}
#if (0)
typedef ex_ui::draw::CZBuffer  TZBuffer;
#endif
#endif/*_UIX_GDI_ZBUF_H_INCLUDED*/