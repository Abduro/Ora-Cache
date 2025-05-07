#ifndef _SHAREDUIXGDIZ_BUF_H_INCLUDED
#define _SHAREDUIXGDIZ_BUF_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2020 at 4:35:03, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared draw library Z-buffer interface declaration file.
*/
#if(0)
#include "uix.gdi.defs.h"
#include "uix.gdi.shape.h"
#include "color.alpha.h"
#include "color.generic.h"

namespace ex_ui { namespace draw {

	using ex_ui::draw::shape::CRectEdge;
	using ex_ui::draw::shape::CPosition;
	using ex_ui::draw::shape::CRounded ;

	using ex_ui::color::eAlphaValue;
	using ex_ui::color::CColour;

	class CZBuffer : public ::WTL::CDC { typedef ::WTL::CDC TBaseDC;
	private:
		HDC      m_hOrigin;
		RECT     m_rcPaint;
		CBitmap  m_surface;
		HBITMAP  m_hBmpOld;

	public:
		 CZBuffer(void);
		 CZBuffer(const HDC hDC, const RECT& rcPaint);
		~CZBuffer(VOID);

	public:
		HRESULT  CopyTo(HBITMAP& hBitmap);
		HRESULT  CopyTo(CONST HDC hCompatibleDC, const INT _x, const INT _y, const BYTE _alpha = eAlphaValue::eOpaque );
		HRESULT  Create(const HDC hDC, const RECT& rcPaint);
		
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
		VOID     Reset       (void)      ; // copies the buffer content to original device and resets the buffer to uninitialized state;
	public:
		operator HDC     (void) const { return TBaseDC::m_hDC; }
		operator HBITMAP (void) const { return this->m_surface.m_hBitmap; }

	public:
		static const bool Is (const HDC); // returns true if a handle provided has proper type value;

	private:
		CZBuffer(const CZBuffer&);
		CZBuffer& operator= (const CZBuffer&);
	};
}}

typedef ex_ui::draw::CZBuffer  TZBuffer;
#endif
#endif/*_SHAREDUIXGDIZ_BUF_H_INCLUDED*/