/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Nov-2026 at 20:44:25.920, UTC+4, Batumi, Thursday;
	The is virtual camera test application  registry storage wrapper interface implementation file;
*/
#include "test.gui.reg.h"
#include "test.gui.res.h"
#include "test.gui.view.h"

using namespace  ::test::app::storage;
using CRegApp  = ::test::app::storage::route::CApp ;
using CRegCmd  = ::test::app::storage::route::CCommand ;
using CRegCmds = ::test::app::storage::route::CCommands;
using CRegMru  = ::test::app::storage::route::CMru;
using CRegRoot = ::test::app::storage::route::CRoot;

#pragma region cls::CCommand{}

static _pc_sz p_err_not_inited = _T("_e_not_inited: The command is not set");

CCommand::CCommand (const uint32_t _cmd_id) : m_cmd_id(_cmd_id), m_tab_ndx(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = p_err_not_inited; }

TError&   CCommand::Error (void) const { return this->m_error; }

uint32_t  CCommand::Id (void) const { return this->m_cmd_id; }
err_code  CCommand::Id (const uint32_t _cmd_id) {
	_cmd_id;
	this->m_error <<__METHOD__<<__s_ok;
	if (false == CCommand::Is_valid(_cmd_id, this->m_error))
		return this->Error();

	this->m_cmd_id = _cmd_id;

	return this->Error();
}

bool  CCommand::Is_valid (void) const { return CCommand::Is_valid(this->Id(), this->Tab(), this->m_error); }
bool  CCommand::Is_valid (const uint32_t _cmd_id, CError& _error) {
	_cmd_id; _error;
	switch (_cmd_id) {
	case IDC_VIEW_LOAD_HTML: { _error <<__s_ok; } break;
	default: _error <<__e_inv_arg = TString().Format(_T("__e_inv_arg: The command (id = %u) is not defined"), _cmd_id);
	}
	return false == _error;
}
bool  CCommand::Is_valid (const uint32_t _cmd_id, const uint32_t _tab_ndx, CError& _error) {
	_cmd_id; _error; _tab_ndx;
	if (false == CCommand::Is_valid(_cmd_id, _error))
		return false;

	const uint32_t u_tab_count = ::shared::Get_View().Pages().Get().Tabs().Count();
	if (0 < u_tab_count && u_tab_count > _tab_ndx)
	     _error <<__s_ok;
	else _error <<__e_inv_arg = TString().Format(_T("__e_inv_arg: The tab index (%u) is out of tabs' count (%u)"), _tab_ndx, u_tab_count);
	
	return false == _error;
}

CString  CCommand::Get (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == this->Is_valid())
		return CString();

	TRegKeyEx reg_key;
	CString cs_path = reg_key.Value().GetString(CRegCmd::Get_path(this->Id(), this->Tab()), CRegCmd::Get_name(this->Id()));
	if (cs_path.IsEmpty())
		this->m_error = reg_key.Error();

	return cs_path;
}

err_code CCommand::Set (const CString& _value) {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == this->Is_valid())
		return this->m_error <<__e_not_inited = p_err_not_inited;

	if (_value.IsEmpty())
		return this->m_error <<__e_inv_arg = _T("__e_inv_arg: The input value string is empty");

	TRegKeyEx reg_key;
	if (__failed(reg_key.Value().Set(CRegCmd::Get_path(this->Id(), this->Tab()), CRegCmd::Get_name(this->Id()), (_pc_sz)_value)))
		this->m_error = reg_key.Error();

	return this->Error();
}

uint32_t  CCommand::Tab (void) const { return this->m_tab_ndx; }   
err_code  CCommand::Tab (const uint32_t _tab_ndx) {
	_tab_ndx;
	this->m_error <<__METHOD__<<__s_ok;
	if (false == CCommand::Is_valid(this->Id(), _tab_ndx, this->m_error))
		return this->Error();

	this->m_tab_ndx = _tab_ndx;

	return this->Error();
}

CCommand& CCommand::operator << (const uint32_t _cmd_id) { this->Id(_cmd_id); return *this; }
err_code  CCommand::operator << (const _pc_sz _p_value) { return this->Set(CString(_p_value)); }
CCommand& CCommand::operator >> (const uint32_t _tab_ndx) { this->Tab(_tab_ndx); return *this; }

#pragma endregion
#pragma region cls::CRegApp{}

CRegApp::CApp (void) {}

_pc_sz CRegApp::Root (void) const {
	static CString cs_root;
	if (cs_root.IsEmpty()) {
		cs_root.Format(_T("%s\\App"), ::Get_reg_router().Root().Path());
	}
	return (_pc_sz) cs_root;
}

#pragma endregion
#pragma region cls::CRegCmd{}

_pc_sz CRegCmd::Get_name (const uint32_t _cmd_id) {
	_cmd_id;
	static CString cs_name;

	switch (_cmd_id) {
		case IDC_VIEW_LOAD_HTML: cs_name = _T("Path"); break;
		default: cs_name = _T(""); // this is (Default) value name of type REG_SZ;
	}

	return (_pc_sz) cs_name;
}

_pc_sz CRegCmd::Get_path (const uint32_t _cmd_id, const uint32_t _tab_ndx) {
	static CString cs_path;
	cs_path.Format(_T("%s\\%u\\%u"), ::Get_reg_router().Cmds().Root(), _cmd_id, _tab_ndx);
	return (_pc_sz)cs_path;
}

#pragma endregion
#pragma region cls::CRegCmds{}

CRegCmds::CCommands (void) {}

_pc_sz CRegCmds::Root (void) {
	static CString cs_root;
	if (cs_root.IsEmpty()) {
		cs_root.Format(_T("%s\\Commands"), ::Get_reg_router().App().Root());
	}
	return (_pc_sz) cs_root;
}

#pragma endregion
#pragma region cls::CRegMru{}

_pc_sz CRegMru::Name (void) const { static _pc_sz p_name = _T("Path"); return p_name; }
_pc_sz CRegMru::Root (void) const {
	static CString cs_root;
	if (cs_root.IsEmpty()) {
		cs_root.Format(_T("%s\\MRU"), ::Get_reg_router().Cmds().Root());
	}
	return (_pc_sz) cs_root;
}

#pragma endregion
#pragma region cls::CRegRoot{}

_pc_sz  CRegRoot::Path (void) const {
	static CString cs_root;
	if (cs_root.IsEmpty()) {
		cs_root = TString().Format(_T("%s\\Tutorials"), TBase::Path());
	}
	return (_pc_sz) cs_root;
}

const
CRoot_base& CRegRoot::operator ()(void) const { return (TBase&)*this; }
CRoot_base& CRegRoot::operator ()(void)       { return (TBase&)*this; }

#pragma endregion
#pragma region cls::CReg_router{}

CReg_router:: CReg_router (void) {}
CReg_router::~CReg_router (void) {}
const
CRegApp&  CReg_router::App (void) const { return this->m_app; }
CRegApp&  CReg_router::App (void)       { return this->m_app; }
const
CRegCmds& CReg_router::Cmds (void) const { return this->m_cmds; }
CRegCmds& CReg_router::Cmds (void)       { return this->m_cmds; }
const
CRegMru&  CReg_router::Mru (void) const { return this->m_mru; }
CRegMru&  CReg_router::Mru (void)       { return this->m_mru; }
const
CRegRoot& CReg_router::Root (void) const { return this->m_root; }
CRegRoot& CReg_router::Root (void)       { return this->m_root; }

#pragma endregion

CReg_router& ::Get_reg_router (void) {
	static CReg_router router;
	return router;
}