/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Jul-2025 at 23:39:10.451, (UTC+4), Batumi, Friday;
	This is Ebo Pack generic 32-bits image cache interface implementation file;
*/
#include "uix.img.cache.h"

using namespace ex_ui::draw::images;

/////////////////////////////////////////////////////////////////////////////

CList:: CList (void) : m_size{0}, m_list(nullptr) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CList:: CList (const CList& _src) : CList() { *this = _src; }
CList::~CList (void) {

	if (this->Is_valid())
		this->Destroy();
}

/////////////////////////////////////////////////////////////////////////////

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

err_code  CList::DuplicateTo (HImgList& _h_dest) const {
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