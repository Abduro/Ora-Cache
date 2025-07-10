/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apt-2022 at 18:16:52.260, UTC+7, Novosibirsk, Thursday;
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

CPicture:: CPicture (void) : m_hBitmap(nullptr) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CPicture:: CPicture (const CPicture& _ref) : CPicture() { *this = _ref; }
CPicture::~CPicture (void) { this->Delete(); }

/////////////////////////////////////////////////////////////////////////////

err_code   CPicture::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == this->Handle())
		return this->Error();
	// the error may occur in case when the handle being deleted is selected by device context; but such case is not supposed to be;
	::DeleteObject((HGDIOBJ)this->m_hBitmap);

	this->m_hBitmap = nullptr;

	return this->Error();
}

TError&    CPicture::Error  (void) const { return this->m_error; }
const
HBITMAP    CPicture::Handle (void) const { return this->m_hBitmap; }

bool       CPicture::Is_valid (void) const { return this->Handle() != nullptr; }

err_code   CPicture::Load   (_pc_sz _p_file_path) {
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
	if (this->Error().Is())
		return this->Error();

	this->m_error << p_disp->QueryInterface(IID_IPicture, (void**)&this->m_pPicture);
	if (this->Error().Is())
		return this->Error();

	OLE_XSIZE_HIMETRIC cx = 0; this->m_error << this->m_pPicture->get_Width(&cx) ; if (this->Error().Is()) return this->Error();
	OLE_YSIZE_HIMETRIC cy = 0; this->m_error << this->m_pPicture->get_Height(&cy); if (this->Error().Is()) return this->Error();

	HDC hdc_desktop = ::GetDC(HWND_DESKTOP);
	const int ret_w = ::MulDiv(::GetDeviceCaps(hdc_desktop, LOGPIXELSX), (cx), 2540);
	const int ret_h = ::MulDiv(::GetDeviceCaps(hdc_desktop, LOGPIXELSY), (cy), 2540);

	HBITMAP hRezultBitmap = ::CreateCompatibleBitmap(hdc_desktop, ret_w, ret_h);
	HDC hBitmapDC = ::CreateCompatibleDC(hdc_desktop);

	if (hRezultBitmap && hBitmapDC) {
		HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hBitmapDC, hRezultBitmap);
		// https://docs.microsoft.com/en-us/windows/win32/api/ocidl/nf-ocidl-ipicture-render ;
		this->m_error << this->m_pPicture->Render(hBitmapDC, 0, 0, ret_w, ret_h, 0, cy, cx, -cy, 0);

		::SelectObject(hBitmapDC, hOldBitmap);
		::ReleaseDC(HWND_DESKTOP, hBitmapDC );
	}
	else
		this->m_error.Last();

	::ReleaseDC(HWND_DESKTOP, hdc_desktop); hdc_desktop = nullptr;

	if (this->Error().Is() == false) {
		this->m_hBitmap = hRezultBitmap; hRezultBitmap = nullptr;
	}
	else if (!!hRezultBitmap) {
		::DeleteObject((HGDIOBJ) hRezultBitmap); hRezultBitmap = nullptr; // tries to delete bitmap handle;
	}

	return this->Error();
}

#if defined(_DEBUG)
CString  CPicture::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {bits=%d(bpp);size=%s;scan_line=%u(bytes)}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {bits=%d(bpp);size=%s;scan_line=%u(bytes)}");
	static _pc_sz pc_sz_pat_r = _T("bits=%d(bpp);size=%s;scan_line=%u(bytes)");

	CString cs_size = TStringEx().Format (_T("[w|h:%d|%d](px)"), this->Size().cx, this->Size().cy);
	CString cs_out;
#if (0)
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		TBase::bmBitsPixel, (_pc_sz) cs_size, TBase::bmWidthBytes);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		TBase::bmBitsPixel, (_pc_sz) cs_size, TBase::bmWidthBytes);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r,
		TBase::bmBitsPixel, (_pc_sz) cs_size, TBase::bmWidthBytes);
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

err_code   CPicture::ToBitmap (HBITMAP& _in_out) const {
	_in_out;
	this->m_error << __METHOD__ << __s_ok;

	if (_in_out)
		return this->m_error << (err_code)TErrCodes::eObject::eInited = _T("Input handle must be nullptr");

	if (this->Is_valid() == false)
		return this->m_error << __e_not_inited;

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CPicture&  CPicture::operator = (const CPicture& _src) { *this << _src.Ptr(); return *this; }
CPicture&  CPicture::operator <<(const TPicturePtr& _ptr) { this->Ptr() = _ptr; return *this; }

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