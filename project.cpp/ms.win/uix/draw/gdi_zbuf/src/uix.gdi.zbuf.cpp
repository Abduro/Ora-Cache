/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2020 at 4:42:18, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared draw library Z-buffer interface implementation file.
*/
#include "uix.gdi.zbuf.h"
#if (0)
using namespace ex_ui::draw;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace details
{
	void GdiProvider_DrawGradRect(const HDC hDC, const RECT& rcDraw, const COLORREF clrFrom, const COLORREF clrUpto, const bool bVertical)
	{
		TRIVERTEX        vert[2] = {0};
		GRADIENT_RECT    gRect   = {0};
		vert [0] .x      = rcDraw.left;
		vert [0] .y      = rcDraw.top;
		vert [0] .Red    = GetRValue(clrFrom)<<8;
		vert [0] .Green  = GetGValue(clrFrom)<<8;
		vert [0] .Blue   = GetBValue(clrFrom)<<8;
		vert [0] .Alpha  = 0x0000;

		vert [1] .x      = rcDraw.right;
		vert [1] .y      = rcDraw.bottom; 
		vert [1] .Red    = GetRValue(clrUpto)<<8;
		vert [1] .Green  = GetGValue(clrUpto)<<8;
		vert [1] .Blue   = GetBValue(clrUpto)<<8;
		vert [1] .Alpha  = 0x0000;
		// https://docs.microsoft.com/en-us/windows/win32/gdi/drawing-a-shaded-rectangle
		// https://docs.microsoft.com/en-us/windows/win32/gdi/drawing-a-shaded-triangle

		gRect.UpperLeft  = 0;
		gRect.LowerRight = 1;
		::GradientFill(hDC, vert, 2, &gRect, 1, bVertical ? GRADIENT_FILL_RECT_V : GRADIENT_FILL_RECT_H);
	}
}}}
using namespace ex_ui::draw::details;
/////////////////////////////////////////////////////////////////////////////

CZBuffer:: CZBuffer (void): m_hOrigin(NULL), m_hBmpOld(NULL) {}
CZBuffer:: CZBuffer (const HDC hDC, const RECT& rcPaint) : CZBuffer() { this->Create(hDC, rcPaint); }
CZBuffer::~CZBuffer (VOID) { this->Reset(); }

/////////////////////////////////////////////////////////////////////////////

HRESULT CZBuffer::CopyTo (HBITMAP& hBitmap)
{
	if (hBitmap)
		return HRESULT_FROM_WIN32(ERROR_OBJECT_ALREADY_EXISTS);

	HRESULT hr_ = S_OK;
	HDC hCompatible = ::CreateCompatibleDC(*this);
	if (!hCompatible)
		return HRESULT_FROM_WIN32(::GetLastError());

	BITMAPINFO info_ = { {sizeof( BITMAPINFO ), __W(m_rcPaint), __H(m_rcPaint), 1, 32, BI_RGB, 0, 0, 0, 0, 0}, {0, 0, 0, 0}};
	
	hBitmap = ::CreateDIBSection(*this, &info_, DIB_RGB_COLORS, NULL, NULL, 0);
	{
		HGDIOBJ prev = ::SelectObject(hCompatible, (HGDIOBJ)hBitmap);
		hr_ = this->CopyTo(hCompatible, 0, 0);
		::SelectObject(hCompatible, prev);
	}
	::DeleteDC(hCompatible);
	hCompatible = NULL;
	return  hr_;
}

HRESULT CZBuffer::CopyTo (CONST HDC hCompatibleDC, const INT _x, const INT _y, const BYTE _alpha)
{
	if (!this->IsValid())
		return OLE_E_BLANK;

	const SIZE sz_ = {__W(m_rcPaint), __H(m_rcPaint)};

	if (TAlpha::eOpaque == _alpha)
	{
		const BOOL bResult = ::BitBlt(hCompatibleDC, _x, _y, sz_.cx, sz_.cy, TBaseDC::m_hDC, m_rcPaint.left, m_rcPaint.top, SRCCOPY);
		return (!bResult ? HRESULT_FROM_WIN32(::GetLastError()) : S_OK);
	}
	else
	{
		BLENDFUNCTION bf = {0};
		bf.BlendOp       = AC_SRC_OVER;
		bf.BlendFlags    = 0;
		bf.SourceConstantAlpha = _alpha;
		bf.AlphaFormat         = 0;
		const BOOL bResult = ::AlphaBlend(
			hCompatibleDC,
			_x,
			_y,
			sz_.cx,
			sz_.cy,
			TBaseDC::m_hDC,
			m_rcPaint.left,
			m_rcPaint.top,
			sz_.cx,
			sz_.cy,
			bf
		);
		return (bResult ? S_OK : HRESULT_FROM_WIN32(::GetLastError()));
	}
}

HRESULT CZBuffer::Create (const HDC hDC, const RECT& rcPaint)  {
	this->Reset();

	m_hOrigin = hDC;
	m_rcPaint = rcPaint;
	TBaseDC::CreateCompatibleDC(m_hOrigin);
	if (!TBaseDC::m_hDC)
		return (HRESULT_FROM_WIN32(::GetLastError()));

	const SIZE sz_ = {
		__W(m_rcPaint),
		__H(m_rcPaint)
	};
	// TODO: DIB Section class already exists and must be used here;
	m_surface.CreateCompatibleBitmap(m_hOrigin, sz_.cx, sz_.cy);
	if (0==m_surface)
	{
		BITMAPINFO info_ = { {sizeof( BITMAPINFO ), sz_.cx, sz_.cy, 1, 32, BI_RGB, 0, 0, 0, 0, 0}, {0, 0, 0}};
		m_surface = ::CreateDIBSection(hDC, &info_, DIB_RGB_COLORS, NULL, NULL, 0);

		if(!m_surface)
			return (HRESULT_FROM_WIN32(::GetLastError()));
	}
	m_hBmpOld = TBaseDC::SelectBitmap(m_surface);
	TBaseDC::SetViewportOrg(-m_rcPaint.left, -m_rcPaint.top);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////

VOID    CZBuffer::DrawLine (const CPosition& _pos, const CColour& _clr, const INT nThickness)
{
	if (_pos.IsHorz())
	{
		const LONG n_bottom = _pos.Start().y + nThickness;
		const RECT rc_ = {
			_pos.Start().x, _pos.Start().y, _pos.End().x, n_bottom
		};
		this->DrawRectangle(rc_, _clr, _clr, false, _clr.Alpha());
#if defined(_DEBUG)
		ATLTRACE(_T("%s:horz_rc={l:%d|t:%d|r:%d|b:%d};\n"), (LPCTSTR)__METHOD__, rc_.left, rc_.top, rc_.right, rc_.bottom);
#endif
	}
	if (_pos.IsVert())
	{
		const bool b_top_bottom = (_pos.End().y > _pos.Start().y); // if true that is the right side, otherwise is the left one;

		const RECT rc_line = {
			_pos.Start().x,
			(b_top_bottom ? _pos.Start().y : _pos.End().y),
			_pos.Start().x + nThickness, 
			(b_top_bottom ? _pos.End().y : _pos.Start().y)
		};

		this->DrawRectangle(rc_line, _clr, _clr, true, _clr.Alpha());
		
#if defined(_DEBUG)
		ATLTRACE(_T("%s:vert_rc={l:%d|t:%d|r:%d|b:%d};\n"), (LPCTSTR)__METHOD__, rc_line.left, rc_line.top, rc_line.right, rc_line.bottom);
#endif
	}
}
VOID    CZBuffer::DrawLine (const CPosition& _pos, const COLORREF _clr, const INT nThickness) {
	this->DrawLine(_pos.Start(), _pos.End(), _clr, nThickness);
}
VOID    CZBuffer::DrawLine (const INT _x0, const INT _y0, const INT _x1, const INT _y1, const COLORREF _clr, const INT nThickness)
{
	::WTL::CPen cPen;
	cPen.CreatePen(PS_SOLID, nThickness, _clr);

	const INT nSave = TBaseDC::SaveDC();
	TBaseDC::SelectPen(cPen);

	TBaseDC::MoveTo(_x0, _y0);
	TBaseDC::LineTo(_x1, _y1);

	TBaseDC::RestoreDC(nSave);
}

VOID    CZBuffer::DrawLine (const POINT& _start, const POINT& _end, const COLORREF _clr, const INT nThickness) {
	this->DrawLine(_start.x, _start.y, _end.x, _end.y, _clr, nThickness);
}

/////////////////////////////////////////////////////////////////////////////

VOID    CZBuffer::DrawRectangle (CONST CRounded& _rect, CONST COLORREF _borders, CONST COLORREF _fill) CONST {
	if (_rect.Is() == false)
		return;
	if (CLR_NONE == _borders && CLR_NONE == _fill)
		return;
	Gdiplus::Graphics gp_(TBaseDC::m_hDC);
	gp_.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	if (CLR_NONE != _fill) {
		Gdiplus::SolidBrush br_(_fill);
		gp_.FillPath(&br_, &_rect.Path());
	}
	if (CLR_NONE != _borders) {
		Gdiplus::Pen  pn_(_borders);
		gp_.DrawPath(&pn_, &_rect.Path());
	}
}

VOID    CZBuffer::DrawRectangle (const RECT& _rc, const COLORREF _c_0, const COLORREF _c_1, const bool bVertical, const BYTE ba) const
{
	if (::IsRectEmpty(&_rc) || !TBaseDC::m_hDC)
		return;
	if (ba < 1) // fully transparent
		return;

	if (ba < TAlpha::eOpaque)
	{
		HDC hdcMem = ::CreateCompatibleDC(TBaseDC::m_hDC);
		SIZE sz = { __W(_rc), __H(_rc) }; 

		HBITMAP hbmpCanvas = ::CreateCompatibleBitmap(TBaseDC::m_hDC, sz.cx, sz.cy);
		if (hbmpCanvas)
		{
			const RECT rc_ = {0, 0, sz.cx, sz.cy};
			const INT iZPoint  = ::SaveDC(hdcMem);
			::SelectObject(hdcMem, (HGDIOBJ)hbmpCanvas);

			details::GdiProvider_DrawGradRect(hdcMem, rc_, _c_0, _c_1, bVertical);

			BLENDFUNCTION blfun = {0}; 
			blfun.BlendOp       = AC_SRC_OVER; 
			blfun.BlendFlags    = 0; 
			blfun.SourceConstantAlpha = BYTE(INT(TAlpha::eOpaque * ba / 100)); 
			blfun.AlphaFormat   = 0;

			::AlphaBlend(
				TBaseDC::m_hDC, _rc.left, _rc.top, sz.cx, sz.cy, hdcMem, 0, 0, sz.cx, sz.cy, blfun
			);

			::RestoreDC(hdcMem, iZPoint);
			::DeleteObject((HGDIOBJ)hbmpCanvas);
		}
		::DeleteDC(hdcMem);
	}
	else
		details::GdiProvider_DrawGradRect(TBaseDC::m_hDC, _rc, _c_0, _c_1, bVertical);
}

VOID    CZBuffer::DrawRectangle (const RECT& rcDraw, const COLORREF clrBorder, const INT nThickness, const DWORD dwEdges)
{
	if (::IsRectEmpty(&rcDraw) || !TBaseDC::m_hDC)
		return;

	::WTL::CPen pen_;
	pen_.CreatePen(PS_SOLID, nThickness, clrBorder);

	const INT nSave = TBaseDC::SaveDC();
	TBaseDC::SelectPen(pen_);

	// 1) left side
	if (CRectEdge::eLeft & dwEdges)
	{
		TBaseDC::MoveTo(rcDraw.left, rcDraw.bottom - nThickness);
		TBaseDC::LineTo(rcDraw.left, rcDraw.top);
	}
	// 2) top side
	if (CRectEdge::eTop  & dwEdges)
	{
		TBaseDC::MoveTo(rcDraw.left, rcDraw.top);
		TBaseDC::LineTo(rcDraw.right - nThickness, rcDraw.top);
	}
	// 3) right side
	if (CRectEdge::eRight & dwEdges)
	{
		TBaseDC::MoveTo(rcDraw.right - nThickness, rcDraw.top);
		TBaseDC::LineTo(rcDraw.right - nThickness, rcDraw.bottom - nThickness);
	}
	// 4) bottom side
	if (CRectEdge::eBottom & dwEdges)
	{
		TBaseDC::MoveTo(rcDraw.right - nThickness, rcDraw.bottom - nThickness);
		TBaseDC::LineTo(rcDraw.left, rcDraw.bottom - nThickness);
	}
	TBaseDC::RestoreDC(nSave);
}

VOID    CZBuffer::DrawSolidRect (const RECT& rcDraw, const CColour& clr)const
{
	Gdiplus::Rect rc0(rcDraw.left, rcDraw.top, __W(rcDraw), __H(rcDraw));
	Gdiplus::SolidBrush br0(clr);
	Gdiplus::Graphics gp_(TBaseDC::m_hDC);
	gp_.FillRectangle(&br0, rc0);
}

VOID    CZBuffer::DrawSolidRect (const RECT& rcDraw, const COLORREF clrFill, const BYTE _alpha) const
{
	if (::IsRectEmpty(&rcDraw) || CLR_NONE == clrFill)
		return;
	if (eAlphaValue::eTransparent == _alpha)
		return;

	CColour clr(clrFill, _alpha);
	this->DrawSolidRect(rcDraw, clr);
}

/////////////////////////////////////////////////////////////////////////////

VOID    CZBuffer::DrawTextExt (LPCTSTR pszText, const HFONT fnt_, const RECT& rcDraw, const COLORREF clrFore, const DWORD fmt_)
{
	if (!pszText || !::lstrlenW(pszText))
		return;
	if (::IsRectEmpty(&rcDraw))
		return;
	const HFONT    fnt_loc = (NULL == fnt_ ? (HFONT)::GetStockObject(DEFAULT_GUI_FONT) : fnt_);
	const COLORREF clr_loc = (CLR_NONE == clrFore ? ::GetSysColor(COLOR_WINDOWTEXT) : clrFore);
	const DWORD    fmt_loc = (0 == fmt_ ? DT_LEFT | DT_VCENTER | DT_WORDBREAK | DT_NOCLIP | DT_NOPREFIX : fmt_);
	const INT   nSavePoint = TBaseDC::SaveDC();
	TBaseDC::SelectFont(fnt_loc);
	TBaseDC::SetBkMode(TRANSPARENT);
	TBaseDC::SetTextColor(clr_loc);

	::DrawText(TBaseDC::m_hDC, pszText, -1, const_cast<LPRECT>(&rcDraw), fmt_loc);

	TBaseDC::RestoreDC(nSavePoint);
}

VOID    CZBuffer::DrawTextExt (LPCTSTR pszText, LPCTSTR pszFontFamily, const DWORD dwFontSize, const RECT& rcDraw, const COLORREF clrFore, const DWORD dwFormat)
{
	if (!pszText
		|| !(::lstrlenW(pszText) > 0)
		|| !pszFontFamily
		|| !(::lstrlenW(pszFontFamily) > 0)
		|| !(dwFontSize > 0)
		|| ::IsRectEmpty(&rcDraw))
		return;

	Gdiplus::Graphics gp_(TBaseDC::m_hDC);
	ex_ui::draw::shape::CRectFEx rc_(rcDraw);

	CColour     color_(clrFore == CLR_NONE ? ::GetSysColor(COLOR_WINDOWTEXT) : clrFore);
	Gdiplus::Font fnt_(pszFontFamily, (Gdiplus::REAL)dwFontSize);

	Gdiplus::SolidBrush br_(color_);
	Gdiplus::StringFormat sfmt(Gdiplus::StringFormatFlagsNoClip);

	if (false){}
	else if (DT_RIGHT  & dwFormat)  sfmt.SetAlignment(Gdiplus::StringAlignmentFar );
	else if (DT_CENTER & dwFormat)  sfmt.SetAlignment(Gdiplus::StringAlignmentCenter);
	else                            sfmt.SetAlignment(Gdiplus::StringAlignmentNear);

	if (false){}
	else if (DT_VCENTER & dwFormat) sfmt.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	else if (DT_BOTTOM  & dwFormat) sfmt.SetLineAlignment(Gdiplus::StringAlignmentFar);
	else                            sfmt.SetLineAlignment(Gdiplus::StringAlignmentNear);

	gp_.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	gp_.DrawString(
		pszText,
		(INT)::lstrlenW(pszText),
		&fnt_,
		rc_,
		&sfmt,
		&br_
	);
}

/////////////////////////////////////////////////////////////////////////////
const
RECT&   CZBuffer::GetDrawRect (void) const { return m_rcPaint; }

bool    CZBuffer::IsValid (void) const { bool b_result = false;

	if (::IsRectEmpty(&m_rcPaint)) return b_result;
	if (CZBuffer::Is(TBaseDC::m_hDC) == false) return b_result;
	if (m_surface.IsNull()) return b_result;

	return (b_result = true);
}

VOID    CZBuffer::Reset   (void)
{
	if (m_hBmpOld)
	{
		const INT iWidth  = m_rcPaint.right - m_rcPaint.left;
		const INT iHeight = m_rcPaint.bottom - m_rcPaint.top;

		::BitBlt(m_hOrigin, m_rcPaint.left, m_rcPaint.top, iWidth, iHeight, TBaseDC::m_hDC, m_rcPaint.left, m_rcPaint.top, SRCCOPY);

		TBaseDC::SelectBitmap(m_hBmpOld);

		m_hOrigin = NULL;
		m_hBmpOld = NULL;
		m_surface.DeleteObject();

		::DeleteDC(TBaseDC::m_hDC); TBaseDC::m_hDC = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
const
bool    CZBuffer::Is (const HDC _hdc) {
	if (NULL == _hdc) return false;
	const DWORD d_type = ::GetObjectType(_hdc); return (OBJ_MEMDC == d_type || OBJ_DC == d_type);
}
#endif