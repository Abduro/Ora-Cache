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