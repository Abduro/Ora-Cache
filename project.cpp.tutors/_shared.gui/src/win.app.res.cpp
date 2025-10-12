/*
	Created by Tech_dog (ebontrop@gmail.com) in 12-Oct-2025 at 09:35:01.597, UTC+4, Batumi, Sunday;
	This is Ebo Pack windows executable genereic resource wrapper interface implementation file;
*/
#include "win.app.res.h"
#include "shared.preproc.h"

using namespace shared::app::res;

CLocator:: CLocator (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CLocator::~CLocator (void) {}

TError&    CLocator::Error (void) const { return this->m_error; }

// https://stackoverflow.com/questions/9646752/findresource-fails-to-find-data-even-though-data-is-in-exe ;
bool CLocator::Has (const uint16_t _u_res_id, const e_res_types _e_type) const {
	_u_res_id; _e_type;
	this->m_error <<__METHOD__<<__s_ok;
	if (0 == _u_res_id) {
		this->m_error <<__e_inv_arg<< TString().Format(_T("#__e_inv_val: '_u_res_id' (%u) has invalid value"), _u_res_id);
		return false;
	}
	// https://stackoverflow.com/questions/27930069/how-do-i-get-a-string-resource-by-name-in-win32-or-mfc ;
	// https://devblogs.microsoft.com/oldnewthing/20040130-00/?p=40813 ;
	t_char* p_type = nullptr;
	uint16_t u_res_id = _u_res_id;

	switch (_e_type) {
	case e_res_types::e_data: p_type = RT_RCDATA; break;
	case e_res_types::e_string: p_type = RT_STRING; u_res_id = u_res_id / 16 + 1; break;
	default: {
			this->m_error <<__e_inv_arg<< TString().Format(_T("#__e_inv_val: '_u_res_id' (%u) is not supported"), _u_res_id);
			return false;
		}
	}
	
	return !!::FindResource(nullptr, MAKEINTRESOURCE(u_res_id), p_type);
}