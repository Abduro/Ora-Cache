/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Oct-2010 at 1:34:44am, GMT+3, Rostov-on-Don, Tuesday;
	This is Sfx Pack project shared UIX draw library GDI wrapper interface implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on on 7-Feb-2015 at 10:27:49pm, GMT+3, Taganrog, Saturday;
	Adopted to v15 on 28-May-2018 at 10:56:51p, UTC+7, Phuket, Rawai, Monday;
	Adopted to FakeGPS project on 24-Apr-2020 at 9:47:58p, UTC+7, Novosibirsk, Friday;
*/
#include "uix.img.bitmap.h"

using namespace ex_ui::draw::bitmaps;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace bitmaps { namespace _impl {
#if defined(_DEBUG)
	class CBmp_Spec {
	public:
		CBmp_Spec (void) = delete; CBmp_Spec (const CBmp_Spec&) = delete; CBmp_Spec (CBmp_Spec&&) = delete;
		CBmp_Spec (const TBmpHeader& _header) : m_header(_header) {} ~CBmp_Spec (void) = default;

	public:
		// https://learn.microsoft.com/en-us/windows/win32/api/strmif/ns-strmif-am_media_type ; deprecated;
		// https://learn.microsoft.com/en-us/windows/win32/directshow/video-subtypes ;
		// https://learn.microsoft.com/en-us/windows/win32/directshow/directx-video-acceleration-video-subtypes ;
		_pc_sz Compress (void) {
			switch (this->m_header.biCompression) {
			case BI_BITFIELDS: this->cs_out = _T("bitfields"); break;
			case BI_JPEG     : this->cs_out = _T("jpeg"); break;
			case BI_PNG      : this->cs_out = _T("rgb" ); break;
			case BI_RGB      : this->cs_out = _T("rgb" ); break;
			case BI_RLE4     : this->cs_out = _T("rle4"); break;
			case BI_RLE8     : this->cs_out = _T("rle8"); break;
			default:
				this->cs_out = _T("#video_4cc");
			}
			return this->cs_out.GetString();
		}

	private:
		CBmp_Spec& operator = (const CBmp_Spec&) = delete;
		CBmp_Spec& operator = (CBmp_Spec&&) = delete;

	private:
		const TBmpHeader& m_header;
		CString cs_out;
	};
#endif
}}}}

using namespace ex_ui::draw::bitmaps::_impl;
/////////////////////////////////////////////////////////////////////////////
#define hwnd_desctop HWND_DESKTOP
err_code CBmpHeader::Get (const HBitmap& _from, TBmpHeader& _to) {
	_from; _to;
	err_code n_result = __s_ok;
	if (nullptr == _from || false == CBitmapInfo::IsValid(_from))
		return n_result = __e_inv_arg;

	TBmpInfo bmp_info = {0};
	bmp_info.bmiHeader.biSize = sizeof(TBmpHeader);

	const HDC h_screen = ::GetDC(hwnd_desctop);
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getdibits ;
	if (false == !!::GetDIBits(h_screen, _from, 0, 1, nullptr, &bmp_info, DIB_RGB_COLORS))
		n_result = __LastErrToHresult();
	else { // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/memcpy-s-wmemcpy-s ;
		n_result = ::memcpy_s(&_to, sizeof(TBmpHeader), &bmp_info.bmiHeader, sizeof(TBmpHeader));
		if (!!n_result)
			n_result = __e_no_memory;
	}
	::ReleaseDC(hwnd_desctop, h_screen);

	return n_result;
}

#if defined(_DEBUG)
CString  CBmpHeader::Print (const TBmpHeader& _header, const e_print _e_opt) {
	_header; _e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {bits=%d(bpp);format=%s;size=%s;res=%s;indices=%u}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {bits=%d(bpp);format=%s;size=%s;res=%s;indices=%u}");
	static _pc_sz pc_sz_pat_r = _T("bits=%d(bpp);format=%s;size=%s;res=%s;indices=%u");

	CString cs_res  = TStringEx().Format (_T("[horz|vert:%d|%d](px/m)"), _header.biXPelsPerMeter, _header.biYPelsPerMeter);
	CString cs_size = TStringEx().Format (_T("[w|h:%d|%d](px)"), _header.biWidth, _header.biHeight);
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_header.biBitCount, CBmp_Spec(_header).Compress(), (_pc_sz) cs_size, (_pc_sz) cs_res, _header.biClrUsed);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		_header.biBitCount, CBmp_Spec(_header).Compress(), (_pc_sz) cs_size, (_pc_sz) cs_res, _header.biClrUsed);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r,
		_header.biBitCount, CBmp_Spec(_header).Compress(), (_pc_sz) cs_size, (_pc_sz) cs_res, _header.biClrUsed);
	}
	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CBitmapInfo:: CBitmapInfo(void) { this->Reset(); }
CBitmapInfo:: CBitmapInfo(const CBitmapInfo& _ref) : CBitmapInfo() { *this = _ref; }
CBitmapInfo:: CBitmapInfo(const HBITMAP hBitmap, const UINT UID) : CBitmapInfo() { *this << hBitmap << UID; }
CBitmapInfo::~CBitmapInfo(void) { }

/////////////////////////////////////////////////////////////////////////////

err_code  CBitmapInfo::Attach (const HBitmap hBitmap) {
	hBitmap;
	err_code n_result = __s_ok;

	if (CBitmapInfo::IsValid(hBitmap) == false)
		return (n_result = __e_inv_arg);

	n_result = this->Reset();

	m_handle = hBitmap;
	// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getobject
	if (!::GetObject(hBitmap, sizeof(TBase), (LPVOID)(TBase*)this))
		n_result = (err_code) TErrCodes::eData::eType;
	
	if (__succeeded(n_result) && nullptr == TBase::bmBits) {
		n_result = (err_code) TErrCodes::eAccess::eDenied; // TODO: error code must be reviewed;
	}
	return n_result;
}

HBitmap   CBitmapInfo::Detach (void) { HBitmap hTmp = m_handle; this->Reset(); return hTmp; }

err_code  CBitmapInfo::Reset  (void) {

	err_code n_result = __s_ok;

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
	m_UID    = 0;
	m_handle = nullptr;
	::RtlZeroMemory((void*)static_cast<TBitmap*>(this), sizeof(TBitmap));
#endif
	return n_result;
}

/////////////////////////////////////////////////////////////////////////////
const
HBitmap       CBitmapInfo::Handle(void) const { return m_handle; }
UINT          CBitmapInfo::ID    (void) const { return m_UID; }
bool          CBitmapInfo::Is    (void) const { return CBitmapInfo::IsValid(m_handle); }
TBmpInfo      CBitmapInfo::Raw   (void) const {

	const dword n_size = static_cast<dword>(((TBase::bmWidth * TBase::bmBitsPixel + 31) / 32) * 4 * TBase::bmHeight);

	TBmpInfo bmp_info = {
		{sizeof(TBmpInfo), TBase::bmWidth, TBase::bmHeight, 1, TBase::bmBitsPixel, BI_RGB, n_size, 0, 0, 0, 0}, // header;
		0, 0, 0, 0 // quad;
	};

	return bmp_info;
}

err_code      CBitmapInfo::Size  (t_size& size) const {
	size;
	err_code n_result =  __s_ok;

	if (this->Is() == false)
		return n_result = (err_code) TErrCodes::eData::eInvalid;

	size.cx = ((TBitmap&)(*this)).bmWidth;
	size.cy = ((TBitmap&)(*this)).bmHeight;

	return n_result;
}

#if defined(_DEBUG)
CString  CBitmapInfo::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {bits=%d(bpp);size=%s;scan_line=%u(bytes)}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {bits=%d(bpp);size=%s;scan_line=%u(bytes)}");
	static _pc_sz pc_sz_pat_r = _T("bits=%d(bpp);size=%s;scan_line=%u(bytes)");

	CString cs_size = TStringEx().Format (_T("[w|h:%d|%d](px)"), TBase::bmWidth, TBase::bmHeight);
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		TBase::bmBitsPixel, (_pc_sz) cs_size, TBase::bmWidthBytes);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		TBase::bmBitsPixel, (_pc_sz) cs_size, TBase::bmWidthBytes);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r,
		TBase::bmBitsPixel, (_pc_sz) cs_size, TBase::bmWidthBytes);
	}
	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CBitmapInfo&  CBitmapInfo::operator = (const CBitmapInfo& _ref) { *this << _ref.ID() << _ref.Handle(); return *this; }
CBitmapInfo&  CBitmapInfo::operator <<(const UINT _id) { this->m_UID = _id; return *this; }
CBitmapInfo&  CBitmapInfo::operator <<(const HBITMAP _handle) { this->Attach(_handle); return *this; }

/////////////////////////////////////////////////////////////////////////////

CBitmapInfo::operator const HBitmap  (void) const { return m_handle; }
CBitmapInfo::operator const TBmpInfo (void) const { return this->Raw(); }

/////////////////////////////////////////////////////////////////////////////
// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getobject ;
bool CBitmapInfo::IsValid(const HBitmap _handle) {  return(_handle != NULL && OBJ_BITMAP == ::GetObjectType((HGDIOBJ)_handle)); }

/////////////////////////////////////////////////////////////////////////////

CDibSection:: CDibSection (void) {
	this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;
	this->Reset();
}
CDibSection:: CDibSection (const CDibSection& _src) : CDibSection() { *this = _src; }
CDibSection:: CDibSection (const HDC hDC, const SIZE& sz) : CDibSection() { this->Create(hDC, sz); }
CDibSection::~CDibSection (void) { if (this->Is()) { this->Destroy(); } }

/////////////////////////////////////////////////////////////////////////////

err_code CDibSection::Create (const HDC hDC, const SIZE& sz) {

	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == hDC)
		return this->m_error << (err_code) TErrCodes::eObject::eHandle;

	if (1 > sz.cx || 1 > sz.cy)
		return this->m_error << __e_inv_arg;

	if (this->Is())
		this->Destroy();

	if (this->Error())
		return this->Error();

	m_size = sz;

	BITMAPINFO bi = {{sizeof(BITMAPINFOHEADER), sz.cx, sz.cy, 1, (WORD)32, BI_RGB, 0, 0, 0, 0, 0}, 0, 0, 0, 0};
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createdibsection ;
	m_handle = ::CreateDIBSection(hDC, &bi, DIB_RGB_COLORS, (void**)(&m_pData), NULL, 0);
	if (nullptr == m_handle) {
		this->m_error.Last();
	}
	
	return this->Error();
}

err_code CDibSection::Destroy(void) {

	this->m_error << __METHOD__ << __s_ok;

	if (this->Is() == false)
		return this->m_error << (err_code) TErrCodes::eExecute::eState;

	try {
		// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-deleteobject ;
		const BOOL b_result = ::DeleteObject((HGDIOBJ)m_handle);
		if (FALSE == b_result)
			this->m_error.Last();  // frankly speaking, the handle may be okay, but is still selected by DC at this time;
	}
	catch (...) { this->m_error << __e_not_expect; }

	if (false == this->Error())
		this->Reset();

	return this->Error();
}

HBitmap  CDibSection::Detach (void) { HBITMAP h_result = m_handle; this->Reset(); return h_result; }

err_code CDibSection::Reset  (void) {

	this->m_error << __METHOD__ << __s_ok;

	if (this->Is()) {
		return this->m_error << (err_code) TErrCodes::eExecute::eState; // object still exists; cannot clean the variables;
	}

	m_pData   = nullptr;
	m_handle  = nullptr;
	m_size.cx = m_size.cy = 0;

	this->m_error << __e_not_inited;

	return __s_ok;
}

/////////////////////////////////////////////////////////////////////////////

_pc_byte CDibSection::Bits   (void) const { return m_pData; }

TError&  CDibSection::Error  (void) const { return this->m_error; }

HBitmap  CDibSection::Handle (void) const { return (this->Is() ? m_handle : nullptr); }
bool     CDibSection::Is     (void) const { return (m_handle && OBJ_BITMAP == ::GetObjectType(m_handle)); }
t_size   CDibSection::Size   (void) const { return  m_size; }

#if defined(_DEBUG)
CString CDibSection::Print  (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {handle=%s;size=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {handle=%s;size=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("handle=%s;size=%s;valid=%s");

	CString cs_handle = TStringEx().__address_of(this->Handle(), _T("0x%08x"));
	CString cs_size   = TStringEx().Format(_T("[w|h:%d|%d](px)"), this->Size().cx, this->Size().cy);
	CString cs_valid  = TStringEx().Bool (this->Is());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format ( pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, 
		(_pc_sz) cs_handle, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format ( pc_sz_pat_n, (_pc_sz)__CLASS__, 
		(_pc_sz) cs_handle, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format ( pc_sz_pat_r,
		(_pc_sz) cs_handle, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

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

CDibSection::operator HBitmap() const { return this->Handle(); }