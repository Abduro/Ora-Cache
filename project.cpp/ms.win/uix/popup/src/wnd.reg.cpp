/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Oct-2026 at 12:37:13.863, UTC+4, Batumi, Thursday;
	The is popup window  registry storage wrapper interface implementation file;
*/
#include "wnd.reg.h"

using namespace ::ex_ui::popup::storage;
using namespace ::ex_ui::popup::storage::route;

#pragma region cls::CApp{}

using CAppWnd = CApp::CWindow;

CApp::CApp (void) {}

_pc_sz CApp::Root (void) const {

	static CString cs_root;
	if (cs_root.IsEmpty()) {
		cs_root.Format(_T("%s\\App"), ::Get_reg_router().Root().Path());
	}
	return (_pc_sz) cs_root;
}
const
CAppWnd& CApp::Window (void) const { return this->m_wnd; }
CAppWnd& CApp::Window (void)       { return this->m_wnd; }

#pragma endregion

#pragma region cls::CRoot{}

_pc_sz  CRoot::Path (void) const {
	static CString cs_root;
	if (cs_root.IsEmpty()) {
		cs_root = TString().Format(_T("%s\\Tutorials"), TBase::Path());
	}
	return (_pc_sz) cs_root;
}

const
CRoot_base& CRoot::operator ()(void) const { return (TBase&)*this; }
CRoot_base& CRoot::operator ()(void)       { return (TBase&)*this; }

#pragma endregion
#pragma region cls::CReg_router{}

CReg_router:: CReg_router (void) {}
CReg_router::~CReg_router (void) {}

const
CApp& CReg_router::App (void) const { return this->m_app; }
CApp& CReg_router::App (void)       { return this->m_app; }
const
CRoot& CReg_router::Root (void) const { return this->m_root; }
CRoot& CReg_router::Root (void)       { return this->m_root; }

#pragma endregion

CReg_router& ::Get_reg_router (void) {
	static CReg_router router;
	return router;
}

#pragma region cls::CWindow{}

CAppWnd::CWindow (void) {}

_pc_sz CAppWnd::Position (void) const {

	static CString cs_pos;
	if (cs_pos.IsEmpty()) {
		cs_pos.Format(_T("%s\\Position"), this->Root());
	}
	return (_pc_sz) cs_pos;
}

_pc_sz CAppWnd::Root (void) const {

	static CString cs_root;
	if (cs_root.IsEmpty()) {
		cs_root.Format(_T("%s\\Window"), ::Get_reg_router().App().Root());
	}
	return (_pc_sz) cs_root;
}

using e_pos = CAppWnd::e_pos;

_pc_sz CAppWnd::Side (const e_pos _e_side) const {
	_e_side;
	static CString cs_sides[4];
	if (cs_sides[(uint32_t)_e_side].IsEmpty()) {
		cs_sides[(uint32_t)_e_side] = e_pos::e_left == _e_side ? _T("Left") : e_pos::e_right == _e_side ? _T("Right") : e_pos::e_top == _e_side ? _T("Top") : _T("Bottom");
	}
	return (_pc_sz) cs_sides[(uint32_t)_e_side];
}

#pragma endregion