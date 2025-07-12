/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2022 at 18:16:52.260, UTC+7, Novosibirsk, Thursday;
	This is a picture related interfaces' implementation file; [this declaration is made within 'Smart Diagram' project of ARQA Technologies]
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack image wrappers' project on 09-Jul-2025 at 13:30:43.876, UTC+4, Batumi, Wednesday;
*/
#include "uix.picture.h"

using namespace ex_ui::draw::images;

namespace ex_ui { namespace draw { namespace images { namespace _impl { /*void __warning_lnk_4221 (void) {}*/


}}}}

using namespace ex_ui::draw::images::_impl;

/////////////////////////////////////////////////////////////////////////////

CPicture:: CPicture (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CPicture:: CPicture (const CPicture& _ref) : CPicture() { *this = _ref; }
CPicture::~CPicture (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&    CPicture::Error  (void) const { return this->m_error; }

uint32_t   CPicture::Height (void) const {
	this->m_error <<__METHOD__<<__s_ok;
	if (this->Is_valid() == false) {
		this->m_error << __e_not_inited;
		return 0;
	}
	else {
		// https://learn.microsoft.com/en-us/windows/win32/api/ocidl/nf-ocidl-ipicture-get_height ;
		OLE_YSIZE_HIMETRIC n_height = 0;
		this->m_error << this->m_pPicture->get_Height(&n_height);
		return static_cast<uint32_t>(::abs(n_height));
	}
}

bool       CPicture::Is_valid (void) const { return this->Ptr() != nullptr; }

err_code   CPicture::Load (_pc_sz _p_file_path) {
	_p_file_path;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eInited;

	if (nullptr == _p_file_path || 0 == ::_tcslen(_p_file_path))
		return this->m_error << __e_inv_arg;

	// https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathfileexistsa ;

	if (false == ::PathFileExists((_pc_sz)_p_file_path))
		this->m_error << (err_code) TErrCodes::ePath::eNoFile;

	// https://learn.microsoft.com/en-us/windows/win32/api/olectl/nf-olectl-oleloadpicturefile ;
	_variant_t v_path(_p_file_path);

	CComPtr<IDispatch> p_disp;

	this->m_error << ::OleLoadPictureFile(v_path, &p_disp);
	if (this->Error().Is()) {
		this->m_error  = _T("Invalid picture (CTL_E_INVALIDPICTURE)");
		return this->Error();
	}

	this->m_error << p_disp->QueryInterface(IID_IPicture, (void**)&this->m_pPicture);
	
	return this->Error();
}

#if defined(_DEBUG)
CString  CPicture::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {picture=%s;size=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {picture=%s;size=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("picture=%s;size=%s;valid=%s");

	CString cs_picture = TStringEx().__address_of(this->Ptr(), _T("0x%08x"));
	CString cs_size    = TStringEx().Format (_T("[w|h:%u|%u](px)"), this->Width(), this->Height());
	CString cs_valid   = TStringEx().Bool(this->Is_valid());
	CString cs_out;
#if (1)
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		(_pc_sz) cs_picture, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz) cs_picture, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r,
		(_pc_sz) cs_picture, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}
#endif
	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

const
TPicturePtr&  CPicture::Ptr (void) const { return this->m_pPicture; }
TPicturePtr&  CPicture::Ptr (void)       { return this->m_pPicture; }

t_size     CPicture::Size (void) const {
	return t_size{static_cast<long>(this->Width()), static_cast<long>(this->Height())};
}

err_code   CPicture::ToBitmap (HBITMAP& _in_out) const {
	_in_out;
	this->m_error << __METHOD__ << __s_ok;

	if (_in_out)
		return this->m_error << (err_code)TErrCodes::eObject::eInited = _T("Input handle must be nullptr");

	if (this->Is_valid() == false)
		return this->m_error << __e_not_inited;

	const uint32_t n_height = this->Height(); if (this->Error().Is()) return this->Error();
	const uint32_t n_width  = this->Width() ; if (this->Error().Is()) return this->Error();

	HDC hdc_desktop = ::GetDC(HWND_DESKTOP);
	const int ret_w = ::MulDiv(::GetDeviceCaps(hdc_desktop, LOGPIXELSX), n_width , 2540);
	const int ret_h = ::MulDiv(::GetDeviceCaps(hdc_desktop, LOGPIXELSY), n_height, 2540);

	HBITMAP h_dsk_bmp = ::CreateCompatibleBitmap(hdc_desktop, ret_w, ret_h);
	HDC h_dsk_dev_ctx = ::CreateCompatibleDC(hdc_desktop);

	if (h_dsk_bmp && h_dsk_dev_ctx) {
		HBITMAP h_prev_bmp = (HBITMAP)::SelectObject(h_dsk_dev_ctx, h_dsk_bmp);
		// https://docs.microsoft.com/en-us/windows/win32/api/ocidl/nf-ocidl-ipicture-render ;
		this->m_error << this->m_pPicture->Render(h_dsk_dev_ctx, 0, 0, ret_w, ret_h, 0, 0,  n_width, n_height, nullptr);

		::SelectObject(h_dsk_dev_ctx, h_prev_bmp);
		::ReleaseDC(HWND_DESKTOP , h_dsk_dev_ctx);
	}
	else
		this->m_error.Last();

	::ReleaseDC(HWND_DESKTOP, hdc_desktop); hdc_desktop = nullptr;

	if (this->Error().Is() == false) {
		_in_out = h_dsk_bmp; h_dsk_bmp = nullptr;
	}
	else if (!!h_dsk_bmp) {
		::DeleteObject((HGDIOBJ) h_dsk_bmp); h_dsk_bmp = nullptr; // tries to delete bitmap handle;
	}

	return this->Error();
}

uint32_t   CPicture::Width (void) const {
	this->m_error <<__METHOD__<<__s_ok;
	if (this->Is_valid() == false) {
		this->m_error << __e_not_inited;
		return 0;
	}
	else {
		// https://learn.microsoft.com/en-us/windows/win32/api/ocidl/nf-ocidl-ipicture-get_width ;
		OLE_XSIZE_HIMETRIC n_width = 0;
		this->m_error << this->m_pPicture->get_Width(&n_width);
		return static_cast<uint32_t>(::abs(n_width));
	}
}

/////////////////////////////////////////////////////////////////////////////

CPicture&  CPicture::operator = (const CPicture& _src) { *this << _src.Ptr(); return *this; }
CPicture&  CPicture::operator <<(const TPicturePtr& _ptr) { this->Ptr() = _ptr; return *this; }
const
CPicture&  CPicture::operator >>(HBITMAP& _in_out) const { this->ToBitmap(_in_out); return *this; }

#if (0)
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

HRESULT    CPicture::ToBitmap(HBITMAP& _in_out) const
{
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


CPicture&  CPicture::operator <<(const LPSTREAM _stream) { this->Create(_stream); return *this; }

/////////////////////////////////////////////////////////////////////////////
#endif