/*
	Created by Tech_dog (ebontrop@gmail.ru) on 16-Oct-2026 at 18:43:28.846, UTC+4, Batumi, Friday;
	This is system shell dialogs' wrapper interface implementation file;
*/
#include "shell.fs.dlg.h"

using namespace ::shared::shell::ntfs::dialogs;

#pragma region cls::CFileOpen{}

using COpts = CFileOpts;

CFileOpen::CFileOpen (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok;

	this->m_error << this->m_p_dlg.CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL);
	this->m_opts  << this->m_p_dlg;
}

err_code CFileOpen::Do (_pc_sz _p_title, const HWND _h_owner) {
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _h_owner || false == !!::IsWindow(_h_owner))
		return this->m_error <<__e_hwnd = _T("__e_hwnd: This dialog owner window handle is invalid"); // for saving a modality of the dialog and proper z-order;

	if (this->Filter().Is_valid() == false)
		return this->m_error = this->Filter().Error();

	if (nullptr == this->m_p_dlg)
		return this->m_error << (err_code)TErrCodes::eExecute::eState = _T("__e_state: 'File Open' dialog interface object is not created");

	this->m_error << this->m_p_dlg->SetFileTypes(static_cast<UINT>(this->Filter().Items().size()), (COMDLG_FILTERSPEC*)this->Filter().Items().data());
	if (this->Error())
		return this->Error();

	CString cs_title(_p_title); cs_title.Trim();
	if (cs_title.IsEmpty())
		cs_title = _T("Open File");

	this->m_error << this->m_p_dlg->SetTitle((_pc_sz)cs_title);
	if (this->Error())
		return this->Error();

	this->m_error << this->m_p_dlg->Show(_h_owner);
	if (this->Error())
		return this->Error();

	CComPtr<IShellItem> p_item;
	this->m_error << this->m_p_dlg->GetResult(&p_item);
	if (this->Error())
		return this->Error();

	PWSTR lp_path = nullptr;
	this->m_error << p_item->GetDisplayName(SIGDN_FILESYSPATH, &lp_path);
	if (this->Error())
		return this->Error();

	this->m_selected = lp_path;
	::CoTaskMemFree(lp_path); lp_path = nullptr;

	return this->Error();
}

TError&  CFileOpen::Error (void) const { return this->m_error; }
const
CFilter& CFileOpen::Filter (void) const { return this->m_filter; }
CFilter& CFileOpen::Filter (void)       { return this->m_filter; }
const
COpts&   CFileOpen::Opts (void) const { return this->m_opts; }
COpts&   CFileOpen::Opts (void)       { return this->m_opts; }
     
const
CString& CFileOpen::Selected (void) const { return this->m_selected; }

#pragma endregion

namespace shared { namespace shell { namespace ntfs { namespace dialogs {

}}}}

#pragma region cls::CFileOpts{}

using e_common = CFileOpts::e_common;
using e_open = CFileOpts::e_open;
using e_save = CFileOpts::e_save;

static _pc_sz e_no_open_dlg = _T("__e_ptr: Invalid pointer to 'File Open' interface");

CFileOpts::CFileOpts (void) : m_flags(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("__e_not_inited: The flags are not set"); }

TError&  CFileOpts::Error (void) const { return this->m_error; }

dword_t  CFileOpts::Flags (void) const { return this->m_flags; }

err_code CFileOpts::Get (void) {
	return CFileOpts::Get(this->m_p_dlg, this->m_flags, this->m_error <<__METHOD__<<__s_ok); 
}

err_code CFileOpts::Get (IFileOpenDlgPtr& _p_dlg, dword_t& _flags, CError& _error) {
	_p_dlg; _flags = 0; _error;
	if (nullptr == _p_dlg)
		return _error <<__e_pointer = e_no_open_dlg;

	FILEOPENDIALOGOPTIONS dlg_options = 0;
	_error << _p_dlg->GetOptions(&dlg_options); // https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ifiledialog-getoptions ;
	if (false == _error)
		_flags = static_cast<dword_t>(dlg_options);

	return _error;
}

bool CFileOpts::Has (const e_common _e_flag, const dword_t _flags) { return _e_flag & _flags; }
bool CFileOpts::Has (const e_open   _e_flag, const dword_t _flags) { return _e_flag & _flags; }
bool CFileOpts::Has (const e_save   _e_flag, const dword_t _flags) { return _e_flag & _flags; }
const
IFileOpenDlgPtr& CFileOpts::Ptr (void) const { return this->m_p_dlg; }

err_code CFileOpts::Set (const dword_t _flags) {
	if (__succeeded(CFileOpts::Set(this->m_p_dlg, _flags, this->m_error <<__METHOD__<<__s_ok)))
		this->m_flags = _flags;
	return this->Error();
}

err_code CFileOpts::Set (IFileOpenDlgPtr& _p_dlg, const dword_t _flags, CError& _error) {
	_p_dlg; _flags; _error;
	if (nullptr == _p_dlg)
		return _error <<__e_pointer = e_no_open_dlg;

	_error << _p_dlg->SetOptions(_flags); // https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ifiledialog-setoptions ;
	
	return _error;
}

CFileOpts& CFileOpts::operator <<(IFileOpenDlgPtr& _p_dlg) { this->m_p_dlg = _p_dlg; return *this; }

#pragma endregion
#pragma region cls::CFilter{}

CFilter::CFilter (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("No filter item is added yet"); }

err_code CFilter::Append (_pc_sz _p_name, _pc_sz _p_spec) {
	_p_name; _p_spec;
	this->m_error <<__METHOD__<<__s_ok;

	CString cs_name(_p_name), cs_spec(_p_spec); cs_name.Trim(); cs_spec.Trim();

	if (cs_name.IsEmpty()) return this->m_error <<__e_inv_arg = _T("__e_inv_arg: Item name is empty");
	if (cs_spec.IsEmpty()) return this->m_error <<__e_inv_arg = _T("__e_inv_arg: Item spec is empty");
	try {
#if (1)
		this->m_items.emplace_back(::std::make_pair(cs_name, cs_spec));
#else
		this->m_items.insert[cs_spec] = cs_name;
#endif
	}
	catch (const ::std::bad_alloc&) { this->m_error <<__e_no_memory; }

	return this->Error();
}

TError&  CFilter::Error (void) const { return this->m_error; }

bool     CFilter::Is_valid (void) const { return this->Items().empty() == false; }
#if (1)
const
flt_items_t& CFilter::Items (void) const { return this->m_items; }
flt_items_t& CFilter::Items (void)       { return this->m_items; }
#else
const
item_map_t& CFilter::Items (void) const { return this->m_items; }
item_map_t& CFilter::Items (void)       { return this->m_items; }
#endif

#pragma endregion