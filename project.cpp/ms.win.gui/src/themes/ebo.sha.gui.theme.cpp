/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Dec-2020 at 8:37:53.978 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Sha Optima Tool GUI generic format color theme interface implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack UM test project on 14-Jan-2021 at 12:03:27.692 pm, UTC+7, Novosibirsk, Thursday;
	Adopted to Ebo Pack render project desktop GUI app on 26-Apr-2025 at 22:49:56.686, UTC+4, Batumi, Saturday;
*/
#include "ebo.sha.gui.theme.h"

using namespace ebo::sha::theme;
using namespace ebo::sha::theme::colors;

using namespace ebo::sha::theme::paths;

/////////////////////////////////////////////////////////////////////////////

TError& CNot_Copyable::Error (void) const { return this->m_error; }
bool    CNot_Copyable::Is_valid (void) const { return false == this->m_path.IsEmpty(); }

_pc_sz  CNot_Copyable::Get (void) const { return (_pc_sz) this->m_path; }

/////////////////////////////////////////////////////////////////////////////

CRoot:: CRoot (void) { No_Copy::m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CRoot::~CRoot (void) {}

err_code CRoot::Set (void) {
	No_Copy::m_error <<__METHOD__<<__s_ok;
#if (0)	
	err_code n_error = ex_ui::theme::Get_current().Load(); // this is required for setting the current theme;

	if (__failed(n_error))
		return this->m_error << n_error;

	CString cs_root = Get_router().TestCase().Root();  // gets the path to the root key;

	CRegKey root_key;
	LSTATUS n_result = root_key.Open(Get_router().Root(), (_pc_sz) cs_root);
	if (!!n_result)
		return this->m_error = dword(n_result);

	t_char  sz_buffer[512] = {0}; unsigned long u_count = _countof(sz_buffer);

	unsigned long n_chars = u_count;

	n_result = root_key.QueryStringValue(_T("path"), sz_buffer, &n_chars);
	if (!!n_result)
		(this->m_error = dword(n_result)) = _T("Path to test cases is not specified;");
	else
		this->m_path = sz_buffer;
#elif (true==false)
	// just the playing with operators;
	TRegKeyEx the_key;    (the_key[(_pc_sz)_T("")])() << (_pc_sz) Get_router().TestCase().Root() >> _T("path");
	this->m_path = (_pc_sz)the_key[(_pc_sz)_T("")];

	if (No_Copy::m_path.IsEmpty())
		No_Copy::m_error = the_key[(long)0] = _T("Path to test cases is not specified;");
#else
	TRegKeyEx the_key;
	the_key.Value().Cache() << (_pc_sz) Get_router().TestCase().Root() >> _T("path");
	if (the_key.Value().Cache().Is() == false) {
		No_Copy::m_error << __e_not_expect = _T("Cache object is not valid");
	}
	else {
		this->m_path = the_key.Value().GetString((_pc_sz) Get_router().TestCase().Root(), _T("path"));
	}

#endif
	return No_Copy::Error();
}

CRoot::operator _pc_sz (void) { this->Set(); return CNot_Copyable::Get(); }

/////////////////////////////////////////////////////////////////////////////

CStatus:: CStatus (void) { No_Copy::m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CStatus::~CStatus (void) {}

CString   CStatus::Get (const uint32_t _img_ndx) {
	_img_ndx;
	CString cs_file = No_Copy::Get();

	TRegKeyEx the_key; (the_key[(_pc_sz)_T("")])() << (_pc_sz) Get_router().TestCase().Control(0) >> TStringEx().Format(_T("image_%u"), _img_ndx);
	cs_file += (_pc_sz) the_key[(_pc_sz)_T("")];

	if (the_key.Error().Is())
		No_Copy::m_error = the_key.Error();

	return cs_file;
}

err_code  CStatus::Set (void) {

	No_Copy::m_error <<__METHOD__<<__s_ok;

	CRoot root;

	if (__failed(root.Set()))
		return No_Copy::m_error = root.Error();

	No_Copy::m_path = root.Get();
	No_Copy::m_path += _T("sta-bar\\"); // it is supposed the path ends already up by a backslash;
	
	return No_Copy::Error();
}