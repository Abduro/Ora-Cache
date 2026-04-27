/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 23:33:14.733, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials'main window context menu wrapper interface implementation file;
*/
#include "ctx_menu_wrapper.h"
#include "gl_renderer.h"
#include "open_gl_tutor.3.res.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

#include "console.h"
#include "console.pers.h"

using namespace ex_ui::draw::gui;

namespace renderer { using CCfg = ex_ui::draw::open_gl::render::CCfg; }
namespace views { using CGrid = ex_ui::draw::open_gl::view::CGrid; }

using CState = shared::gui::menus::CState;

#pragma region cls::CBase{}

using CBase = menus::CBase;

CBase::CBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
TError& CBase::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CCaretaker{}

CCaretaker::CCaretaker (void) { TBase::m_error >>__CLASS__; }

err_code CCaretaker::ApplyTo (CCtxMenu& _ctx_mnu) {
	_ctx_mnu;
	TBase::m_error >>__CLASS__<<__METHOD__<<__s_ok;
	using CState = shared::gui::menus::CState;

	// (1) sets the grid cell size first;
	menus::CCell cell;
	if (__failed(cell.ApplyTo(_ctx_mnu))) {
		TBase::m_error = cell.Error();
		__trace_err_2(TBase::Error());
	}

	// (2) sets the draw object which are currently selected;
	const renderer::CCfg& cfg = ::Get_renderer().Cfg();

	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_DRW_OBJ_GRID, cfg.Is_drawable(TPipe::e_grid), TBase::m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_DRW_OBJ_TRIA, cfg.Is_drawable(TPipe::e_tria), TBase::m_error);

	// (3) sets the console menu items related to check state;
	menus::CConsole con;
	if (__failed(con.ApplyTo(_ctx_mnu))) {
		TBase::m_error = con.Error();
		__trace_err_2(TBase::Error());
	}
	return TBase::Error();
}

#pragma endregion
#pragma region cls::CCell{}

menus::CCell::CCell (void) : TBase() { TBase::m_error >> __CLASS__; }

err_code menus::CCell::ApplyTo (CCtxMenu& _ctx_mnu) {
	_ctx_mnu;
	TBase::m_error >>__CLASS__<<__METHOD__<<__s_ok;
#if (0)
	views::CGrid& grid = ::Get_renderer().View().Grid();
	const t_size_u& cell_size = grid.Cell().Get();

	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_H_025, IDR_TUTOR_3_GRD_CELL_H_025 == menus::CCell::HeightToCmd(cell_size.cy), TBase::m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_H_050, IDR_TUTOR_3_GRD_CELL_H_050 == menus::CCell::HeightToCmd(cell_size.cy), TBase::m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_H_075, IDR_TUTOR_3_GRD_CELL_H_075 == menus::CCell::HeightToCmd(cell_size.cy), TBase::m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_H_100, IDR_TUTOR_3_GRD_CELL_H_100 == menus::CCell::HeightToCmd(cell_size.cy), TBase::m_error);

	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_W_025, IDR_TUTOR_3_GRD_CELL_W_025 == menus::CCell::WidthToCmd (cell_size.cx), TBase::m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_W_050, IDR_TUTOR_3_GRD_CELL_W_050 == menus::CCell::WidthToCmd (cell_size.cx), TBase::m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_W_075, IDR_TUTOR_3_GRD_CELL_W_075 == menus::CCell::WidthToCmd (cell_size.cx), TBase::m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_W_100, IDR_TUTOR_3_GRD_CELL_W_100 == menus::CCell::WidthToCmd (cell_size.cx), TBase::m_error);
#endif
	return TBase::Error();
}

uint32_t menus::CCell::CmdToHeight (const uint32_t _u_cmd_id) {
	_u_cmd_id;
	uint32_t u_hight = 0;
	switch (_u_cmd_id) {
	case IDR_TUTOR_3_GRD_CELL_H_025 : u_hight = 025; break; case IDR_TUTOR_3_GRD_CELL_H_050 : u_hight = 050; break;
	case IDR_TUTOR_3_GRD_CELL_H_075 : u_hight = 075; break; case IDR_TUTOR_3_GRD_CELL_H_100 : u_hight = 100; break;
	}
	return u_hight;
}

uint32_t menus::CCell::CmdToWidth (const uint32_t _u_cmd_id) {
	_u_cmd_id;
	uint32_t u_width = 0;
	switch (_u_cmd_id) {
	case IDR_TUTOR_3_GRD_CELL_W_025 : u_width = 025; break; case IDR_TUTOR_3_GRD_CELL_W_050 : u_width = 050; break;
	case IDR_TUTOR_3_GRD_CELL_W_075 : u_width = 075; break; case IDR_TUTOR_3_GRD_CELL_W_100 : u_width = 100; break;
	}
	return u_width;
}

uint32_t menus::CCell::HeightToCmd (const uint32_t _u_height) {
	_u_height;
	uint32_t u_cmd_id = 0;
	switch (_u_height) {
	case 025 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_H_025; break; case 050 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_H_050; break;
	case 075 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_H_075; break; case 100 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_H_100; break;
	}
	return u_cmd_id;
}

uint32_t menus::CCell::WidthToCmd (const uint32_t _u_width) {
	_u_width;
	uint32_t u_cmd_id = 0;
	switch (_u_width) {
	case 025 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_W_025; break; case 050 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_W_050; break;
	case 075 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_W_075; break; case 100 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_W_100; break;
	}
	return u_cmd_id;
}

#pragma endregion
#pragma region cls::CConsole{}

using CConsole = menus::CConsole;

CConsole::CConsole (void) : TBase() { TBase::m_error >>__CLASS__; }

err_code CConsole::ApplyTo (CCtxMenu& _ctx_mnu) {
	_ctx_mnu;
	TBase::m_error <<__METHOD__<<__s_ok;

	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_CON_PINNED, ::Get_ConPers().Pin().Is_pinned(), TBase::m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_CON_VISIBLE, TConAccess().Is_visible(), TBase::m_error);
	
	return TBase::Error();
}

bool CConsole::On_command (const uint32_t _u_cmd_id) {
	_u_cmd_id;
	TBase::m_error <<__METHOD__<<__s_ok;
	bool b_handled = true;

	using namespace shared::console;
	
	CCmd_Handler handler;

	switch (_u_cmd_id) {
	case IDR_TUTOR_3_CON_CLEAR  : {
		if (__failed(handler.On_command(e_cmd_ids::e_clear)))
			TBase::m_error = handler.Error();
		else { __trace_info_2(_T("command 'Clear console' (%04u) is completed;\n"), _u_cmd_id); }
	} break;
	case IDR_TUTOR_3_CON_PINNED : {} break;
	case IDR_TUTOR_3_CON_VISIBLE: {
#if (0)
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-iswindowvisible ;
		TConAccess() << !TConAccess().Is_visible();
#else
		handler.On_command(e_cmd_ids::e_visible);
#endif
		{ __trace_info_2(_T("command 'Show/Hide console' (%04u) is completed;\n"), _u_cmd_id); }
	} break;
	default:
		b_handled = false;
	}

	if (TBase::Error())
		__trace_err_ex_2(TBase::Error());

	return b_handled;
}

#pragma endregion
#pragma region cls::CGrid{}

#include "gl_viewport.h"
#include "open_gl_tutor.3.res.h"

menus::CGrid::CGrid (void) { TBase::m_error >>__CLASS__; }

bool menus::CGrid::On_command (const uint32_t _u_cmd_id) {
	_u_cmd_id;
	TBase::m_error <<__METHOD__<<__s_ok;

	const uint32_t u_height = CCell::CmdToHeight(_u_cmd_id);
	const uint32_t u_width  = CCell::CmdToWidth (_u_cmd_id);

	using CViewPort = ex_ui::draw::open_gl::CViewPort;

	bool b_handled = false;
#if (0)
	switch (u_cmd_id) {
	case IDR_TUTOR_3_GRD_CELL_H_025 : grid.Cell().H(025); break; case IDR_TUTOR_3_GRD_CELL_H_050 : grid.Cell().H(050); break;
	case IDR_TUTOR_3_GRD_CELL_H_075 : grid.Cell().H(075); break; case IDR_TUTOR_3_GRD_CELL_H_100 : grid.Cell().H(100); break;
	case IDR_TUTOR_3_GRD_CELL_W_025 : grid.Cell().W(025); break; case IDR_TUTOR_3_GRD_CELL_W_050 : grid.Cell().W(050); break;
	case IDR_TUTOR_3_GRD_CELL_W_075 : grid.Cell().W(075); break; case IDR_TUTOR_3_GRD_CELL_W_100 : grid.Cell().W(100); break;
	default:
		return this->Error();
	}
#elif (false == true)
	TRenderer& renderer = ::Get_renderer();
	CViewPort& viewport = renderer.View();

	views::CGrid&  grid = viewport.Grid();

	if (0 != u_height) { grid.Cell().H(u_height); b_handled = true; }
	if (0 != u_width ) { grid.Cell().W(u_width);  b_handled = true; }

	if (b_handled)
	if (__failed(grid.Update(viewport.Get()))) { // re-calculates the grid lines' layout;
		return TBase::m_error = grid.Error();
	}
#endif
	return b_handled;
}

#pragma endregion
#pragma region cls::COrganizer{}

COrganizer::COrganizer (void) { TBase::m_error >>__CLASS__; }

err_code COrganizer::On_command (const uint32_t _u_cmd_id) {
	_u_cmd_id;
	TBase::m_error >>__CLASS__<<__METHOD__<<__s_ok;

	// (1) checks for console related commands;
	menus::CConsole console;
	if (console.On_command(_u_cmd_id)) {
		if (console.Error())
			TBase::m_error = console.Error();
		return TBase::Error();
	}

	bool b_draw = false;

	//__trace_info(_T("selected cmd_id: %u;\n"), _u_cmd_id);
	// (2) makes deal with the background grid cell dimensions;
	menus::CGrid grid;
	b_draw = grid.On_command(_u_cmd_id);
	if (grid.Error())
		return TBase::m_error = grid.Error();

	TRenderer& renderer = ::Get_renderer();
	// (3) what is drawble objects about;
	if (IDR_TUTOR_3_DRW_OBJ_GRID == _u_cmd_id) { renderer.Cfg().Toggle(TPipe::e_object::e_grid); b_draw = true; }
	if (IDR_TUTOR_3_DRW_OBJ_TRIA == _u_cmd_id) { renderer.Cfg().Toggle(TPipe::e_object::e_tria); b_draw = true; }
	
	if (false == b_draw) // nothing to draw;
		return TBase::Error();

	renderer.Is_allowed(true);

	if (__failed(renderer.Draw()))
		TBase::m_error = renderer.Error();

	renderer.Is_allowed(false);

	return TBase::Error();
}
#pragma endregion