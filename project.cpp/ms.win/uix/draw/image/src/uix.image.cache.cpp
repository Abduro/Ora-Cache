/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Jul-2025 at 23:39:10.451, (UTC+4), Batumi, Friday;
	This is Ebo Pack generic 32-bits image cache interface implementation file;
*/
#include "uix.image.cache.h"
#include "uix.image.prov.h"

using namespace ex_ui::draw::images;

#include "shell.fs.folder.h"

using namespace shared::user_32::ntfs;

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

	CList&  GetFakeList (void) {
		static CList fake_lst; return fake_lst;
	}
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

err_code  CList::Append (const HBitmap _h_bitmap) {
	_h_bitmap;
	this->m_error << __METHOD__ << __s_ok;
#if (0)
	if (this->Is_valid() == false)
		return this->m_error << __e_not_inited;
#endif
	if (nullptr == _h_bitmap || false == CBitmapInfo::IsValid(_h_bitmap))
		return this->m_error << __e_inv_arg;

	TBmpHeader bmp_head = {0};

	this->m_error = CBmpHeader::Get(_h_bitmap, bmp_head);
	if (this->Error().Is())
		return this->Error();

	if (32 != bmp_head.biBitCount)
		return this->m_error << (err_code) TErrCodes::eData::eInvalid = _T("Bits per pixel value must be 32");

	if (this->Is_valid() == false) {
		if (__failed(this->Create(static_cast<uint16_t>(bmp_head.biWidth), static_cast<uint16_t>(bmp_head.biHeight))))
			return this->Error();
	}

	if (this->Size().cx != bmp_head.biWidth || this->Size().cy != bmp_head.biHeight)
		return this->m_error << (err_code) TErrCodes::eExecute::eParameter = _T("Different sizes between the input bitmap and this list");
	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_add ;
	const int n_index = ::ImageList_Add(this->Handle(), _h_bitmap, nullptr);
	if (0 > n_index)
		this->m_error << __e_not_expect = _T("The bitmap cannot be added");

	return this->Error();
}

err_code  CList::Append (_pc_sz _p_path, const TImgFmt _e_format) {
	_p_path; _e_format;
	this->m_error << __METHOD__ << __s_ok;

	CDataProvider prov_;

	if (__failed(prov_.Load(_p_path, _e_format))) {
		return this->m_error = prov_.Error();
	}

	if (this->Is_valid() == false) {
		if (__failed(this->Create(prov_.Result().Size())))
			return this->Error();
	}

	this->Append (prov_.Result().Handle());

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
		this->m_size = {_n_width, _n_height};
		this->m_list_id = CListId::ToDword(this->m_size);
#if defined (_DEBUG)
		t_size sz_test  = CListId::ToSize (this->m_list_id);
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

err_code  CList::Draw (const uint16_t _n_index, const HDC _h_dc, const int16_t _n_x, const int16_t _n_y, const uint32_t _u_mode) {
	_n_index; _h_dc; _n_x; _n_y; _u_mode;
	err_code n_result = __s_ok;

	if (_n_index >= this->Count()) return n_result = this->m_error <<__METHOD__<< __e_index;
	if (this->Is_valid() == false) return n_result = this->m_error <<__METHOD__<<__e_not_inited;
	if (0 == _h_dc) return n_result = this->m_error <<__METHOD__<< (err_code) TErrCodes::eObject::eHandle;

	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_draw ;
	if (false == !!::ImageList_Draw(this->Handle(), _n_index, _h_dc, _n_x, _n_y, _u_mode))
		n_result = (this->m_error <<__METHOD__).Last();

	return n_result;
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
	else {
		int32_t n_count =  ::ImageList_GetImageCount(this->Handle());
		return  n_count < 0 ? 0 : static_cast<uint16_t>(n_count);
	}
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

CList&    CList::operator = (const CList& _src) {
	if (this->Is_valid())
		this->Destroy();

	err_code n_result = __e_not_inited;

	if (_src.Is_valid())
		n_result = _src.CopyTo(this->Handle());

	this->m_error << n_result;

	this->m_list_id = _src.Id();
	this->m_size = _src.Size();

	return *this;
}

/////////////////////////////////////////////////////////////////////////////

CCache:: CCache (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CCache:: CCache (const CCache& _src) : CCache() { *this = _src; }
CCache::~CCache (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CCache::Append (_pc_sz _p_file_dir, const TImgFmt _e_format) {
	_p_file_dir; _e_format;
	this->m_error << __METHOD__ << __s_ok;

	CFolder target;

	if (__failed(target.Path(_p_file_dir)))
		return this->m_error = target.Error();

	if (__failed(target.EnumItems(TImgType().Ext(_e_format))))
		return this->m_error = target.Error();

	CDataProvider prov_;

	TFileList files = target.Files();
	TSubDirs  subdirs = target.SubDirs();

	for (size_t i_ = 0; i_ < files.size(); i_++) {
		// this is some sort of 'normalizing' paths of image files, must be reviewed;
		CString& cs_file = files.at(i_);
		cs_file = TString().Format(_T("%s%s"), target.Path(), (_pc_sz) cs_file);

		if (__failed(prov_.Load((_pc_sz) cs_file, _e_format))) {
			this->m_error = prov_.Error(); break;
		}

		const CResult& result = prov_.Result();
		TRawLists::iterator found_ = this->m_lists.find(CListId::ToDword(result.Size()));

		if (this->m_lists.end() == found_) {
			CList list_;
			if (__failed(list_.Create(result.Size()))) {
				return this->m_error = list_.Error();
			}
			else
				this->m_lists.insert(::std::make_pair(/*CListId::ToDword(result.Size())*/list_.Id(), list_));

			found_ = this->m_lists.find(CListId::ToDword(result.Size())); // once again; it is not good approach, but is okay for the time being;
		}
		if (this->m_lists.end() == found_) {
			return this->m_error << __e_not_expect;
		}

		if (__failed(found_->second.Append(result.Handle()))) { // the image list makes a copy of the image being inserted;
			return this->m_error = found_->second.Error();
		}
	}
	// no subfolders this time; this must be done by CFolder class itself;
	for (size_t i_ = 0; i_ < subdirs.size(); i_++) {
	}

	return this->Error();
}

err_code CCache::Append(const t_size& _size, const uint16_t _n_count, const uint16_t _n_delta) {
	_size;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Has(_size))
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	CList list;
	if (__failed(list.Create(_size, _n_count, _n_delta)))
		return this->m_error = list.Error();
	try {
		this->m_lists.insert(::std::make_pair(/*CListId::ToDword(_size)*/list.Id(), list));
	}
	catch (const ::std::bad_alloc&) {
		this->m_error << __e_no_memory;
	}

	return this->Error();
}

TError&  CCache::Error (void) const { return this->m_error; }
// https://en.cppreference.com/w/cpp/container/map/contains.html ;
const bool CCache::Has (const dword _n_id) const { return (!!_n_id && this->m_lists.find(_n_id) != this->m_lists.end()); }
const bool CCache::Has (const t_size& _size) const { return this->Has(CListId::ToDword(_size)); }
const
CList&  CCache::List (const dword _n_id) const {
	_n_id;
	this->m_error <<__METHOD__<<__s_ok;

	TRawLists::const_iterator found_ = this->m_lists.find(_n_id);
	if (found_ == this->m_lists.end()) {
		this->m_error << (err_code) TErrCodes::eObject::eNotFound;
		return GetFakeList();
	}
	else {
		return found_->second;
	}
}

CList&  CCache::List (const dword _n_id) {
	_n_id;
	this->m_error <<__METHOD__<<__s_ok;

	TRawLists::iterator found_ = this->m_lists.find(_n_id);
	if (found_ == this->m_lists.end()) {
		this->m_error << (err_code) TErrCodes::eObject::eNotFound;
		return GetFakeList();
	}
	else {
		return found_->second;
	}
}

const
CList&  CCache::List (const t_size& _size) const { return this->List(CListId::ToDword(_size)); }
CList&  CCache::List (const t_size& _size)       { return this->List(CListId::ToDword(_size)); }

#if defined(_DEBUG)
CString  CCache::Print (const e_print _e_opt/* = e_print::e_all*/, _pc_sz _p_pfx/* = _T("\t\t")*/, _pc_sz _p_sfx/* = _T("\n")*/) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%slists:%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {lists=%s}");
	static _pc_sz pc_sz_pat_r = _T("lists=%s");

	CString cs_lists;

	for (TRawLists::const_iterator iter_ = this->m_lists.begin(); iter_ != this->m_lists.end(); ++iter_) {
		const CList& list_ = iter_->second;
		cs_lists += _p_sfx;
		cs_lists += _p_pfx;
		cs_lists += list_.Print(e_print::e_req);
	}
	if (cs_lists.IsEmpty() == true) {
		cs_lists += _p_sfx;
		cs_lists += _p_pfx;
		cs_lists += _T("#no_list");
	}
	
	CString cs_out;

#if (1)
	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_lists, _p_sfx, _p_pfx);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n,(_pc_sz)__CLASS__,
		(_pc_sz) cs_lists);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r,
		(_pc_sz) cs_lists);
	}
#endif

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CCache&  CCache::operator = (const CCache&) { return *this; }