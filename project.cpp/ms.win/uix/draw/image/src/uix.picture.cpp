/*
	This is a picture related interfaces' implementation file;
*/
#include "uix.picture.h"

namespace ex_ui { namespace draw { namespace images { namespace _impl { void __warning_lnk_4221 (void) {}}}}}

#if (0)
using namespace qchart::drawing;

/////////////////////////////////////////////////////////////////////////////

CPicture:: CPicture (void) {}
CPicture:: CPicture (const CPicture& _ref) : CPicture() { *this = _ref; }
CPicture::~CPicture (void) {}

/////////////////////////////////////////////////////////////////////////////

HRESULT    CPicture::Create  (const LPSTREAM _stream)
{
	HRESULT hr_ = S_OK;

	if (NULL == _stream)
		return (hr_ = E_POINTER);


	if (this->IsValid())
		return (hr_ = __DwordToHresult(ERROR_ALREADY_INITIALIZED));

	// https://docs.microsoft.com/en-us/windows/win32/api/olectl/nf-olectl-oleloadpicture
	hr_ = ::OleLoadPicture(_stream, 0, TRUE, IID_IPicture, (void**)&m_picture);
	if (FAILED(hr_))
		return hr_;

	if (false == this->IsValid())
		hr_ = __DwordToHresult(ERROR_UNSUPPORTED_TYPE);

	return  hr_;
}

HRESULT    CPicture::Create  (LPCTSTR _lp_sz_path)
{
	CGlobal_Alloca alloca_;
	CFile file_;

	HRESULT hr_ = file_.Open(_lp_sz_path);

	if (FAILED(hr_))
		return hr_;

	hr_ = alloca_.Allocate(file_.Size());
	if (FAILED(hr_))
		return hr_;

	hr_ = alloca_.Lock();
	if (FAILED(hr_))
		return hr_;

	hr_ = file_.Read(alloca_);
	if (FAILED(hr_))
		return hr_;

	hr_ = alloca_.Unlock(); // alloca_.Ptr() is not valid now; do not check for error code this time;

	CStream stream_;
	hr_  =  stream_.Create(alloca_);
	if (FAILED(hr_))
		return hr_;

	hr_ = this->Create(stream_);

	return  hr_;
}

bool       CPicture::IsValid (void) const { return (NULL != m_picture); }

const
IPicture*  CPicture::Ptr(void) const { return m_picture; }
IPicture*  CPicture::Ptr(void)       { return m_picture; }

HRESULT    CPicture::ToBitmap(HBITMAP& _in_out) const
{
	HRESULT hr_ = S_OK;

	if (_in_out)
		return (hr_ = __DwordToHresult(ERROR_ALREADY_INITIALIZED));

	if (false == this->IsValid())
		return (hr_ = OLE_E_BLANK);

	OLE_XSIZE_HIMETRIC cx = 0;
	OLE_YSIZE_HIMETRIC cy = 0;

	hr_ = m_picture->get_Width(&cx) ; if (FAILED(hr_)) return hr_;
	hr_ = m_picture->get_Height(&cy); if (FAILED(hr_)) return hr_;

	HDC hdc_desktop = ::GetDC(HWND_DESKTOP);

	const WORD ret_w = ::MulDiv(::GetDeviceCaps(hdc_desktop, LOGPIXELSX), (cx), 2540);
	const WORD ret_h = ::MulDiv(::GetDeviceCaps(hdc_desktop, LOGPIXELSY), (cy), 2540);

	// create compatible bitmap and DC
	HBITMAP hRezultBitmap = ::CreateCompatibleBitmap(hdc_desktop, ret_w, ret_h);
	HDC hBitmapDC = ::CreateCompatibleDC(hdc_desktop);

	if (hRezultBitmap && hBitmapDC)
	{
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hBitmapDC, hRezultBitmap);
		// https://docs.microsoft.com/en-us/windows/win32/api/ocidl/nf-ocidl-ipicture-render
		hr_ = m_picture->Render(hBitmapDC, 0, 0, ret_w, ret_h, 0, cy, cx, -cy, 0);

		::SelectObject(hBitmapDC, hOldBitmap);
		::ReleaseDC(HWND_DESKTOP, hBitmapDC);
	}
	else
		hr_ = E_FAIL;

	::ReleaseDC(HWND_DESKTOP, hdc_desktop); hdc_desktop = NULL;

	if (SUCCEEDED(hr_))
		_in_out = hRezultBitmap;

	return  hr_;
}

/////////////////////////////////////////////////////////////////////////////

CPicture&  CPicture::operator = (const CPicture& _ref) { this->m_picture = _ref.m_picture; return *this; }
CPicture&  CPicture::operator <<(const LPSTREAM _stream) { this->Create(_stream); return *this; }

/////////////////////////////////////////////////////////////////////////////
#endif