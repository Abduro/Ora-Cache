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
}}}

using namespace ex_ui::draw::_impl;
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

CZBuffer:: CZBuffer (void) : m_origin(nullptr) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CZBuffer:: CZBuffer (const HDC _h_origin, const t_rect& _rc_draw) : CZBuffer() { this->Create(_h_origin, _rc_draw); }
CZBuffer::~CZBuffer (void) { this->Reset(); }

/////////////////////////////////////////////////////////////////////////////

err_code  CZBuffer::Create (const HDC _h_origin, const t_rect& _rc_draw)  {
	_h_origin; _rc_draw;
	err_code n_result = __s_ok;

	if (this->Is_valid())
		return this->m_error << __METHOD__ << (err_code) TErrCodes::eObject::eExists;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createcompatibledc ;
	if (nullptr == TDC::CreateCompatibleDC(_h_origin))
		return n_result = (this->m_error << __METHOD__).Last();

	this->m_origin = _h_origin;

	if (__failed(this->m_surface.Create(_h_origin, _rc_draw))) // needs to be checked against input dc and CreateDIBSection; (done)
		return this->m_error = this->m_surface.Error();

	if (__failed(this->m_surface.ApplyTo(TDC::m_hDC)))         // applying new surface created above to select into this memory device context;
		return this->m_error = this->m_surface.Error();

	return n_result;
}
err_code  CZBuffer::Reset (void){
	
	err_code n_result = __s_ok;

	if (this->Is_valid() == false)
		return this->m_error << __METHOD__ << __e_not_inited;

	if (this->m_surface.Prev()) {
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-bitblt ;
		const t_rect& rc_draw = this->m_surface.Area();

		const bool b_result = !!::BitBlt(
		/*  the surface object that is applied to this in-memory device context sets the view port to 0:0,
		    this is made for cases when the device context is created for particular area of drawing operation, not for entire client rectangle;
		    thus, in-memory device context draw area is always set to 0:0 in case of using entire client area of the window being drawn;
			perhaps it must be reviewed more carefully for applying clipping regions properly;
		*/
			this->m_origin, rc_draw.left, rc_draw.top, __W(rc_draw), __H(rc_draw), TDC::m_hDC, rc_draw.left, rc_draw.top, SRCCOPY
		);
		if (false == b_result)
			n_result = (this->m_error << __METHOD__).Last();

		// https://stackoverflow.com/questions/27422871/does-deletedc-automatically-unselect-objects ;

		TDC::SelectBitmap(this->m_surface.Prev()); // the bitmap being returned is not important;
		this->m_surface.Destroy();                 // the result being returned is not important, bedause the device context is deleted in any case;

		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-deletedc;
		if (::DeleteDC(TDC::m_hDC))
			TDC::m_hDC = nullptr;
		else
			n_result = (this->m_error << __METHOD__).Last();
	}
	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

TError&   CZBuffer::Error (void) const { return this->m_error; }
bool      CZBuffer::Is_valid (void) const { return nullptr != TDC::m_hDC && OBJ_DC != ::GetObjectType(TDC::m_hDC); }

/////////////////////////////////////////////////////////////////////////////

err_code  CZBuffer::Draw (const CLine& _line) {
	
	err_code n_result = __s_ok;

	if (_line.Is_valid() == false) return n_result = this->m_error << __METHOD__ << __e_inv_arg;
	if (this->Is_valid() == false) return n_result = this->m_error << __METHOD__ << __e_not_inited;

	class CAdjuster { // the line is already checked for validity and requires to be checked for direction: vertical or horizontal;
	public:           // actually the line direction may be ignored, but it's very possible to have a drawing that looks like not expected to;
		 CAdjuster (const CLine& _line) : m_line(_line){} CAdjuster (void) = delete; CAdjuster (const CAdjuster&) = delete; CAdjuster (CAdjuster&&) = delete;
		~CAdjuster (void) {}
	public:
		err_code Do (CRect& _rect) const {
			_rect;
			err_code n_result = __s_ok;
			_rect.SetRect(this->m_line.Begin(), this->m_line.End());

			if (false){}
			else if (this->m_line.Is_horz()) {
				// the line thickness is added to the end point Y value; it is assumed the end point Y not less than start point Y;
				_rect.bottom += this->m_line.Thickness();
			} 
			else if (this->m_line.Is_vert()) {
				// the line thickness is added to the end point X value; it is assumed the end point X not less than start point X;
				_rect.right  += this->m_line.Thickness();
			}
			else {
				n_result = /*__e_not_expect*/(err_code)TErrCodes::eData::eUnsupport;
			}
			return n_result;
		}

	private:
		CAdjuster& operator = (const CAdjuster&) = delete; CAdjuster& operator = (CAdjuster&&) = delete;
	private:
		const CLine& m_line;
	};
#if (0)
	if (_line.Is_vert () == false && _line.Is_horz() == false)
		return this->m_error << (err_code)TErrCodes::eData::eUnsupport;
#endif
	// it uses the alpha blend, thus the line is substituted by the rectangle of appropriate size;
	// or if the line thickeness is greater than 1px, the same approach is used;
	if (_line.Color().A() != 0x0 || _line.Thickness() > 1) { 
		
		CRect rect_;
		this->m_error << CAdjuster(_line).Do(rect_);
		if (this->Error())
			return this->Error();
		
		this->Draw(rect_, _line.Color());
	}
	else { // the line is drawn in regular manner;
		::WTL::CPen cPen;
		cPen.CreatePen(PS_SOLID, _line.Thickness(), _line.Color().ToRgb());

		const int32_t nSave = TDC::SaveDC();
		TDC::SelectPen(cPen);

		TDC::MoveTo(_line.Begin().X(), _line.Begin().Y()); // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-movetoex ;
		TDC::LineTo(_line.End().X(), _line.End().Y());     // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-lineto ;

		TDC::RestoreDC(nSave);
	}

	return n_result;
}

err_code  CZBuffer::Draw (const CLine& _line, const rgb_color _clr) {
	_line; _clr;
	err_code n_result = __s_ok;

	if (_line.Is_valid() == false) return n_result = this->m_error << __METHOD__ << __e_inv_arg;
	if (this->Is_valid() == false) return n_result = this->m_error << __METHOD__ << __e_not_inited;

	::WTL::CPen cPen;
	cPen.CreatePen(PS_SOLID, _line.Thickness(), _clr);

	const int32_t nSave = TDC::SaveDC();
	TDC::SelectPen(cPen);

	TDC::MoveTo(_line.Begin().X(), _line.Begin().Y());
	TDC::LineTo(_line.End().X(), _line.End().Y());

	TDC::RestoreDC(nSave);

	return n_result;
}

err_code  CZBuffer::Draw (const CRect& _rect, const TRgbQuad& _clr) {
	return this->Draw((const t_rect&)_rect, _clr);
}

err_code  CZBuffer::Draw (const t_rect& _rect, const TRgbQuad& _clr) {
	_rect; _clr;
	err_code n_result = __s_ok;

	if (::IsRectEmpty(&_rect)) return this->m_error <<__METHOD__ << __e_rect;
	if (this->Is_valid() == false) return this->m_error <<__METHOD__ << __e_not_inited;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-rectvisible ;
	if (false == !!::RectVisible(TDC::m_hDC, &_rect))
		return this->m_error <<__METHOD__ << __s_false;

	if (false) {}                    // https://learn.microsoft.com/en-us/windows/win32/gdi/drawing-rectangles ;
	else if (_clr.A() == 0xff) {}    // is transparent and nothing to draw;
	else if (_clr.A() == 0x00) {     // draws the rectangle by filling solid color;

		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-fillrect ;
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createsolidbrush ;
		class CBrush {
		public:
			 CBrush (const rgb_color _clr) : m_brush(nullptr) { this->m_brush = ::CreateSolidBrush(_clr); }
			~CBrush (void) { if (this->m_brush){ ::DeleteObject(this->m_brush); this->m_brush = nullptr; }}
			HBRUSH  Get (void) const { return this->m_brush; }
		private:
			HBRUSH m_brush;
		};
#if (1)
		if (false == !!TDC::FillRect(&_rect, CBrush(/*_clr.ToRgb()*/TRgbQuad(0,0,0xff).ToRgb()).Get()))
			return (this->m_error << __METHOD__).Last();
#else
		if (false == !!::FillRect(TDC::m_hDC, &_rect, CBrush(_clr.ToRgb()).Get()))
			return (this->m_error << __METHOD__).Last();
#endif
	}
	else { // draws semitransparent rectangle by applying alpha blend;

		CBlender blender;
		blender.Func().PerPixelAlpha(false, rgb_value(int32_t(0xff * _clr.A() / 100)));
		blender.Out() << this->m_origin << (const t_rect&)_rect;
		blender.Src() << TDC::m_hDC << (const t_rect&)_rect;

		if (__failed(blender.Draw()))
			n_result = this->m_error = blender.Error();
	}

	return n_result;
}

err_code  CZBuffer::Draw (const t_rect& _rect, const rgb_color _clr) {
	_rect; _clr;
	err_code n_result = __s_ok;

	if (::IsRectEmpty(&_rect)) return this->m_error <<__METHOD__ << __e_rect;
	if (this->Is_valid() == false) return this->m_error <<__METHOD__ << __e_not_inited;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-rectvisible ;
	if (false == !!::RectVisible(TDC::m_hDC, &_rect))
		return this->m_error <<__METHOD__ << __s_false;

	if (false) {} // https://learn.microsoft.com/en-us/windows/win32/gdi/drawing-rectangles ;
	else {
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-fillrect ;
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createsolidbrush ;
		class CBrush {
		public:
			 CBrush (const rgb_color _clr) : m_brush(nullptr) { this->m_brush = ::CreateSolidBrush(_clr); }
			~CBrush (void) { if (this->m_brush){ ::DeleteObject(this->m_brush); this->m_brush = nullptr; }}
			HBRUSH  Get (void) const { return this->m_brush; }
		private:
			HBRUSH m_brush;
		};
#if (1)
		if (false == !!TDC::FillRect(&_rect, CBrush(_clr).Get()))
			return (this->m_error << __METHOD__).Last();
#else
		if (false == !!::FillRect(TDC::m_hDC, &_rect, CBrush(_clr.ToRgb()).Get()))
			return (this->m_error << __METHOD__).Last();
#endif
	}
	return n_result;
}

err_code  CZBuffer::Draw  (_pc_sz pszText, const h_font& fnt_, const t_rect& _rect, const rgb_color clrFore, const dword _u_format) {
	pszText; fnt_; _rect; clrFore; _u_format;

	err_code n_result = __s_ok;

	if (::IsRectEmpty(&_rect)) return this->m_error <<__METHOD__<<__e_rect;
	if (this->Is_valid() == false) return this->m_error <<__METHOD__<<__e_not_inited;

	if (!pszText || !::lstrlenW(pszText))
		return this->m_error <<__METHOD__<<__e_inv_arg;

	static const dword fmt_ = DT_LEFT | DT_VCENTER |/*DT_WORDBREAK*/DT_END_ELLIPSIS | DT_NOCLIP | DT_NOPREFIX /*|DT_MODIFYSTRING*/;

	const h_font    fnt_loc = (nullptr == fnt_ ? (h_font)::GetStockObject(DEFAULT_GUI_FONT) : fnt_);
	const rgb_color clr_loc = (__clr_none == clrFore ? ::GetSysColor(COLOR_WINDOWTEXT) : clrFore);
	const dword     fmt_loc = (0 == _u_format ? fmt_ : _u_format);

	const int32_t nSave = TDC::SaveDC();

	TDC::SelectFont(fnt_loc);          // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-selectobject ;
	if (0 == TDC::SetBkMode(__no_bkg)) // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setbkmode ; the example of text rotation;
		n_result = (this->m_error << __METHOD__).Last();
	if (__clr_invalid == TDC::SetTextColor(clr_loc))
		n_result = (this->m_error << __METHOD__).Last();

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtext ;
	if (0 == ::DrawText(TDC::m_hDC, pszText, -1, const_cast<t_rect*>(&_rect), fmt_loc))
		n_result = (this->m_error <<__METHOD__).Last();

	TDC::RestoreDC(nSave);

	return n_result;
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