/*
	Created by Tech_dog (ebontrop@gmail.ru) on 16-Oct-2026 at 18:43:28.846, UTC+4, Batumi, Friday;
	This is system shell dialogs' wrapper interface implementation file;
*/
#include "shell.fs.dlg.h"

using namespace ::shared::shell::ntfs::dialogs;

#pragma region cls::CFileOpen{}

CFileOpen::CFileOpen (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CFileOpen::Do (_pc_sz _p_title, const HWND _h_owner) {
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _h_owner || false == !!::IsWindow(_h_owner))
		return this->m_error <<__e_hwnd = _T("__e_hwnd: This dialog owner window handle is invalid"); // for saving a modality of the dialog and proper z-order;

	if (this->Filter().Is_valid() == false)
		return this->m_error = this->Filter().Error();

	CComPtr<IFileOpenDialog> p_dialog;
	this->m_error << p_dialog.CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL);
	if (this->Error())
		return this->Error();

	this->m_error << p_dialog->SetFileTypes(static_cast<UINT>(this->Filter().Items().size()), (COMDLG_FILTERSPEC*)this->Filter().Items().data());
	if (this->Error())
		return this->Error();

	CString cs_title(_p_title); cs_title.Trim();
	if (cs_title.IsEmpty())
		cs_title = _T("Open File");

	this->m_error << p_dialog->SetTitle((_pc_sz)cs_title);
	if (this->Error())
		return this->Error();

	this->m_error << p_dialog->Show(_h_owner);
	if (this->Error())
		return this->Error();

	CComPtr<IShellItem> p_item;
	this->m_error << p_dialog->GetResult(&p_item);
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
CString& CFileOpen::Selected (void) const { return this->m_selected; }

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