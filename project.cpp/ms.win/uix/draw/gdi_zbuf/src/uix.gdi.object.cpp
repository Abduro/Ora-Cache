/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Oct-2010 at 1:34:44am, GMT+3, Rostov-on-Don, Tuesday;
	This is Sfx Pack project shared UIX draw library GDI wrapper interface implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on on 7-Feb-2015 at 10:27:49pm, GMT+3, Taganrog, Saturday;
	Adopted to v15 on 28-May-2018 at 10:56:51p, UTC+7, Phuket, Rawai, Monday;
	Adopted to FakeGPS project on 24-Apr-2020 at 9:47:58p, UTC+7, Novosibirsk, Friday;
*/
#include "uix.gdi.object.h"

using namespace ex_ui::draw::memory;

/////////////////////////////////////////////////////////////////////////////

CBitmapInfo:: CBitmapInfo(void) { this->Reset(); }
CBitmapInfo:: CBitmapInfo(const CBitmapInfo& _ref) : CBitmapInfo() { *this = _ref; }
CBitmapInfo:: CBitmapInfo(const HBITMAP hBitmap, const UINT UID) : CBitmapInfo() { *this << hBitmap << UID; }
CBitmapInfo::~CBitmapInfo(void) { }

/////////////////////////////////////////////////////////////////////////////

HRESULT       CBitmapInfo::Attach (const HBITMAP hBitmap) { HRESULT hr_ = S_OK;

	if (CBitmapInfo::IsValid(hBitmap) == false)
		return (hr_ = E_INVALIDARG);

	hr_ = this->Reset();

	m_handle = hBitmap;
	// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getobject
	if (!::GetObject(hBitmap, sizeof(TBase), (LPVOID)(TBase*)this))
		hr_ = __DwordToHresult(ERROR_INVALID_DATATYPE);
	
	if (SUCCEEDED(hr_) && NULL == TBase::bmBits) {
		hr_ = __DwordToHresult(ERROR_ACCESS_DENIED); // TODO: error code must be reviewed;
	}
	return hr_;
}

HBITMAP       CBitmapInfo::Detach (void) { HBITMAP hTmp = m_handle; this->Reset(); return  hTmp; }

HRESULT       CBitmapInfo::Reset  (void) { HRESULT hr_ = S_OK;
#if (0)
	if (this->Is()) {
		// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-deleteobject
		const BOOL b_result = ::DeleteObject((HGDIOBJ)m_hBitmap);
		if (FALSE == b_result)
			hr_ = E_FAIL;
		else {
			m_hBitmap = NULL;
			::memset((void*)static_cast<BITMAP*>(this), 0, sizeof(BITMAP));
		}
	}
	else {
		m_hBitmap = NULL;
		::memset((void*)static_cast<BITMAP*>(this), 0, sizeof(BITMAP));
	}
#else
	m_UID    = 0   ;
	m_handle = NULL;
	::RtlZeroMemory((void*)static_cast<BITMAP*>(this), sizeof(BITMAP));
#endif
	return hr_;
}

/////////////////////////////////////////////////////////////////////////////
const
HBITMAP       CBitmapInfo::Handle(void) const { return m_handle; }
UINT          CBitmapInfo::ID    (void) const { return m_UID; }
bool          CBitmapInfo::Is    (void) const { return CBitmapInfo::IsValid(m_handle); }
BITMAPINFO    CBitmapInfo::Raw   (void) const {

	const DWORD n_size = static_cast<DWORD>(((TBase::bmWidth * TBase::bmBitsPixel + 31) / 32) * 4 * TBase::bmHeight);

	BITMAPINFO bmp_info = {
		{sizeof(BITMAPINFO), TBase::bmWidth, TBase::bmHeight, 1, TBase::bmBitsPixel, BI_RGB, n_size, 0, 0, 0, 0}, // header;
		0, 0, 0, 0 // quad;
	};

	return bmp_info;
}
HRESULT       CBitmapInfo::Size  (SIZE& size) const { HRESULT hr_ = S_OK;

	if (this->Is() == false)
		return (hr_ = __DwordToHresult(ERROR_INVALID_DATA));

	size.cx = ((BITMAP&)(*this)).bmWidth;
	size.cy = ((BITMAP&)(*this)).bmHeight;

	return hr_;
}

/////////////////////////////////////////////////////////////////////////////

CBitmapInfo&  CBitmapInfo::operator = (const CBitmapInfo& _ref) { *this << _ref.ID() << _ref.Handle(); return *this; }
CBitmapInfo&  CBitmapInfo::operator <<(const UINT _id) { this->m_UID = _id; return *this; }
CBitmapInfo&  CBitmapInfo::operator <<(const HBITMAP _handle) { this->Attach(_handle); return *this; }

/////////////////////////////////////////////////////////////////////////////

CBitmapInfo::operator const HBITMAP  (void) const { return m_handle; }
CBitmapInfo::operator const BITMAPINFO (void) const { return this->Raw(); }

/////////////////////////////////////////////////////////////////////////////

bool CBitmapInfo::IsValid(const HBITMAP _handle) {  return(_handle != NULL && OBJ_BITMAP == ::GetObjectType((HGDIOBJ)_handle)); }

/////////////////////////////////////////////////////////////////////////////

CDibSection:: CDibSection(void) { this->Reset(); }
CDibSection:: CDibSection(const HDC hDC, const SIZE& sz) : CDibSection() { this->Create(hDC, sz); }
CDibSection::~CDibSection(void) { if (this->Is()) { this->Destroy(); } }

/////////////////////////////////////////////////////////////////////////////

HRESULT CDibSection::Create (const HDC hDC, const SIZE& sz) { HRESULT hr_ = S_OK;
	if (NULL == hDC)
		return (hr_ = __DwordToHresult(ERROR_INVALID_HANDLE));

	if (1 > sz.cx || 1 > sz.cy)
		return (hr_ = E_INVALIDARG);

	if (this->Is())
		hr_ = this->Destroy();
	if (FAILED(hr_))
		return hr_;

	m_size = sz;

	BITMAPINFO bi = {{sizeof(BITMAPINFOHEADER), sz.cx, sz.cy, 1, (WORD)32, BI_RGB, 0, 0, 0, 0, 0}, 0, 0, 0, 0};

	m_handle = ::CreateDIBSection(hDC, &bi, DIB_RGB_COLORS, (void**)(&m_pData), NULL, 0);
	if (NULL == m_handle) {
		hr_ = __LastErrToHresult();
	}
	
	return hr_;
}

HRESULT CDibSection::Destroy(void) { HRESULT hr_ = S_OK;
	if (this->Is() == false)
		return (hr_ = __DwordToHresult(ERROR_INVALID_STATE));

	try {
		// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-deleteobject ;
		const BOOL b_result = ::DeleteObject((HGDIOBJ)m_handle);
		if (FALSE == b_result)
			hr_ = __DwordToHresult(ERROR_INVALID_HANDLE);  // frankly speaking, the handle may be okay, but is still selected by DC at this time;
	}
	catch (...) { hr_ = E_UNEXPECTED; }

	if (SUCCEEDED(hr_))
		this->Reset();

	return hr_;
}

HBITMAP CDibSection::Detach (void) { HBITMAP h_result = m_handle; this->Reset(); return h_result; }

HRESULT CDibSection::Reset  (void) { HRESULT hr_ = S_OK;

	if (this->Is()) {
		return (hr_ = __DwordToHresult(ERROR_INVALID_STATE) ); // object still exists; cannot clean the variables;
	}
	m_pData   = NULL;
	m_handle  = NULL;
	m_size.cx = m_size.cy = 0;

	return hr_;
}

/////////////////////////////////////////////////////////////////////////////

PCBYTE  CDibSection::Bits   (void) const { return m_pData; }

HBITMAP CDibSection::Handle (void) const { return (this->Is() ? m_handle : NULL); }
bool    CDibSection::Is     (void) const { return (m_handle && OBJ_BITMAP == ::GetObjectType(m_handle)); }
SIZE    CDibSection::Size   (void) const { return  m_size; }

/////////////////////////////////////////////////////////////////////////////

CDibSection&  CDibSection::operator = (const CDibSection& _ref) {
	// TODO: deleting may be made after checking the source section, otherwise, this bitmap (if any) will be lost;
	if (this->Is())
		this->Destroy();
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-copyimage
	this->m_handle = (HBITMAP)::CopyImage(_ref.Handle(), IMAGE_BITMAP, 0, 0, 0x0); // the size of the bitmap being created is set automatically;
	if (this->Is())
		this->m_size = _ref.Size();

	return *this;
}

/////////////////////////////////////////////////////////////////////////////

CDibSection::operator HBITMAP() const { return this->Handle(); }