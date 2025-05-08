#ifndef _UIX_GDI_ZBUF_H_INCLUDED
#define _UIX_GDI_ZBUF_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2020 at 4:35:03, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared draw library Z-buffer interface declaration file.
*/
#include "uix.gdi.defs.h"
#if(0)
#include "uix.gdi.shape.h"
#include "color.alpha.h"
#include "color.generic.h"
#endif
namespace ex_ui { namespace draw { namespace memory {

	using namespace shared::types;
	using CError = shared::sys_core::CError;
	using TError = const CError;

	class CSurface {
	public:
		 CSurface (void); CSurface (const CSurface&) = delete; CSurface (CSurface&&) = delete;
		~CSurface (void);

	public:
		const
		t_rect&   Area (void) const;
		t_rect&   Area (void) ;

		err_code  Create (const HDC hDC, const t_rect& _rc_draw); // creates a new surface bitmat that is compatible to input device context;

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
		HBITMAP  m_surface[2]; // 0|old surface; 1|new surface;
		t_rect   m_rc_draw;    // draw area of a surface;
		CError   m_error;
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
		err_code  Create(const HDC _h_origin, const t_rect& _rc_draw);
		TError&   Error (void) const;

		bool   Is_valid (void) const;

		void      Reset (void) ; // copies the buffer content to original device and resets the buffer to uninitialized state;
#if (0)
	public:
		HRESULT  CopyTo(HBITMAP& hBitmap);
		HRESULT  CopyTo(CONST HDC hCompatibleDC, const INT _x, const INT _y, const BYTE _alpha = eAlphaValue::eOpaque );
		
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
		const
		RECT&    GetDrawRect (void) const;
		bool     IsValid     (void) const;
		
	public:
		operator HDC     (void) const { return TBaseDC::m_hDC; }
		operator HBITMAP (void) const { return this->m_surface.m_hBitmap; }

	public:
		static const bool Is (const HDC); // returns true if a handle provided has proper type value;
#endif
	private:
		CZBuffer& operator = (const CZBuffer&) = delete;
		CZBuffer& operator = (CZBuffer&&) = delete;

	private:
		HDC      m_origin;
		CSurface m_surface;
		CError   m_error;
	};
}}}
#if (0)
typedef ex_ui::draw::CZBuffer  TZBuffer;
#endif
#endif/*_UIX_GDI_ZBUF_H_INCLUDED*/