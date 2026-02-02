/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Feb-2026 at 21:40:32.962, UTC+4, Batumi, Monday;
	This Ebo Pack OpenGL tutorials' registry paths' router class interface implementation file;
*/
#include "sys.reg.router.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::sys_core::storage;
using namespace shared::sys_core::storage::route;

using CCell = CGrid::CCell;
using e_renderer = CRoot::e_renderer;
using CVersion   = CCtx::CVersion;
using CTestCase  = CShaders::CTestCase;

#define TutorialRootKey HKEY_CURRENT_USER

static e_renderer e_current = e_renderer::e_open_gl;
static CString cs_$_root;
static CString cs_theme;

#pragma region cls::CCell{}

CCell::CCell (void) {}

CString CCell::Name (const e_values _e_value) const {
	_e_value;
	if (e_values::e_height == _e_value) return CString(_T("height"));
	if (e_values::e_width == _e_value) return CString(_T("width"));

	return CString(_T("")); // this is '(default)' value name;
}

_pc_sz  CCell::Root (void) const {

	static CString cs_cell;

	if (cs_cell.IsEmpty()) {
		cs_cell.Format(_T("%s\\cell"), (_pc_sz) Get_reg_router().Viewport().Grid().Root());
	}
	return (_pc_sz)cs_cell;
}

#pragma endregion
#pragma region cls::CContext{}

CCtx::CCtx (void) {}

_pc_sz CCtx::Root (void) const {

	static CString cs_root;

	if (cs_root.IsEmpty()) {
		cs_root.Format(_T("%s\\context"), (_pc_sz) Get_reg_router().Root().Path(Get_reg_router().Root().Renderer()));
	}
	return (_pc_sz) cs_root;
}
const
CVersion& CCtx::Version (void) const { return this->m_version; }

#pragma endregion
#pragma region cls::CDraw{}

using e_targets = CDraw::e_targets;

CDraw::CDraw (void) {}

CString CDraw::Name (const e_targets _target) const {
	_target;
	if (e_targets::e_grid == _target) return CString(_T("grid.1"));
	if (e_targets::e_tria == _target) return CString(_T("triangle.1"));

	return CString(_T("")); // this is '(default)' value name;
}

_pc_sz CDraw::Root (void) const {

	static CString cs_root;

	if (cs_root.IsEmpty()) {
		cs_root.Format(_T("%s\\renderer\\draw"), (_pc_sz) Get_reg_router().Root().Path(Get_reg_router().Root().Renderer()));
	}

	return (_pc_sz) cs_root;
}

#pragma endregion
#pragma region cls::CGrird{}

CGrid::CGrid (void) {}
const
CCell& CGrid::Cell (void) const { return m_cell; }
CCell& CGrid::Cell (void)       { return m_cell; }

_pc_sz CGrid::Clr_name (void) const { static _pc_sz p_clr_name = _T("color"); return p_clr_name; }

_pc_sz CGrid::Root (void) const {

	static CString cs_grid;

	if (cs_grid.IsEmpty()) {
		cs_grid.Format(_T("%s\\grid"), (_pc_sz) Get_reg_router().Viewport().Root());
	}
	return (_pc_sz)cs_grid;
}

#pragma endregion
#pragma region cls::CRoot{}

CRoot::CRoot (void) {}
const
HKEY    CRoot::Key  (void) const { static HKEY h_key = TutorialRootKey; return h_key; }
_pc_sz  CRoot::Path (void) const { static _pc_sz p_path = _T("Software\\ebo::pack\\tutorials"); return p_path; }

CString CRoot::Path (const e_renderer _renderer) const {
	_renderer;
	CString cs_path;

	if (e_renderer::e_direct_x == _renderer) cs_path.Format(_T("%s\\direct_x"), CRoot::Path());
	if (e_renderer::e_open_gl  == _renderer) cs_path.Format(_T("%s\\open_gl"), CRoot::Path());

	return  cs_path;
}

e_renderer CRoot::Renderer (void) const { return e_current; }
const bool CRoot::Renderer (const e_renderer _e_curr) {
	_e_curr;
	const bool b_changed = this->Renderer() != _e_curr;
	if (b_changed) {
		e_current = _e_curr;
		cs_$_root = _T("");  // must be set by shaders' class itself;
	}
	return b_changed;
}

#pragma endregion
#pragma region CShaders{}

CShaders::CShaders (void) {}

CString CShaders::Name (const e_types _e_type) const {
	_e_type;
	CString cs_out;

	if (e_types::e_fragment == _e_type) cs_out = _T("$_fragment");
	if (e_types::e_vertex == _e_type) cs_out = _T("$_vertex");

	return  cs_out;
}

CString CShaders::Path (_pc_sz _p_object) const {
	_p_object;
	CString cs_path; cs_path.Format(_T("%s\\%s"), this->Root(), _p_object);
	return  cs_path;
}

_pc_sz  CShaders::Root (void) const {

	if (cs_$_root.IsEmpty()) {
		cs_$_root.Format(_T("%s\\shaders"), (_pc_sz) Get_reg_router().Root().Path(Get_reg_router().Root().Renderer()));
	}
	return (_pc_sz) cs_$_root;
}
#pragma endregion
#pragma region cls::CTestCase{}

CString CTestCase::Key_path (const uint32_t _u_number) {
	_u_number;
	static _pc_sz pc_sz_pat = _T("%s\\test.case.%u");
	CString cs_key_path; cs_key_path.Format(pc_sz_pat, ::Get_reg_router().Shaders().Root(), _u_number);
	return  cs_key_path;
}

#pragma endregion
#pragma region cls::CTheme{}

CTheme::CTheme (void) {}

CString CTheme::Path (const e_element _element) const {
	_element;
	CString cs_path;

	if (e_element::e_bkgnd  == _element) cs_path.Format(_T("%s"), this->Root());
	if (e_element::e_border == _element) cs_path.Format(_T("%s"), this->Root());

	return  cs_path;
}

_pc_sz  CTheme::Root (void) const {

	if (cs_theme.IsEmpty()) {
		cs_theme.Format(_T("%s\\theme"), (_pc_sz) Get_reg_router().Root().Path(Get_reg_router().Root().Renderer()));
	}
	return (_pc_sz) cs_theme;
}

_pc_sz  CTheme::To_str (const e_element _element) {
	static CString cs_out;

	if (e_element::e_bkgnd == _element) cs_out = _T("bkgnd");
	if (e_element::e_border == _element) cs_out = _T("border");

	return (_pc_sz) cs_out; // if it is empty, then the '(default)' value is meant;
}

#pragma endregion
#pragma region cls::CViewPort{}

CViewport::CViewport (void) {}
const
CGrid& CViewport::Grid (void) const { return this->m_grid; }
CGrid& CViewport::Grid (void)       { return this->m_grid; }

_pc_sz CViewport::Root (void) const {

	static CString cs_viewport;

	if (cs_viewport.IsEmpty()) {
		cs_viewport.Format(_T("%s\\viewport"), (_pc_sz) Get_reg_router().Root().Path(Get_reg_router().Root().Renderer()));
	}
	return (_pc_sz) cs_viewport;
}

#pragma endregion
#pragma region cls::CVersion{}

CVersion::CVersion (void) {}

CString CVersion::Name (const e_values _e_value) const {
	_e_value;
	if (e_values::e_core  == _e_value) return CString(_T("core"));
	if (e_values::e_major == _e_value) return CString(_T("major"));
	if (e_values::e_minor == _e_value) return CString(_T("minor"));

	return CString(_T("")); // this is '(default)' value name;
}
_pc_sz  CVersion::Root (void) const {

	static CString cs_root;

	if (cs_root.IsEmpty()) {
		cs_root.Format(_T("%s\\version"), ::Get_reg_router().Ctx().Root());
	}
	return (_pc_sz) cs_root;
}

#pragma endregion

#pragma region cls::CReg_router{}

CReg_router:: CReg_router (void) {}
CReg_router::~CReg_router (void) {}

const   CCtx&  CReg_router::Ctx (void) const { return this->m_ctx; }
const   CDraw& CReg_router::Draw (void) const { return this->m_draw; }

const
CRoot&  CReg_router::Root (void) const { return this->m_root; }
CRoot&  CReg_router::Root (void)       { return this->m_root; }

const
CShaders& CReg_router::Shaders (void) const { return this->m_shaders; }
CShaders& CReg_router::Shaders (void)       { return this->m_shaders; }

const
CTheme&  CReg_router::Theme (void) const { return this->m_theme; }
CTheme&  CReg_router::Theme (void)       { return this->m_theme; }

const
CViewport& CReg_router::Viewport (void) const { return this->m_v_port; }
CViewport& CReg_router::Viewport (void)       { return this->m_v_port; }

CReg_router& ::Get_reg_router (void) {
	static CReg_router router;
	return router;
}

#pragma endregion