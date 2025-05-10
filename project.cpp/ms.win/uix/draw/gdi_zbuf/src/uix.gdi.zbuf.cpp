/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2020 at 4:42:18, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared draw library Z-buffer interface implementation file.
*/
#include "uix.gdi.zbuf.h"

using namespace ex_ui::draw::memory;

#ifndef __W
#define __W(_rect) (_rect.right - _rect.left)
#endif
#ifndef __H
#define __H(_rect) (_rect.bottom - _rect.top)
#endif

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace _impl {

	void DrawGradRect(const HDC hDC, const RECT& rcDraw, const COLORREF clrFrom, const COLORREF clrUpto, const bool bVertical)
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

using namespace ex_ui::draw::_impl;
/////////////////////////////////////////////////////////////////////////////

CDrawArea:: CDrawArea (void) : m_rect {0} {}
CDrawArea:: CDrawArea (const t_rect& _rect) : CDrawArea() { *this << _rect; }
CDrawArea::~CDrawArea (void) {}

/////////////////////////////////////////////////////////////////////////////
const
t_rect&  CDrawArea::Get (void) const { return this->m_rect; }
t_rect&  CDrawArea::Get (void)       { return this->m_rect; }

bool     CDrawArea::Is_empty (void) const { return !!::IsRectEmpty(&this->Get()); }

bool     CDrawArea::Set (const t_rect& _rect) {
	const bool b_changed = (
		_rect.left != this->Get().left || _rect.top != this->Get().top || _rect.right != this->Get().right || _rect.bottom != this->Get().bottom
	);
	if (b_changed)
		this->m_rect = _rect;
	return b_changed;
}

CDrawArea& CDrawArea::operator <<(const t_rect& _rect) { this->Get() = _rect; return *this; }

/////////////////////////////////////////////////////////////////////////////

CCopier:: CCopier (const HDC& _h_mem_dc) : m_mem_dc(_h_mem_dc) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CCopier::~CCopier (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CDrawArea& CCopier::DrawArea (void) const { return this->m_drw_area; }
CDrawArea& CCopier::DrawArea (void)       { return this->m_drw_area; }

TError&   CCopier::Error (void) const { return this->m_error; }
bool      CCopier::Is_valid (void) const { return CZBuffer::Is_DC(this->m_mem_dc); }

err_code  CCopier::To (HBITMAP& _h_out) const {
	_h_out;
	this->m_error << __METHOD__ << __s_ok;

	if (_h_out)
		return this->m_error << (err_code) TErrCodes::eObject::eExists;
	if (false == this->Is_valid())
		return this->m_error << __e_not_inited;
	const
	HDC  hCompatible = ::CreateCompatibleDC(this->m_mem_dc);
	if (!hCompatible)
		return this->m_error.Last();
#if (0)
	BITMAPINFO info_ = { {sizeof( BITMAPINFO ), __W(m_rcPaint), __H(m_rcPaint), 1, 32, BI_RGB, 0, 0, 0, 0, 0}, {0, 0, 0, 0}};

	hBitmap = ::CreateDIBSection(*this, &info_, DIB_RGB_COLORS, NULL, NULL, 0);
	{
		HGDIOBJ prev = ::SelectObject(hCompatible, (HGDIOBJ)hBitmap);
		hr_ = this->CopyTo(hCompatible, 0, 0);
		::SelectObject(hCompatible, prev);
	}
	::DeleteDC(hCompatible);
	hCompatible = NULL;
#endif
	return  this->Error();
}

err_code  CCopier::To (const HDC _h_comp_dc, const int32_t _x, const int32_t _y, const _byte _alpha) {
	_h_comp_dc; _x; _y; _alpha;
	this->m_error << __METHOD__ << __s_ok;

	if (false == this->Is_valid())
		return this->m_error << __e_not_inited;

	if (this->DrawArea().Is_empty())
		return this->m_error << __e_rect;
#if (0)
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
#endif
	return this->Error();
}


/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CSurface:: CSurface (void) : m_surface{nullptr}, m_rc_draw{0} { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CSurface::~CSurface (void) { this->Destroy(); }

/////////////////////////////////////////////////////////////////////////////

err_code   CSurface::ApplyTo(const HDC _h_mem_dc) {
	_h_mem_dc;
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _h_mem_dc || OBJ_MEMDC != ::GetObjectType(_h_mem_dc))
		return this->m_error << __e_inv_arg = _T("Input arg is not memory device context");

	if (this->Is_valid() == false)
		return this->m_error << __e_not_inited;

	this->Prev() = (HBITMAP)::SelectObject(_h_mem_dc, this->New());
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setviewportorgex ;
	::SetViewportOrgEx(_h_mem_dc, -this->Area().left, -this->Area().top, nullptr);
	return this->Error();
}
const
t_rect&    CSurface::Area (void) const { return this->m_rc_draw; }
t_rect&    CSurface::Area (void)       { return this->m_rc_draw; }

err_code   CSurface::Create (const HDC _h_origin, const t_rect& _rc_draw) {
	_h_origin; _rc_draw;
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	if (::IsRectEmpty(&_rc_draw))
		return this->m_error << __e_rect;

	if (nullptr == _h_origin || OBJ_DC != ::GetObjectType(_h_origin))
		return this->m_error << (err_code) TErrCodes::eObject::eHandle;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createcompatiblebitmap ;
	this->New() = ::CreateCompatibleBitmap(_h_origin, __W(_rc_draw), __H(_rc_draw));

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createdibsection ;
	if (nullptr == this->New()) {

		BITMAPINFO info_ = { {sizeof( BITMAPINFO ), __W(_rc_draw), __H(_rc_draw), 1, 32, BI_RGB, 0, 0, 0, 0, 0}, {0, 0, 0}};
		this->New() = ::CreateDIBSection(_h_origin, &info_, DIB_RGB_COLORS, NULL, NULL, 0);
		if (nullptr == this->New())
			return this->m_error.Last();
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-selectobject ;
	this->Area() = _rc_draw;
#if (0)
	// this is applied to memory device context, not to origin device context;
	this->Prev() = (HBITMAP)::SelectObject(_h_mem_dc, this->New());
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setviewportorgex ;
	::SetViewportOrgEx(_h_mem_dc, -_rc_draw.left, -_rc_draw.top, nullptr);
#endif
	return this->Error();
}

err_code   CSurface::Destroy (void) {
	this->m_error << __METHOD__ << __s_ok;
	if (this->New()) {
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-deleteobject ;
		if (false == !!::DeleteObject(this->New())) {
			return this->m_error << __e_fail << _T("The bitmap is selected in the device context"); // there is no way to get exact error;
		}
	}
	this->New() = nullptr;
	this->Prev() = nullptr;

	::SetRectEmpty(&this->Area());

	this->m_error << __e_not_inited;
	return __s_ok; // this is because after calling this method, the surface state is set to uninitialized one, and error object is set accordingly;
}

TError&    CSurface::Error (void) const { return this->m_error; }
bool       CSurface::Is_valid (void) const {
	bool b_result = false;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getobjecttype ;
	b_result = (!::IsRectEmpty(&this->Area()) && nullptr != this->New() && OBJ_BITMAP == ::GetObjectType(this->New()));

	return b_result;
}
const
HBITMAP&   CSurface::Prev (void) const { return this->m_surface[0]; }
HBITMAP&   CSurface::Prev (void)       { return this->m_surface[0]; }
const
HBITMAP&   CSurface::New  (void) const { return this->m_surface[1]; }
HBITMAP&   CSurface::New  (void)       { return this->m_surface[1]; }

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CZBuffer:: CZBuffer (void) : m_origin(nullptr), m_copier(TDC::m_hDC) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CZBuffer:: CZBuffer (const HDC _h_origin, const t_rect& _rc_draw) : CZBuffer() { this->Create(_h_origin, _rc_draw); }
CZBuffer::~CZBuffer (void) { this->Reset(); }

/////////////////////////////////////////////////////////////////////////////
const
CCopier&  CZBuffer::Copier (void) const { return this->m_copier; }
err_code  CZBuffer::Create (const HDC _h_origin, const t_rect& _rc_draw)  {
	_h_origin; _rc_draw;
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createcompatibledc ;
	if (nullptr == TDC::CreateCompatibleDC(_h_origin))
		return this->m_error.Last();

	this->m_origin = _h_origin;

	if (__failed(this->m_surface.Create(_h_origin, _rc_draw))) // needs to be checked against input dc and CreateDIBSection; (done)
		return this->m_error = this->m_surface.Error();

	if (__failed(this->m_surface.ApplyTo(TDC::m_hDC)))         // applying new surface created above to select into this memory device context;
		return this->m_error = this->m_surface.Error();

	return this->Error();
}

TError&   CZBuffer::Error (void) const { return this->m_error; }

bool      CZBuffer::Is_valid (void) const { return nullptr != TDC::m_hDC && OBJ_DC != ::GetObjectType(TDC::m_hDC); }

err_code  CZBuffer::Reset (void){
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid() == false)
		return this->m_error << __e_not_inited;

	if (this->m_surface.Prev()) {
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-bitblt ;
		const t_rect& rc_draw = this->m_surface.Area();

		const bool b_result = !!::BitBlt(
			this->m_origin, rc_draw.left, rc_draw.top, __W(rc_draw), __H(rc_draw), TDC::m_hDC, rc_draw.left, rc_draw.top, SRCCOPY
		);
		if (false == b_result)
			this->m_error.Last();

		// https://stackoverflow.com/questions/27422871/does-deletedc-automatically-unselect-objects ;

		TDC::SelectBitmap(this->m_surface.Prev()); // the bitmap being returned is not important;
		this->m_surface.Destroy();                 // the result being returned is not important, bedause the device context is deleted in any case;

		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-deletedc;
		if (::DeleteDC(TDC::m_hDC))
			TDC::m_hDC = nullptr;
		else
			this->m_error.Last();
	}
	return this->Error();
}

const
CSurface& CZBuffer::Surface (void) const { return this->m_surface; }
CSurface& CZBuffer::Surface (void)       { return this->m_surface; }

/////////////////////////////////////////////////////////////////////////////

bool CZBuffer::Is_DC (const HDC _hdc) {
	_hdc;
	if (nullptr == _hdc) return false;
	const dword d_type = ::GetObjectType(_hdc); return (OBJ_MEMDC == d_type || OBJ_DC == d_type);
}

bool CZBuffer::Is_DC_mem (const HDC _hdc) {
	_hdc;
	if (nullptr == _hdc) return false;
	const dword d_type = ::GetObjectType(_hdc); return (OBJ_MEMDC == d_type/* || OBJ_DC == d_type*/);
}

#if (0)
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
#endif