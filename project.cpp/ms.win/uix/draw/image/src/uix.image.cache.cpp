/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Jul-2025 at 23:39:10.451, (UTC+4), Batumi, Friday;
	This is Ebo Pack generic 32-bits image cache interface implementation file;
*/
#include "uix.image.cache.h"

using namespace ex_ui::draw::images;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace images { namespace _impl {

#if (0)
	/*
		This is the simplified version of the implementation of loading PNG picture from a file;
		*important*: OleLoadPictureFile() does not work with png, jpeg and other format image types;
	*/
#include <olectl.h>

	class CPicture {
	public:
		 CPicture (void) : m_hBitmap(nullptr) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
		 CPicture (const CPicture&) = delete; CPicture (CPicture&&) = delete;
		~CPicture (void) { this->Delete(); }
	public:
		err_code Delete(void) {
			this->m_error <<__METHOD__<<__s_ok;

			if (nullptr == this->Handle())
				return this->Error();
			// the error may occur in case when the handle being deleted is selected by device context; but such case is not supposed to be;
			::DeleteObject((HGDIOBJ)this->m_hBitmap);

			this->m_hBitmap = nullptr;

			return this->Error();
		}

		TError&  Error (void) const { return this->m_error; }

		const HBITMAP  Handle (void) const { return this->m_hBitmap; }

		err_code Load  (_pc_sz _p_file_path) {
			_p_file_path;
			this->m_error <<__METHOD__<<__s_ok;

			if (nullptr == _p_file_path || 0 == ::_tcslen(_p_file_path))
				return this->m_error << __e_inv_arg;

			// https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathfileexistsa ;

			if (false == ::PathFileExists((_pc_sz)_p_file_path))
				this->m_error << (err_code) TErrCodes::ePath::eNoFile;

			// https://learn.microsoft.com/en-us/windows/win32/api/olectl/nf-olectl-oleloadpicturefile ;
			_variant_t v_path(_p_file_path);

			CComPtr<IDispatch> pDisp;

			this->m_error << ::OleLoadPictureFile(v_path, &pDisp);
			if (this->Error().Is())
				return this->Error();

			this->m_error << pDisp->QueryInterface(IID_IPicture, (void**)&this->m_pPicture);
			if (this->Error().Is())
				return this->Error();

			this->Delete();

			OLE_XSIZE_HIMETRIC cx = 0; this->m_error << this->m_pPicture->get_Width(&cx) ; if (this->Error().Is()) return this->Error();
			OLE_YSIZE_HIMETRIC cy = 0; this->m_error << this->m_pPicture->get_Height(&cy); if (this->Error().Is()) return this->Error();

			HDC hdc_desktop = ::GetDC(HWND_DESKTOP);
			const int ret_w = ::MulDiv(::GetDeviceCaps(hdc_desktop, LOGPIXELSX), (cx), 2540);
			const int ret_h = ::MulDiv(::GetDeviceCaps(hdc_desktop, LOGPIXELSY), (cy), 2540);

			HBITMAP hRezultBitmap = ::CreateCompatibleBitmap(hdc_desktop, ret_w, ret_h); // create compatible bitmap and DC ;
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

	private:
		CPicture& operator = (const CPicture&) = delete; CPicture& operator = (CPicture&&) = delete;
		CError m_error;
		CComPtr<IPicture> m_pPicture;
		HBITMAP m_hBitmap;  // the bitmap that is loaded from the file specified;
	};
#endif
}}}}
using namespace ex_ui::draw::images::_impl;

/////////////////////////////////////////////////////////////////////////////

CList:: CList (void) : m_size{0}, m_list(nullptr) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CList:: CList (const CList& _src) : CList() { *this = _src; }
CList::~CList (void) {

	if (this->Is_valid())
		this->Destroy();
}

/////////////////////////////////////////////////////////////////////////////

err_code  CList::Append  (const HBitmap _h_bitmap) {
	_h_bitmap;
	this->m_error << __METHOD__ << __s_ok;
	if (nullptr == _h_bitmap || false == CBitmapInfo::IsValid(_h_bitmap))
		return this->m_error << __e_inv_arg;

	TBmpHeader bmp_head = {0};

	this->m_error = CBmpHeader::Get(_h_bitmap, bmp_head);
	if (this->Error().Is())
		return this->Error();

	if (32 != bmp_head.biBitCount)
		return this->m_error << (err_code) TErrCodes::eData::eInvalid = _T("Bits per pixel value must be 32");

	if (this->Size().cx != bmp_head.biWidth || this->Size().cy != bmp_head.biHeight)
		return this->m_error << (err_code) TErrCodes::eExecute::eParameter = _T("Different sizes between the input bitmap and this list");
	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_add ;
	const int n_index = ::ImageList_Add(this->Handle(), _h_bitmap, nullptr);
	if (0 > n_index)
		this->m_error << __e_not_expect = _T("The bitmap cannot be added");

	return this->Error();
}

err_code  CList::Create (const t_size& _img_size, const uint16_t _n_count, const uint16_t _n_delta) {
	return this->Create (_img_size.cx & 0xff, _img_size.cy & 0xff, _n_count, _n_delta);
}

err_code  CList::Create (const uint16_t _n_width, const uint16_t _n_height, const uint16_t _n_count, const uint16_t _n_delta) {
	_n_width; _n_height; _n_count; _n_delta;
	this->m_error << __METHOD__ << __s_ok;

	if (0 == _n_width || 0 == _n_height)
		return this->m_error << __e_inv_arg = _T("Image size is invalid");

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eInited;
	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_create ;
	this->m_list = ::ImageList_Create(_n_width, _n_height, ILC_COLOR32, _n_count, _n_delta);
	if (nullptr == this->m_list)
		this->m_error.Last();
	else {
		this->m_list_id = (static_cast<dword>(_n_width) << 16) | static_cast<dword>(_n_height);
		this->m_size = {_n_width, _n_height};
#if defined (_DEBUG)
		t_size sz_test = { this->m_list_id >> 16, this->m_list_id & 0xff };
		if (!!sz_test.cx && !!sz_test.cy) {
			const bool b_result = false;
			b_result != b_result;
		}
#endif
	}

	return this->Error();
}

err_code  CList::Destroy(void) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid() == false)
		return this->m_error << __e_not_inited;
	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_destroy ;
	if (false == ::ImageList_Destroy(this->Handle()))
		this->m_error.Last();
	else
		this->Handle() = nullptr;

	return this->Error();
}

err_code  CList::CopyTo (HImgList& _h_dest) const {
	_h_dest;
	this->m_error << __METHOD__ << __s_ok;

	if (!!_h_dest)
		return this->m_error << __e_inv_arg = _T("Input image list handle is already created");

	if (this->Is_valid() == false)
		return this->m_error << __e_not_inited;
	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_duplicate ;
	_h_dest = ::ImageList_Duplicate(this->Handle());
	if (nullptr == _h_dest)
		this->m_error.Last();

	return this->Error();
}

uint16_t  CList::Count  (void) const {
	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_getimagecount ;
	if (this->Is_valid() == false)
		return 0;
	else
		return static_cast<uint16_t>(::ImageList_GetImageCount(this->Handle()));
}

TError&   CList::Error  (void) const { return m_error; }
bool      CList::Is_valid (void) const { return !!this->Handle(); }
dword     CList::Id  (void) const { return this->m_list_id; }
const
HImgList& CList::Handle (void) const { return this->m_list; }
HImgList& CList::Handle (void)       { return this->m_list; }
#if defined(_DEBUG)
CString   CList::Print  (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {id=%u;handle=%s;count=%u;size=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {id=%u;handle=%s;count=%u;size=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("id=%u;handle=%s;count=%u;size=%s;valid=%s");

	CString cs_list  = TStringEx().__address_of(this->Handle(), nullptr);
	CString cs_size  = TStringEx().Format (_T("[w|h:%d|%d](px)"), this->Size().cx,  this->Size().cy);
	CString cs_valid = TStringEx().Bool (this->Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		this->Id(), (_pc_sz) cs_list, this->Count(), (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n,(_pc_sz)__CLASS__,
		this->Id(), (_pc_sz) cs_list, this->Count(), (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r,
		this->Id(), (_pc_sz) cs_list, this->Count(), (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif
const
t_size&   CList::Size (void) const { return this->m_size; }

/////////////////////////////////////////////////////////////////////////////

CList&    CList::operator = (const CList& _src) { _src; return *this; }

/////////////////////////////////////////////////////////////////////////////

CCache:: CCache (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CCache:: CCache (const CCache& _src) : CCache() { *this = _src; }
CCache::~CCache (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  CCache::Error (void) const { return this->m_error; }

/////////////////////////////////////////////////////////////////////////////

CCache&  CCache::operator = (const CCache&) { return *this; }