/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 23:33:14.733, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials'main window context menu wrapper interface implementation file;
*/
#include "ctx_menu_wrapper.h"
#include "gl_renderer.h"
#include "open_gl_tutor.3.res.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl::camera;

#pragma region cls::CCaretaker{}

CCaretaker::CCaretaker (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CCaretaker::ApplyTo (CCtxMenu& _ctx_mnu) {
	_ctx_mnu;
	this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
	using CState = shared::gui::menus::CState;
	// (1) sets the grid cell size first;
	uint32_t u_cmd_id = 0; u_cmd_id;
	view::CGrid& grid = ::Get_renderer().View().Grid();

	const t_size_u& cell_size = grid.Cell().Get();

	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_H_025, IDR_TUTOR_3_GRD_CELL_H_025 == COrganizer::CGrid::CCell::HeightToCmd(cell_size.cy), this->m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_H_050, IDR_TUTOR_3_GRD_CELL_H_050 == COrganizer::CGrid::CCell::HeightToCmd(cell_size.cy), this->m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_H_075, IDR_TUTOR_3_GRD_CELL_H_075 == COrganizer::CGrid::CCell::HeightToCmd(cell_size.cy), this->m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_H_100, IDR_TUTOR_3_GRD_CELL_H_100 == COrganizer::CGrid::CCell::HeightToCmd(cell_size.cy), this->m_error);

	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_W_025, IDR_TUTOR_3_GRD_CELL_W_025 == COrganizer::CGrid::CCell::WidthToCmd(cell_size.cx), this->m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_W_050, IDR_TUTOR_3_GRD_CELL_W_050 == COrganizer::CGrid::CCell::WidthToCmd(cell_size.cx), this->m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_W_075, IDR_TUTOR_3_GRD_CELL_W_075 == COrganizer::CGrid::CCell::WidthToCmd(cell_size.cx), this->m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_GRD_CELL_W_100, IDR_TUTOR_3_GRD_CELL_W_100 == COrganizer::CGrid::CCell::WidthToCmd(cell_size.cx), this->m_error);

	// (2) sets the draw object which are currently selected;
	const render::CCfg& cfg = ::Get_renderer().Cfg();

	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_DRW_OBJ_GRID, cfg.Is_drawable(e_object::e_grid), this->m_error);
	CState::Check(_ctx_mnu.Handle(), IDR_TUTOR_3_DRW_OBJ_TRIA, cfg.Is_drawable(e_object::e_tria), this->m_error);

	return this->Error();
}

TError&  CCaretaker::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CCell{}
using CCell = COrganizer::CGrid::CCell;

uint32_t CCell::CmdToHeight (const uint32_t _u_cmd_id) {
	_u_cmd_id;
	uint32_t u_hight = 0;
	switch (_u_cmd_id) {
	case IDR_TUTOR_3_GRD_CELL_H_025 : u_hight = 025; break; case IDR_TUTOR_3_GRD_CELL_H_050 : u_hight = 050; break;
	case IDR_TUTOR_3_GRD_CELL_H_075 : u_hight = 075; break; case IDR_TUTOR_3_GRD_CELL_H_100 : u_hight = 100; break;
	}
	return u_hight;
}

uint32_t CCell::CmdToWidth (const uint32_t _u_cmd_id) {
	_u_cmd_id;
	uint32_t u_width = 0;
	switch (_u_cmd_id) {
	case IDR_TUTOR_3_GRD_CELL_W_025 : u_width = 025; break; case IDR_TUTOR_3_GRD_CELL_W_050 : u_width = 050; break;
	case IDR_TUTOR_3_GRD_CELL_W_075 : u_width = 075; break; case IDR_TUTOR_3_GRD_CELL_W_100 : u_width = 100; break;
	}
	return u_width;
}

uint32_t CCell::HeightToCmd (const uint32_t _u_height) {
	_u_height;
	uint32_t u_cmd_id = 0;
	switch (_u_height) {
	case 025 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_H_025; break; case 050 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_H_050; break;
	case 075 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_H_075; break; case 100 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_H_100; break;
	}
	return u_cmd_id;
}

uint32_t CCell::WidthToCmd (const uint32_t _u_width) {
	_u_width;
	uint32_t u_cmd_id = 0;
	switch (_u_width) {
	case 025 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_W_025; break; case 050 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_W_050; break;
	case 075 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_W_075; break; case 100 : u_cmd_id = IDR_TUTOR_3_GRD_CELL_W_100; break;
	}
	return u_cmd_id;
}

#pragma endregion
#pragma region cls::CGrid{}

COrganizer::CGrid::CGrid (void) {}

#pragma endregion
#pragma region cls::COrganizer{}
#pragma endregion